/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:31:29 by yabarhda          #+#    #+#             */
/*   Updated: 2025/03/24 20:58:08 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

t_cmd	*finalize_cmds(t_cmd *cmd, t_cmd **head)
{
	if (cmd)
		add_cmd(cmd, head);
	return (*head);
}

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

t_cmd	*handle_pipe_token(t_token *token, t_cmd *cmd, t_cmd **head)
{
	if (!token->next || token->next->type != T_ARG)
	{
		printf("minishell: syntax error\n");
		if (*head)
			free_cmds(*head);
		return (NULL);
	}
	add_cmd(cmd, head);
	return (init_cmd(head));
}

int	process_token(t_token **token_og, t_cmd **cmd, t_cmd **head)
{
	t_token *(token);
	int (result);
	token = *token_og;
	if (token->type == T_ARG)
		return (handle_arg_token(*cmd, token->value, head));
	else if (token->type == T_PIPE)
	{
		*cmd = handle_pipe_token(token, *cmd, head);
		return (*cmd != NULL);
	}
	else if (token->type == T_REDIR_OUT || token->type == T_APPEND
		|| token->type == T_REDIR_IN || token->type == T_HEREDOC)
	{
		result = handle_redirection(*cmd, token, head);
		if (result)
			*token_og = token->next;
		return (result);
	}
	return (1);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd *(head), *(cmd);
	head = NULL;
	cmd = NULL;
	if (tokens && tokens->type == T_PIPE)
		return (printf("minishell: syntax error\n"), NULL);
	while (tokens && tokens->type != T_EOF)
	{
		if (!cmd)
		{
			cmd = init_cmd(&head);
			if (!cmd)
				return (NULL);
		}
		if (!process_token(&tokens, &cmd, &head))
			return (NULL);
		tokens = tokens->next;
	}
	return (finalize_cmds(cmd, &head));
}
