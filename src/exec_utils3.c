/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:32:37 by yabarhda          #+#    #+#             */
/*   Updated: 2025/05/02 11:27:57 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	exec_b(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "cd"))
		ft_cd_m(cmd, cmd->args[1]);
	else if (!ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		ft_pwd(cmd);
	/*I got a error here
	else if (!ft_strcmp(cmd->args[0], "export"))
		export(cmd->args, data);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		unset(cmd->args, data);
	I got a error here*/
	else if (!ft_strcmp(cmd->args[0], "env"))
		ft_env(cmd->data);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		ft_exit(cmd);
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
		exit(0);
	}
	waitpid(pid, &cmd->data->status, 0);
	set_exit_status(cmd->data);
	if (!cmd->data->status)
	{
		if (!ft_strcmp(cmd->args[0], "cd"))
			ft_cd(cmd, cmd->args[1]);
		else if (!ft_strcmp(cmd->args[0], "exit"))
			ft_exit(cmd);
	}
	/*I got a error here
	else if (!ft_strcmp(cmd->args[0], "export"))
		export(cmd->args, data);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		unset(cmd->args, data);
	I got a error here*/
	else if (!ft_strcmp(cmd->args[0], "env"))
		ft_env(cmd->data);
}

void	exit_shell(t_cmd *cmd)
{
	long (exit_status);
	exit_status = cmd->data->status;
	free_env(cmd->data->env);
	free_cmds(cmd);
	exit((unsigned char)exit_status);
}
