/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:38:38 by yabarhda          #+#    #+#             */
/*   Updated: 2025/06/18 18:33:04 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include "../../inc/shell.h"
#include "../../inc/utils.h"
#include "../../inc/signals.h"

static void	exec_b1_helper(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "cd"))
		ft_cd(cmd, cmd->args[1]);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		ft_exit(cmd, 0);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		ft_unset(cmd);
	else if (!ft_strcmp(cmd->args[0], "export") && cmd->args[1])
		ft_export(cmd);
}

void	exec_b1(t_cmd *cmd)
{
	pid_t (pid);
	int (status);
	pid = fork();
	if (!pid)
	{
		signals_child();
		(check_in(cmd, -1), check_out(cmd, -1));
		if (cmd->out != 1)
			(dup2(cmd->out, 1), close(cmd->out));
		if (!ft_strcmp(cmd->args[0], "echo"))
			ft_echo(cmd);
		else if (!ft_strcmp(cmd->args[0], "pwd"))
			ft_pwd(cmd);
		else if (!ft_strcmp(cmd->args[0], "env"))
			ft_env(cmd->data->env);
		else if (!ft_strcmp(cmd->args[0], "export") && !cmd->args[1])
			ft_export(cmd);
		ft_malloc(0, 0);
		exit(0);
	}
	(waitpid(pid, &status, 0), set_exit_status(&status), heredoc_cleanup(cmd));
	if (!status && ft_strcmp(cmd->args[0], "exit"))
		cmd->data->status = status;
	if (!status)
		exec_b1_helper(cmd);
}

void	exec_c(t_cmd *cmd, t_data *data)
{
	if (cmd->in != 0)
		(dup2(cmd->in, 0), close(cmd->in));
	if (cmd->out != 1)
		(dup2(cmd->out, 1), close(cmd->out));
	if (!cmd->args || !cmd->args[0])
		free_n_exit(0, data->input);
	if (execve(filename(cmd->args[0], data), cmd->args, data->envp) == -1)
	{
		if (errno == 2)
			(print_error(cmd->args[0], 1), free_n_exit(127, data->input));
		else
			(print_error(cmd->args[0], 2), free_n_exit(126, data->input));
	}
}

void	multi_cmd_handle(t_cmd *cmd)
{
	int (i);
	t_cmd *(tmp);
	tmp = cmd;
	i = 0;
	cmd->data->pid = (pid_t *)ft_malloc(cmd->data->cc * sizeof(pid_t), 1);
	open_pipes(cmd);
	while (i < cmd->data->cc)
	{
		cmd->data->pid[i] = fork();
		if (cmd->data->pid[i] == -1)
			free_n_exit(1, cmd->data->input);
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
	set_exit_status(&cmd->data->status);
	heredoc_cleanup(cmd);
}

void	exec_cmds(t_cmd *cmd)
{
	pid_t (pid);
	cmd->data->cc = count_cmds(cmd);
	if (cmd->data->cc == 1)
	{
		if (cmd->args && isbuiltin(cmd->args[0]))
			exec_b1(cmd);
		else
		{
			pid = fork();
			if (!pid)
			{
				signals_child();
				(check_in(cmd, -1), check_out(cmd, -1));
				exec_c(cmd, cmd->data);
			}
			waitpid(pid, &cmd->data->status, 0);
			set_exit_status(&cmd->data->status);
			heredoc_cleanup(cmd);
		}
	}
	else
		multi_cmd_handle(cmd);
}
