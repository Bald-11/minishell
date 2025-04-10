/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:31:29 by yabarhda          #+#    #+#             */
/*   Updated: 2025/04/10 13:09:27 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

int	handle_arg_token(t_cmd *cmd, char *value, t_cmd **head)
{
	if (!add_arg_to_cmd(cmd, value))
	{
		if (*head)
			free_cmds(*head);
		return (0);
	}
	return (1);
}

t_cmd	*handle_pipe_token(t_token *token, t_cmd **head, t_data *data)
{
	if (token->next->type == T_PIPE || token->next->type == T_EOF)
	{
		printf("minishell: syntax error\n");
		if (*head)
			free_cmds(*head);
		return (NULL);
	}
	return (init_cmd(head, data));
}

int	process_token(t_token **token_og, t_cmd **cmd, t_cmd **head, t_data *data)
{
	t_token *(token);
	int (result);
	token = *token_og;
	if (token->type == T_ARG)
		return (handle_arg_token(*cmd, token->value, head));
	else if (token->type == T_PIPE)
	{
		*cmd = handle_pipe_token(token, head, data);
		return (*cmd != NULL);
	}
	else if (token->type == T_REDIR_OUT || token->type == T_APPEND
		|| token->type == T_REDIR_IN || token->type == T_HEREDOC)
	{
		result = handle_redirection(*cmd, token);
		if (!result)
			free_cmds(*head);
		else
			*token_og = token->next;
		return (result);
	}
	return (1);
}

t_cmd	*parse_tokens(t_token *token, t_data *data)
{
	t_cmd *(head), *(cmd);
	head = NULL;
	cmd = NULL;
	if (token && token->type == T_PIPE)
		return (printf("minishell: syntax error\n"), NULL);
	cmd = init_cmd(&head, data);
	if (!cmd)
		return (NULL);
	while (token && token->type != T_EOF)
	{
		if (!process_token(&token, &cmd, &head, data))
			return (NULL);
		token = token->next;
	}
	return (head);
}
