/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 08:22:11 by yabarhda          #+#    #+#             */
/*   Updated: 2025/04/05 11:48:26 by yabarhda         ###   ########.fr       */
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

char	*filename(char *cmd)
{
	char *(path), *(c_path);
	char **(arr);
	int (i);
	i = -1;
	if (!ft_strchr_ex(cmd, '/'))
		return (cmd);
	path = getenv("PATH");
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

void	exec_c(t_cmd *cmd, char *envp[])
{
	if (isbuiltin(cmd->args[0]))
	{
		// do something here
		printf("do something here\n"), exit(0);
	}
	else
	{
		if (execve(filename(cmd->args[0]), cmd->args, envp) == -1)
			printf("minishell: command not found: %s\n", cmd->args[0]), exit(1);
	}
}

void	exec_b(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "saf"))
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

int	exec_cmds(t_cmd *cmd, char *envp[])
{
	int (cmd_count);//, i = 0;
	pid_t (pid);
	cmd_count = count_cmds(cmd);
	/* if (cmd_count > 1)
		return (0); */
	/* pid = (pid_t *)malloc(cmd_count * sizeof(pid_t));
	if (!pid)
		return (0); */
	/* while (i < cmd_count)
	{
		pid[i] = fork();
		// add a check if fork fails, free and return.
		if (!pid[i])
		i++;
	} */
	if (cmd_count == 1)
	{
		if (isbuiltin(cmd->args[0]))
			exec_b(cmd);
		else
		{
			pid = fork();
			if (!pid)
				exec_c(cmd, envp);
			waitpid(pid, 0, 0);
		}
	}
	// printf("CMD COUNT: %d\n", cmd_count);
	return (0);
}
