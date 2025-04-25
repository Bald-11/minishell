/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:32:37 by yabarhda          #+#    #+#             */
/*   Updated: 2025/04/25 16:26:20 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	exec_b(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "cd"))
		ft_cd(cmd->args[1]);
	else if (!ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd->args);
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

void	exit_shell(t_cmd *cmd)
{
	long (exit_status);
	exit_status = cmd->data->status;
	free_env(cmd->data->env);
	free_cmds(cmd);
	exit((unsigned char)exit_status);
}
