/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:11:02 by yabarhda          #+#    #+#             */
/*   Updated: 2025/05/06 14:54:35 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

void	open_pipes(t_cmd *cmd)
{
	int (i);
	i = 0;
	cmd->data->pipe = (int **)ft_malloc(sizeof(int *) * (cmd->data->cc - 1), 1);
	while (i < (cmd->data->cc - 1))
	{
		cmd->data->pipe[i] = (int *)ft_malloc(sizeof(int) * 2, 2);
		if (pipe(cmd->data->pipe[i]) == -1)
			free_n_exit(1);
		i++;
	}
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

void	set_exit_status(t_data *data)
{
	int (temp);
	if (WIFEXITED(data->status))
	{
		temp = WEXITSTATUS(data->status);
		data->status = temp;
	}
	else if (WIFSIGNALED(data->status))
	{
		temp = WTERMSIG(data->status);
		data->status = temp;
	}
}
