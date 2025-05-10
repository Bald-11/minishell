/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:58:17 by yabarhda          #+#    #+#             */
/*   Updated: 2025/05/10 11:41:05 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include "../../inc/utils.h"
#include "../../inc/env.h"
#include "../../inc/shell.h"

void	ft_cd(t_cmd *cmd, char *path)
{
	if (!cmd->args[1])
	{
		path = ft_getenv("HOME", cmd->data->env);
		if (!path)
		{
			ft_printf("minishell: cd: HOME not set\n");
			cmd->data->status = 1;
			return ;
		}
	}
	update_env(&cmd->data->env, "OLDPWD");
	cmd->data->status = 0;
	if (chdir(path) == -1)
	{
		ft_printf("minishell: cd: %s: No such file or directory\n", path);
		cmd->data->status = 1;
	}
	update_env(&cmd->data->env, "PWD");
	cmd->data->envp = ft_envp(cmd->data->env);
}

void	ft_echo(t_cmd *cmd)
{
	int (n_flag), i = 1;
	n_flag = is_valid_flag(cmd->args[i]);
	if (!n_flag)
		while (!is_valid_flag(cmd->args[++i]))
			;
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (n_flag)
		printf("\n");
}

void	ft_pwd(t_cmd *cmd)
{
	char *(cwd);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
		cmd->data->status = 0;
	}
	else
	{
		perror("minishell: pwd");
		cmd->data->status = 1;
	}
}

void	update_env_node(t_env *env, char *key, char *value)
{
	int (v_len);
	v_len = ft_strlen(key);
	while (env)
	{
		if (!ft_strncmp(env->key, key, v_len))
		{
			env->value = value;
			return ;
		}
		env = env->next;
	}
}

void	ft_exit(t_cmd *cmd)
{
	int (i);
	i = 0;
	while (cmd->args[i])
		i++;
	ft_printf("exit\n");
	if (cmd->args[1])
	{
		if (!ft_exit_input(cmd->args[1], &cmd->data->status))
			exit_shell(cmd);
		if (i > 2)
		{
			ft_printf("minishell: exit: too many arguments\n");
			cmd->data->status = 1;
			return ;
		}
	}
	exit_shell(cmd);
}
