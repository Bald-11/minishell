/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:30:05 by yabarhda          #+#    #+#             */
/*   Updated: 2025/07/20 09:49:03 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include "../../inc/utils.h"
#include "../../inc/shell.h"

void	free_n_exit(int status, char *input)
{
	free(input);
	ft_malloc(0, 0);
	exit(status);
}

void	print_error(char *str, int err)
{
	char *error;

	if (err == 0)
		perror(str);
	else
	{
		error = ft_strdup("minishell: ");
		if (err >= 1 && err <= 4)
		{
			if (err == 1)
				error = ft_strjoin(error, "command not found");
			else if (err == 2)
				error = ft_strjoin(error, "permission denied");
			else if (err == 3)
				error = ft_strjoin(error, "no such file or directory");
			else if (err == 4)
				error = ft_strjoin(error, "cannot create temp file for here-document");
			error = ft_strjoin(error, ft_strjoin(": ", ft_strjoin(str, "\n")));
		}
		else
		{
			if (err == 5)
				error = ft_strjoin(error, ft_strjoin(str, ": Is a directory\n"));
			else if (err == 6)
			{
				error = ft_strdup("export: `");
				error = ft_strjoin(error, ft_strjoin(str, "': not a valid identifier\n"));
			}
		}
		write(2, error, ft_strlen(error));
	}
}
