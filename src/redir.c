/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:16:47 by yabarhda          #+#    #+#             */
/*   Updated: 2025/04/05 08:15:30 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

t_redir	*create_redir(t_redir_type type, char *file)
{
	t_redir *(redir);
	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	if (!redir->file)
		return (free(redir), NULL);
	redir->next = NULL;
	return (redir);
}

int	add_redir(t_cmd *cmd, t_redir_type type, char *file)
{
	t_redir *(redir), *(last);
	redir = create_redir(type, file);
	if (!redir)
		return (0);
	if (!cmd->redir)
		cmd->redir = redir;
	else
	{
		last = cmd->redir;
		while (last->next)
			last = last->next;
		last->next = redir;
	}
	return (1);
}
