/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:28:19 by yabarhda          #+#    #+#             */
/*   Updated: 2025/04/06 18:19:03 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

int	init_data(t_data *data, char *envp[])
{
	int (i);
	i = 0;
	data->status = 0;
	data->pid = NULL;
	data->cc = 0;
	while (envp[i])
		i++;
	data->env = (char **)malloc((i + 1) * sizeof(char *));
	if (!data->env)
		return (0);
	i = 0;
	while (envp[i])
	{
		data->env[i] = ft_strdup(envp[i]);
		if (!data->env[i])
			return (0);
		i++;
	}
	data->env[i] = NULL;
	return (1);
}

void	free_env(char **env)
{
	int (i);
	i = 0;
	if (!env)
		return ;
	while (env[i])
		free(env[i++]);
	free(env);
}

int	main(int ac, char *av[], char *envp[])
{
	(void)ac;
	(void)av;
	t_data (data);
	if (!init_data(&data, envp))
		return (free_env(data.env), 1);
	shell_loop(&data);
	free_env(data.env);
	rl_clear_history();
	return (0);
}
