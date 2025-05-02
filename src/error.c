/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:09:33 by yabarhda          #+#    #+#             */
/*   Updated: 2025/05/01 13:20:06 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	set_exit_status(t_data *data)
{
	int (temp);
	if (WIFEXITED(data->status))
	{
		temp = WEXITSTATUS(data->status);
		data->status = temp;
	}
	else if (WIFSIGNALED(data->status))
	{
		temp = WTERMSIG(data->status);
		data->status = temp;
	}
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
