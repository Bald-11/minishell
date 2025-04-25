/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:31:00 by yabarhda          #+#    #+#             */
/*   Updated: 2025/04/25 16:30:57 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	ft_cd(char *path)
{
	char	*home;

	if (!path)
	{
		home = getenv("HOME");
		if (!home)
		{
			printf("cd: HOME not set\n");
			return ;
		}
		path = home;
	}
	if (chdir(path) == -1)
		printf("cd: no such file or directory: %s\n", path);
}

void	ft_pwd(t_cmd *cmd)
{
	char *(cwd);
	pid_t (pid);
	pid = fork();
	if (!pid)
	{
		check_out(cmd, -1);
		cwd = getcwd(NULL, 0);
		if (cwd)
		{
			write(cmd->out, cwd, ft_strlen(cwd));
			write(cmd->out, "\n", 1);
			free(cwd);
		}
		exit(0);
	}
	wait(NULL);
}

void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
}

int	isbuiltin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}
