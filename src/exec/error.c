/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:30:05 by yabarhda          #+#    #+#             */
/*   Updated: 2025/07/19 17:04:16 by yabarhda         ###   ########.fr       */
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
	if (err == 0)
		perror(str);
	else
	{
		ft_printf("minishell: ");
		if (err >= 1 && err <= 4)
		{
			if (err == 1)
				ft_printf("command not found");
			else if (err == 2)
				ft_printf("permission denied");
			else if (err == 3)
				ft_printf("no such file or directory");
			else if (err == 4)
				ft_printf("cannot create temp file for here-document");
			ft_printf(": %s\n", str);
		}
		else
		{
			if (err == 5)
				ft_printf("%s: Is a directory\n", str);
			else if (err == 6)
				ft_printf("export: `%s': not a valid identifier\n", str);
		}
	}
}
