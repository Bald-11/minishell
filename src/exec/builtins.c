/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:58:17 by yabarhda          #+#    #+#             */
/*   Updated: 2025/05/05 17:19:01 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

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
	free_arr(cmd->data->envp);
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

void	ft_export(t_cmd *cmd)
{
	if (!cmd->args[1] || !cmd->args[1][0])
	{
		print_sorted_env(cmd->data->env);
		return;
	}
	int i = 1;
	int j = 0;
	int f = 0;
	while (cmd->args[i])
	{
		j = 0;
		if (!((cmd->args[i][0] >= 'A' && cmd->args[i][0] <= 'Z') || (cmd->args[i][0] == '_')))
		{
			ft_printf("minishell: export: `%s': not a valid identifier\n", cmd->args[i]);
			i++;
			cmd->data->status = 1;
			f = 1;
			continue;
		}
		while (cmd->args[i][j])
		{
			if (!is_env_char(cmd->args[i][j]))
			{
				if (j != 0 && cmd->args[i][j] == '=')
					add_env_node(&cmd->data->env, new_env_node(ft_strdup(cmd->args[i]), ft_strdup(&cmd->args[i][j+1])));
				else
				{
					ft_printf("minishell: export: `%s': not a valid identifier\n", cmd->args[i]);
					cmd->data->status = 1;
					f = 1;
				}
				break ;
			}
			j++;
		}
		i++;
	}
	if (!f)
		cmd->data->status = 0;
}

void	ft_unset(t_cmd *cmd)
{
	int		i;

	i = 1;
	if (cmd->args[i])
	{
		while (cmd->args[i])
		{
			ft_popnode(&cmd->data->env, cmd->args[i]);
			i++;
		}
		free_arr(cmd->data->envp);
		cmd->data->envp = ft_envp(cmd->data->env);
	}
	cmd->data->status = 0;
}

void	ft_env(t_env *env)
{
	t_env *(tmp);
	tmp = env;
	while (tmp)
	{
		printf("%s = %s\n", tmp->key, tmp->value);
		tmp = tmp->next;
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
