/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:56:47 by mbarrah           #+#    #+#             */
/*   Updated: 2025/05/20 10:48:19 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell.h"
#include "../../inc/input.h"
#include "../../inc/signals.h"
#include "../../inc/globals.h"
#include "../../inc/parser.h"
#include "../../inc/exec.h"

char	*get_input(void)
{
	char	*input;

	input = readline("minishell> ");
	if (!input)
	{
		printf("exit\n");
		return (NULL);
	}
	if (input[0] != '\0')
		add_history(input);
	return (input);
}

static void	cleanup_and_continue(t_data *data, char *input)
{
	data->token = NULL;
	free(input);
}

static int	process_input(t_data *data, char *input)
{
	if (!check_quotes(input))
		return (0);
	data->token = tokenize(input);
	if (!check_syntax(data->token))
	{
		cleanup_and_continue(data, input);
		return (0);
	}
	expand_tokens(&data->status, data->token, data->env);
	data->cmd = parse_commands(data->token, data);
	if (!data->cmd)
	{
		cleanup_and_continue(data, input);
		return (0);
	}
	return (1);
}

void	minishell(t_data *data)
{
	char	*input;

	while (1)
	{
		signals_interactive();
		input = get_input();
		if (!input)
			break ;
		if (g_sigint_received)
		{
			data->status = 130;
			g_sigint_received = 0;
		}
		if ((input && !input[0]) || !process_input(data, input))
		{
			cleanup_and_continue(data, input);
			continue ;
		}
		signals_exec();
		exec_cmds(data->cmd);
		cleanup_and_continue(data, input);
		data->cmd = NULL;
	}
}
