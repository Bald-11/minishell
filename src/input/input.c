/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:56:47 by mbarrah           #+#    #+#             */
/*   Updated: 2025/06/18 19:44:18 by yabarhda         ###   ########.fr       */
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

static void	cleanup_and_continue(t_data *data)
{
	data->token = NULL;
	free(data->input);
	data->input = NULL;
}

static int	process_input(t_data *data)
{
	if (!check_quotes(data->input))
		return (0);
	data->token = tokenize(data->input);
	if (!check_syntax(data->token))
	{
		cleanup_and_continue(data);
		return (0);
	}
	expand_tokens(&data->status, data->token, data->env);
	data->cmd = parse_commands(data->token, data);
	if (!data->cmd)
	{
		cleanup_and_continue(data);
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
		data->input = input;
		if ((input && !input[0]) || !process_input(data))
		{
			cleanup_and_continue(data);
			continue ;
		}
		signals_heredoc();
		if (heredoc_check(data))
			(signals_exec(), exec_cmds(data->cmd));
		cleanup_and_continue(data);
		data->cmd = NULL;
	}
}
