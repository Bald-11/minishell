/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:09:33 by yabarhda          #+#    #+#             */
/*   Updated: 2025/04/05 18:18:22 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	print_error(char *str, int err)
{
	if (err == 0)
		perror(str);
	else
	{
		printf("minishell: ");
		if (err == 1)
			printf("command not found");
		else if (err == 2)
			printf("permission denied");
		else if (err == 3)
			printf("no such file or directory");
		printf(": %s\n", str);
	}
}
