/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:56:47 by mbarrah           #+#    #+#             */
/*   Updated: 2025/05/09 16:38:06 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/input.h"

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
		setup_signals_interactive();
		input = get_input();
		if (!input)
			break;
		if (!process_input(data, input))
			continue;
		cleanup_and_continue(data, input);
		setup_signals_exec();
		exec_cmds(data->cmd);
		data->cmd = NULL;
	}
}
