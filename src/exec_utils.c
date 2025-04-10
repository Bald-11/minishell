/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:33:50 by yabarhda          #+#    #+#             */
/*   Updated: 2025/04/10 13:08:12 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	free_n_exit(t_cmd *cmd, int status)
{
	if (cmd->in != 0)
		close(cmd->in);
	if (cmd->out != 1)
		close(cmd->out);
	if (cmd->data->pid)
		free(cmd->data->pid);
	free_env(cmd->data->env);
	free_cmds(cmd);
	exit(status);
}

int	count_cmds(t_cmd *cmd)
{
	t_cmd *(tmp) = cmd;
	tmp = cmd;
	int (count);
	count = 1;
	while (tmp->next)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

char	*filename(char *cmd, t_data *data)
{
	char *(path), *(c_path);
	char **(arr);
	int (i);
	i = -1;
	if (!ft_strchr_ex(cmd, '/'))
		return (cmd);
	path = ft_getenv("PATH", data->env);
	if (!path)
		return (cmd);
	arr = ft_split(path, ':');
	if (!arr)
		return (cmd);
	while (arr[++i])
	{
		c_path = ft_strjoin_ex(arr[i], cmd);
		if (!access(c_path, F_OK))
			return (c_path);
		free(c_path);
	}
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (cmd);
}

void	check_access(char *file)
{
	if (access(file, F_OK) == -1)
		print_error(file, 3);
	else if (access(file, W_OK) == -1)
		print_error(file, 2);
}

void	close_all_pipes(t_data *data)
{
	int (i);
	i = -1;
	while (++i < (data->cc - 1))
	{
		close(data->pipe[i][0]);
		close(data->pipe[i][1]);
	}
}
