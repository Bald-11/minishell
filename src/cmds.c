/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:42:53 by yabarhda          #+#    #+#             */
/*   Updated: 2025/04/05 18:04:18 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	free_cmds(t_cmd *cmd)
{
	t_cmd *(temp);
	t_redir *(redir);
	int (i);
	while (cmd)
	{
		i = 0;
		temp = cmd->next;
		if (cmd->args)
		{
			while (cmd->args[i])
				free(cmd->args[i++]);
			free(cmd->args);
		}
		while (cmd->redir)
		{
			redir = cmd->redir;
			cmd->redir = cmd->redir->next;
			free(redir->file);
			free(redir);
		}
		free(cmd);
		cmd = temp;
	}
}

t_cmd	*create_cmd(t_data *data)
{
	t_cmd *(cmd);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = malloc(sizeof(char *));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	cmd->args[0] = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	cmd->data = data;
	cmd->in = 0;
	cmd->out = 1;
	return (cmd);
}

int	add_arg_to_cmd(t_cmd *cmd, char *arg)
{
	int (i), j = -1;
	char **(new_args);
	i = 0;
	while (cmd->args && cmd->args[i])
		i++;
	new_args = (char **)malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (0);
	while (cmd->args && ++j < i)
		new_args[j] = cmd->args[j];
	new_args[i] = ft_strdup(arg);
	if (!new_args[i])
	{
		free(new_args);
		return (0);
	}
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	return (1);
}
