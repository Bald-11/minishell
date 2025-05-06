/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:56:47 by mbarrah           #+#    #+#             */
/*   Updated: 2025/05/06 17:00:44 by yabarhda         ###   ########.fr       */
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
	// free_tokens(data->token);
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
	expand_tokens(data->token, data->env);
	// print_tokens(data->token);
	data->cmd = parse_commands(data->token, data);
	if (!data->cmd)
	{
		// printf("Error: Failed to parse commands\n");
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
		input = get_input();
		if (!input)
			break;
		if (!process_input(data, input))
			continue;
		// print_cmds(data->cmd);
		cleanup_and_continue(data, input);
		exec_cmds(data->cmd);
		// free_all_cmds(data->cmd);
		data->cmd = NULL;
	}
}
