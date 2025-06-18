/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:55:59 by yabarhda          #+#    #+#             */
/*   Updated: 2025/06/18 18:21:34 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/env.h"
#include "../inc/utils.h"
#include "../inc/shell.h"
#include "../inc/input.h"

void	init_data(t_data *data, char **envp)
{
	data->status = 0;
	data->cc = 0;
	data->heredoc_f = 0;
	data->pipe = NULL;
	data->pid = NULL;
	data->env = init_env(envp);
	data->envp = ft_envp(data->env);
	data->cmd = NULL;
	data->token = NULL;
	data->redir = NULL;
	data->input = NULL;
}

void	free_data(void)
{
	ft_malloc(0, 0);
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		exit_status;

	(void)argc;
	(void)argv;
	data = ft_malloc(sizeof(t_data), 1337);
	init_data(data, envp);
	minishell(data);
	exit_status = data->status;
	free_data(); // unfinished
	return ((unsigned char)exit_status);
}
