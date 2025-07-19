/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:14:18 by yabarhda          #+#    #+#             */
/*   Updated: 2025/07/19 16:58:09 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"
#include "../../inc/env.h"
#include "../../inc/exec.h"
#include "../../inc/parser.h"
#include "../../inc/shell.h"

static void	string_check(t_cmd *cmd, int i, int j, int *f)
{
	while (cmd->args[i][j])
	{
		if (!is_env_char(cmd->args[i][j]))
		{
			if (j != 0 && cmd->args[i][j] == '=')
			{
				cmd->args[i][j] = '\0';
				if (!ft_getenv(cmd->args[i], cmd->data->env))
					add_env_node(&cmd->data->env, new_env_node \
					(ft_strdup(cmd->args[i]), ft_strdup(&cmd->args[i][j + 1])));
				else
					update_env_node(cmd->data->env, cmd->args[i], \
					ft_strdup(&cmd->args[i][j + 1]));
			}
			else
			{
				print_error(cmd->args[i], 6);
				cmd->data->status = 1;
				*f = 1;
			}
			break ;
		}
		j++;
	}	
}

void	ft_export(t_cmd *cmd)
{
	int (i), j = 0, f = 0;
	i = 1;
	if (!cmd->args[1] || !cmd->args[1][0])
		return (print_sorted_env(cmd->data->env), (void)0);
	while (cmd->args[i])
	{
		if (!((cmd->args[i][0] >= 'A' && cmd->args[i][0] <= 'Z') ||
			(cmd->args[i][0] >= 'a' && cmd->args[i][0] <= 'z') ||
			(cmd->args[i][0] == '_')))
		{
			print_error(cmd->args[i], 6);
			i++;
			f = 1;
			cmd->data->status = 1;
			continue ;
		}
		string_check(cmd, i, j, &f);
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
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
