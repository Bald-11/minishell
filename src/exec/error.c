/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:30:05 by yabarhda          #+#    #+#             */
/*   Updated: 2025/05/05 15:05:23 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

void	free_n_exit(t_cmd *cmd, int status)
{
	if (cmd->in != 0)
		close(cmd->in);
	if (cmd->out != 1)
		close(cmd->out);
	if (cmd->data->pid)
		free(cmd->data->pid);
	free_arr(cmd->data->envp);
	free_all_cmds(cmd);
	exit(status);
}

void	print_error(char *str, int err)
{
	if (err == 0)
		perror(str);
	else
	{
		ft_printf("minishell: ");
		if (err == 1)
			ft_printf("command not found");
		else if (err == 2)
			ft_printf("permission denied");
		else if (err == 3)
			ft_printf("no such file or directory");
		ft_printf(": %s\n", str);
	}
}
