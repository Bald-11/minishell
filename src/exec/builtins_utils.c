/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:13:54 by yabarhda          #+#    #+#             */
/*   Updated: 2025/07/20 11:37:33 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include "../../inc/shell.h"
#include "../../inc/utils.h"
#include "../../inc/env.h"

void	update_env(t_env **head, char *value)
{
	t_env *(tmp);
	char	*cwd;
	
	tmp = *head;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	if (!tmp)
	{
		add_env_node(head, new_env_node(ft_strdup(value), ft_strdup(cwd)));
		free(cwd);
		return ;
	}
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, value))
		{
			tmp->value = ft_strdup(cwd);
			break ;
		}
		else if (!tmp->next)
		{
			add_env_node(head, new_env_node(ft_strdup(value), ft_strdup(cwd)));
			break ;
		}
		tmp = tmp->next;
	}
	free(cwd);
}

int	is_valid_flag(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	if (s[i] != '-')
		return (1);
	while (s[++i])
	{
		if (s[i] != 'n')
			return (1);
	}
	return (0);
}

void	exec_b(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->args[0], "cd"))
		ft_cd(cmd, cmd->args[1]);
	else if (!ft_strcmp(cmd->args[0], "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		ft_pwd(cmd);
	else if (!ft_strcmp(cmd->args[0], "export"))
		ft_export(cmd);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		ft_unset(cmd);
	else if (!ft_strcmp(cmd->args[0], "env"))
		ft_env(cmd->data->env);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		ft_exit(cmd, 1337);
}

int	ft_exit_input(char *s, int *status)
{
	int (i), f = 0;
	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
		{
			f = 1;
			break ;
		}
		i++;
	}
	ft_strtol(s);
	if ((errno == ERANGE) || f)
	{
		printf("minishell: exit: %s: numeric argument required\n", s);
		*status = 2;
		return (0);
	}
	*status = ft_atoi(s);
	return (1);
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
