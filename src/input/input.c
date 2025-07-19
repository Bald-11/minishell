/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:56:47 by mbarrah           #+#    #+#             */
/*   Updated: 2025/07/19 17:59:18 by yabarhda         ###   ########.fr       */
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

/* 

	t_token	*current;
	char	*expanded_value;

	current = tokens;
	while (current)
	{
		if (current->value && ft_strchr(current->value, '$'))
		{
			expanded_value = expand_env_vars(status, current->value, env);
			if (expanded_value)
			{
				// free(current->value);
				current->value = expanded_value;
			}
		}
		current = current->next;
	}

*/

/* void	token_check(t_data *data)
{
	t_token	*tmp;
	char	*expanded_value;

	tmp = data->token;
	while (tmp)
	{
		if (tmp->value && ft_strchr(tmp->value, '$'))
		{
			int i = 0;
			int quote = 0;
			while (tmp->value[i])
			{
				if ((tmp->value[i] == '\"' || tmp->value[i] == '\'') && !quote)
					quote = !quote;
				if (tmp->value[i] == '$' && !quote)
				{
					if (tmp->value[i + 1] == '\"' || tmp->value[i + 1] == '\'')
						
				}
				i++;
			}
		}
		tmp = tmp->next;
	}	
} */

static int	process_input(t_data *data)
{
	if (!check_quotes(data->input))
		return (0);
	data->token = tokenize(data->input);
	if (!check_syntax(data))
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
		if ((input && !input[0]))
		{
			cleanup_and_continue(data);
			continue ;
		}
		if (!process_input(data))
		{
			data->status = 1;
			cleanup_and_continue(data);
			continue ;
		}
		signals_heredoc();
		if (heredoc_check(data))
		{
			signals_exec();
			exec_cmds(data->cmd);
		}
		cleanup_and_continue(data);
		data->cmd = NULL;
	}
}
