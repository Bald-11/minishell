/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:38:38 by yabarhda          #+#    #+#             */
/*   Updated: 2025/05/05 17:50:25 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

static void	exec_b1_helper(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "cd"))
		ft_cd(cmd, cmd->args[1]);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		ft_exit(cmd);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		ft_unset(cmd);
	else if (!ft_strcmp(cmd->args[0], "export") && cmd->args[1])
		ft_export(cmd);
}

void	exec_b1(t_cmd *cmd)
{
	pid_t (pid);
	pid = fork();
	if (!pid)
	{
		check_in(cmd, -1);
		check_out(cmd, -1);
		if (cmd->out != 1)
		{
			dup2(cmd->out, 1);
			close(cmd->out);
		}
		if (!ft_strcmp(cmd->args[0], "echo"))
			ft_echo(cmd);
		else if (!ft_strcmp(cmd->args[0], "pwd"))
			ft_pwd(cmd);
		else if (!ft_strcmp(cmd->args[0], "env"))
			ft_env(cmd->data->env);
		else if (!ft_strcmp(cmd->args[0], "export") && !cmd->args[1])
			ft_export(cmd);
		exit(0);
	}
	waitpid(pid, &cmd->data->status, 0);
	set_exit_status(cmd->data);
	if (!cmd->data->status)
		exec_b1_helper(cmd);
}

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
	if (!cmd->args[0])
		free_n_exit(cmd, 0);
	if (execve(filename(cmd->args[0], data), cmd->args, data->envp) == -1)
	{
		if (errno == 2)
			(print_error(cmd->args[0], 1), free_n_exit(cmd, 127));
		else
			(print_error(cmd->args[0], 2), free_n_exit(cmd, 126));
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
	if (!cmd->args[0])
		free_n_exit(cmd, 0);
	if (isbuiltin(cmd->args[0]))
		(exec_b(cmd), exit(data->status));
	else
	{
		if (execve(filename(cmd->args[0], data), cmd->args, data->envp) == -1)
		{
			if (errno == 2)
				(print_error(cmd->args[0], 1), free_n_exit(cmd, 127));
			else
				(print_error(cmd->args[0], 2), free_n_exit(cmd, 126));
		}
	}
}

void	multi_cmd_handle(t_cmd *cmd)
{
	int (i);
	t_cmd *(tmp);
	tmp = cmd;
	i = 0;
	cmd->data->pid = (pid_t *)malloc(cmd->data->cc * sizeof(pid_t));
	if (!cmd->data->pid)
		return (ft_printf("minishell: malloc error\n"), (void)0);
	open_pipes(cmd);
	while (i < cmd->data->cc)
	{
		cmd->data->pid[i] = fork();
		if (cmd->data->pid[i] == -1)
			free_n_exit(cmd, 1);
		if (cmd->data->pid[i] == 0)
			execute(tmp, cmd->data, i);
		tmp = tmp->next;
		i++;
	}
	close_all_pipes(cmd->data);
	i = 0;
	while (i < cmd->data->cc && waitpid(cmd->data->pid[i], \
		&cmd->data->status, 0) > 0)
		i++;
	set_exit_status(cmd->data);
}

void	exec_cmds(t_cmd *cmd)
{
	pid_t (pid);
	cmd->data->cc = count_cmds(cmd);
	if (cmd->data->cc == 1)
	{
		if (isbuiltin(cmd->args[0]))
			exec_b1(cmd);
		else
		{
			pid = fork();
			if (!pid)
			{
				check_in(cmd, -1);
				check_out(cmd, -1);
				exec_c(cmd, cmd->data);
			}
			waitpid(pid, &cmd->data->status, 0);
			set_exit_status(cmd->data);
		}
	}
	else
		multi_cmd_handle(cmd);
}
