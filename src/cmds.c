/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:42:53 by yabarhda          #+#    #+#             */
/*   Updated: 2025/03/23 14:18:29 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	free_cmds(t_cmd *cmd)
{
	t_cmd *(temp);
	int (i);
	while (cmd)
	{
		i = 0;
		temp = cmd;
		cmd = cmd->next;
		while (temp->args)
			free(temp->args[i++]);
		free(temp->args);
		free(temp->input_file);
		free(temp->output_file);
		free(temp->heredoc_delim);
		free(temp);
	}
}

t_cmd	*create_cmd(t_token_type type, char *value)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	token->type = type;
	token->value = strdup(value);
	if (!token->value)
	{
		free(token);
		return (NULL);
	}
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!new_token)
	{
		if (*head)
			free_tokens(*head);
		return ;
	}
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}
