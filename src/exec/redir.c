/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:47:00 by yabarhda          #+#    #+#             */
/*   Updated: 2025/07/20 09:53:07 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include "../../inc/shell.h"
#include "../../inc/utils.h"

#include <sys/stat.h>

char	*filename(char *cmd, t_data *data)
{
	char *(path), *(c_path);
	char **(arr);
	int (i);
	struct stat b;
	i = -1;
	if (!ft_strchr_ex(cmd, '/'))
		return (cmd);
	path = ft_getenv("PATH", data->env);
	if (!path)
		return (cmd);
	arr = ft_split(path, ':');
	while (arr[++i])
	{
		c_path = ft_strjoin_ex(arr[i], cmd);
		stat(c_path, &b);
		if (!access(c_path, F_OK) && !S_ISDIR(b.st_mode))
		{
			if (!access(c_path, X_OK))
				return (c_path);
			else
				(print_error(cmd, 2), free_n_exit(126, data->input));
		}
	}
	(print_error(cmd, 1), free_n_exit(127, data->input));
	return (NULL);
}

void	check_in(t_cmd *cmd, int index)
{
	t_redir *(tmp);
	int (tmp_fd);
	tmp_fd = -1;
	tmp = cmd->redir;
	while (tmp)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_HEREDOC)
		{
			if (tmp_fd != -1)
				close(tmp_fd);
			tmp_fd = open(tmp->file, O_RDONLY);
			if (tmp_fd == -1)
				(check_access(tmp->file), free_n_exit(1, cmd->data->input));
		}
		tmp = tmp->next;
	}
	if (tmp_fd != -1)
		cmd->in = tmp_fd;
	else if (index != 0 && index != -1)
		cmd->in = cmd->data->pipe[index - 1][0];
}

void	check_out(t_cmd *cmd, int index)
{
	t_redir *(tmp);
	int (tmp_fd);
	tmp_fd = -1;
	tmp = cmd->redir;
	while (tmp)
	{
		if (tmp->type == REDIR_OUT || tmp->type == REDIR_APPEND)
		{
			if (tmp_fd != -1)
				close(tmp_fd);
			if (tmp->type == REDIR_OUT)
				tmp_fd = open(tmp->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			else if (tmp->type == REDIR_APPEND)
				tmp_fd = open(tmp->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (tmp_fd == -1)
				(check_access(tmp->file), free_n_exit(1, cmd->data->input));
		}
		tmp = tmp->next;
	}
	if (tmp_fd != -1)
		cmd->out = tmp_fd;
	else if (index != -1 && index != cmd->data->cc - 1)
		cmd->out = cmd->data->pipe[index][1];
}
