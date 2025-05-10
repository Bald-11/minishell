/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:26:48 by yabarhda          #+#    #+#             */
/*   Updated: 2025/05/09 13:34:48 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

static void	print_envp(t_env **env_arr, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		printf("declare -x %s=\"%s\"\n", env_arr[i]->key, env_arr[i]->value);
}

static void	bubble_sort(t_env **env_arr, int count)
{
	t_env *(tmp);
	int (i), j = 0;
	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(env_arr[j]->key, env_arr[j + 1]->key) > 0)
			{
				tmp = env_arr[j];
				env_arr[j] = env_arr[j + 1];
				env_arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}	
}

void	print_sorted_env(t_env *env)
{
	t_env *(tmp), **(env_arr);
	int (i), count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	env_arr = ft_malloc(sizeof(t_env *) * count, 32);
	tmp = env;
	i = 0;
	while (tmp)
	{
		env_arr[i++] = tmp;
		tmp = tmp->next;
	}
	bubble_sort(env_arr, count);
	print_envp(env_arr, count);
}

void	exit_shell(t_cmd *cmd)
{
	int (exit_status);
	exit_status = cmd->data->status;
	ft_malloc(0, 0);
	exit((unsigned char)exit_status);
}
