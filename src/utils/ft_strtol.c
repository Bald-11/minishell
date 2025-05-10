/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:49:56 by yabarhda          #+#    #+#             */
/*   Updated: 2025/05/10 11:32:16 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"
#include "../../inc/shell.h"

void	ft_strtol(char *str)
{
	long (result), p = 1, n = 0;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			n = 1;
			p = 0;
		}
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		if ((result < 0 && p) || ((result * -1) > 0 && n))
		{
			errno = ERANGE;
			return ;
		}
		str++;
	}
}
