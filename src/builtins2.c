/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:12:46 by mbarrah           #+#    #+#             */
/*   Updated: 2025/04/10 13:07:10 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	echo(char **args)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (args[1] && !ft_strcmp(args[1], "-n"))
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
}
