/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:00:37 by yabarhda          #+#    #+#             */
/*   Updated: 2025/05/06 16:01:18 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"

void	execute(t_cmd *cmd, t_data *data, int i)
{
	check_in(cmd, i);
	check_out(cmd, i);
	if (cmd->in != 0)
		(dup2(cmd->in, 0), close(cmd->in));
	if (cmd->out != 1)
		(dup2(cmd->out, 1), close(cmd->out));
	close_all_pipes(data);
	if (!cmd->args[0])
		free_n_exit(0);
	if (isbuiltin(cmd->args[0]))
		(exec_b(cmd), exit(data->status));
	else
	{
		if (execve(filename(cmd->args[0], data), cmd->args, data->envp) == -1)
		{
			if (errno == 2)
				(print_error(cmd->args[0], 1), free_n_exit(127));
			else
				(print_error(cmd->args[0], 2), free_n_exit(126));
		}
	}
}
