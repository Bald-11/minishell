/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:55:59 by mbarrah           #+#    #+#             */
/*   Updated: 2025/05/05 17:55:39 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/shell.h"

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
}

void	free_data(t_data *data)
{
	if (data->env)
		free_env(data->env);
	if (data->cmd)
		free_all_cmds(data->cmd);
	if (data->token)
		free_tokens(data->token);
	free(data);
	unlink("/tmp/minishell.txt");
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	init_data(data, envp);
	minishell(data);
	free_data(data);
	return (data->status);
}
