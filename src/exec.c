/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 08:22:11 by yabarhda          #+#    #+#             */
/*   Updated: 2025/04/05 16:25:20 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

int	count_cmds(t_cmd *cmd)
{
	t_cmd *tmp = cmd;
	int count = 1;
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

void	exec_c(t_cmd *cmd, t_data *data)
{
	/* if (isbuiltin(cmd->args[0]))
	{
		// do something here
		printf("do something here\n"), exit(0);
	}
	else */
	if (1)
	{
		if (execve(filename(cmd->args[0], data), cmd->args, data->env) == -1)
			printf("minishell: command not found: %s\n", cmd->args[0]), exit(1);
	}
}

void	exec_b(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		return ;
	else if (!ft_strcmp(cmd->args[0], "cd"))
		cd(cmd->args[1]);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		return ;
	else if (!ft_strcmp(cmd->args[0], "export"))
		return ;
	else if (!ft_strcmp(cmd->args[0], "unset"))
		return ;
	else if (!ft_strcmp(cmd->args[0], "env"))
		return ((void)1);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		printf("exit\n"), exit(0);
}

void	multi_cmd_handle(t_cmd *cmd, char *envp[], t_data *data)
{
	(void)cmd;
	(void)envp;
	(void)data;
	/* pid_t *(pid);
	pid = (pid_t *)malloc(cmd_count * sizeof(pid_t));
	if (!pid)
		return (0);
	while (i < cmd_count)
	{
		pid[i] = fork();
		// add a check if fork fails, free and return.
		if (!pid[i])
		i++;
	} */
}

int	exec_cmds(t_cmd *cmd, t_data *data)
{
	pid_t (pid);
	data->cmd_count = count_cmds(cmd);
	if (data->cmd_count == 1)
	{
		/* if (isbuiltin(cmd->args[0]))
			exec_b(cmd);
		else */
		if (1)
		{
			pid = fork();
			if (!pid)
				exec_c(cmd, data);
			waitpid(pid, 0, 0);
		}
	}
	else
	{
		multi_cmd_handle(cmd, data->env, data);
	}
	return (0);
}
