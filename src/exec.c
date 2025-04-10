/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 08:22:11 by yabarhda          #+#    #+#             */
/*   Updated: 2025/04/10 13:08:30 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	exec_c(t_cmd *cmd, t_data *data)
{
	if (cmd->in != 0)
	{
		dup2(cmd->in, 0);
		close(cmd->in);
	}
	if (cmd->out != 1)
	{
		dup2(cmd->out, 1);
		close(cmd->out);
	}
	if (execve(filename(cmd->args[0], data), cmd->args, data->env) == -1)
	{
		if (errno == 2)
			(print_error(cmd->args[0], 1), free_n_exit(cmd, 127));
		else
			(print_error(cmd->args[0], 2), free_n_exit(cmd, 126));
	}
}

void	open_pipes(t_cmd *cmd)
{
	int (i);
	i = 0;
	cmd->data->pipe = (int **)malloc(sizeof(int *) * (cmd->data->cc - 1));
	if (!cmd->data->pipe)
		return ;
	while (i < (cmd->data->cc - 1))
	{
		cmd->data->pipe[i] = (int *)malloc(sizeof(int) * 2);
		if (!cmd->data->pipe[i] || pipe(cmd->data->pipe[i]) == -1)
			free_n_exit(cmd, 1);
		i++;
	}
}

void	execute(t_cmd *cmd, t_data *data, int i)
{
	check_in(cmd, i);
	check_out(cmd, i);
	if (cmd->in != 0)
		(dup2(cmd->in, 0), close(cmd->in));
	if (cmd->out != 1)
		(dup2(cmd->out, 1), close(cmd->out));
	close_all_pipes(data);
	if (isbuiltin(cmd->args[0]))
		(exec_b(cmd), exit(1));
	else
	{
		if (execve(filename(cmd->args[0], data), cmd->args, data->env) == -1)
		{
			if (errno == 2)
				(print_error(cmd->args[0], 1), free_n_exit(cmd, 127));
			else
				(print_error(cmd->args[0], 2), free_n_exit(cmd, 126));
		}
	}
}

void	multi_cmd_handle(t_cmd *cmd, t_data *data)
{
	int (i);
	t_cmd *(tmp);
	tmp = cmd;
	i = 0;
	data->pid = (pid_t *)malloc(data->cc * sizeof(pid_t));
	if (!data->pid)
		return (printf("minishell: fork error\n"), (void)0);
	open_pipes(cmd);
	while (i < data->cc)
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			free_n_exit(cmd, 1);
		if (data->pid[i] == 0)
			execute(tmp, data, i);
		tmp = tmp->next;
		i++;
	}
	close_all_pipes(data);
	i = 0;
	while (i < data->cc && waitpid(data->pid[i], &data->status, 0) > 0)
		i++;
	set_exit_status(data);
}

int	exec_cmds(t_cmd *cmd, t_data *data)
{
	pid_t (pid);
	data->cc = count_cmds(cmd);
	if (data->cc == 1)
	{
		if (isbuiltin(cmd->args[0]))
			exec_b(cmd);
		else
		{
			pid = fork();
			if (!pid)
			{
				check_in(cmd, -1);
				check_out(cmd, -1);
				exec_c(cmd, data);
			}
			waitpid(pid, &data->status, 0);
			set_exit_status(data);
		}
	}
	else
		multi_cmd_handle(cmd, data);
	return (0);
}
