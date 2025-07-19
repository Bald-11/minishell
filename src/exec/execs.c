/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:00:37 by yabarhda          #+#    #+#             */
/*   Updated: 2025/07/19 17:00:59 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include "../../inc/shell.h"
#include "../../inc/signals.h"

void	execute(t_cmd *cmd, t_data *data, int i)
{
	char	*cmd_file;

	signals_child();
	(check_in(cmd, i), check_out(cmd, i));
	if (cmd->in != 0)
		(dup2(cmd->in, 0), close(cmd->in));
	if (cmd->out != 1)
		(dup2(cmd->out, 1), close(cmd->out));
	close_all_pipes(data);
	if (!cmd->args || !cmd->args[0])
		free_n_exit(0, data->input);
	if (isbuiltin(cmd->args[0]))
		(exec_b(cmd), free_n_exit(data->status, data->input));
	else
	{
		cmd_file = filename(cmd->args[0], data);
		if (execve(cmd_file, cmd->args, data->envp) == -1)
		{
			if (errno == 13)
				(print_error(cmd->args[0], 5), free_n_exit(126, data->input));
			else
				free_n_exit(0, data->input);
		}
	}
}
