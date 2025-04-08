/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:31:00 by yabarhda          #+#    #+#             */
/*   Updated: 2025/04/08 13:42:20 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"


void	cd(char *path)
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

void	echo(char **args)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (args[1] && !ft_strcmp(args[1], "-n"))
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
}

void	pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
}



void	env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
}

void	exit_shell(char **args, t_data *data)
{
	int	exit_code;

	if (!args[1])
		exit_code = 0;
	else
	{
		exit_code = atoi(args[1]);
		if (exit_code < 0 || exit_code > 255)
		{
			printf("minishell: exit: %s: numeric argument required\n", args[1]);
			exit_code = 255;
		}
	}
	printf("exit\n");
	free_env(data->env);
	exit(exit_code);
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
	{
		printf("logout\n");
		exit(0);
	}
	return (0);
}
