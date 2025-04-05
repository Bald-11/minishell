/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:39:18 by yabarhda          #+#    #+#             */
/*   Updated: 2025/04/05 08:16:09 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

t_cmd	*init_cmd(t_cmd **head)
{
	t_cmd *(cmd), *(last);
	cmd = create_cmd();
	if (!cmd)
	{
		if (*head)
			free_cmds(*head);
		return (NULL);
	}
	if (!(*head))
		*head = cmd;
	else if (cmd != *head)
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = cmd;
	}
	return (cmd);
}

int	handle_redirection(t_cmd *cmd, t_token *token)
{
	int (redir_type);
	redir_type = 0;
	if (token->next->type != T_ARG)
		return (printf("minishell: syntax error\n"), 0);
	if (token->type == T_REDIR_OUT)
		redir_type = REDIR_OUT;
	else if (token->type == T_APPEND)
		redir_type = REDIR_APPEND;
	else if (token->type == T_REDIR_IN)
		redir_type = REDIR_IN;
	else if (token->type == T_HEREDOC)
		redir_type = REDIR_HEREDOC;
	if (!add_redir(cmd, redir_type, token->next->value))
		return (0);
	return (1);
}
