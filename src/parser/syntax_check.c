/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:56:35 by mbarrah           #+#    #+#             */
/*   Updated: 2025/07/17 18:44:32 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/shell.h"
#include "../../inc/utils.h"

static int	is_redirection(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT ||
			type == T_APPEND || type == T_HEREDOC);
}

static int	check_redir_no_next(t_token *current)
{
	if (!current->next)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	return (1);
}

static int	check_redir_invalid_next(t_env *env, t_token *current)
{
	if (is_redirection(current->next->type))
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
			current->next->value);
		return (0);
	}
	if (current->next->type == T_PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	if (ft_strchr(current->next->value, '$') && !ft_getenv(&current->next->value[1], env) && current->type != T_HEREDOC)
	{
		printf("minishell: %s: ambiguous redirect\n", current->next->value);
		return (0);		
	}
	return (1);
}

int	check_pipe_syntax(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == T_PIPE)
		{
			if (!current->next)
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				return (0);
			}
			if (current->next->type == T_PIPE)
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}

int	check_redirection_syntax(t_data *data, t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (is_redirection(current->type))
		{
			if (!check_redir_no_next(current))
				return (0);
			if (!check_redir_invalid_next(data->env, current))
				return (0);
		}
		current = current->next;
	}
	return (1);
}

int	check_syntax(t_data *data)
{
	if (!data->token)
		return (1);
	if (!check_redirection_syntax(data, data->token))
		return (0);
	if (!check_pipe_syntax(data->token))
		return (0);
	return (1);
}