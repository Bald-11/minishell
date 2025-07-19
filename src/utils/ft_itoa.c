/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:53:51 by yabarhda          #+#    #+#             */
/*   Updated: 2025/07/19 17:43:28 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

static void	fill_string(char *str, long n, int len)
{
	ft_bzero(str, len + 1);
	while (len)
	{
		len--;
		if (n < 0)
		{
			str[0] = '-';
			n *= -1;
		}
		if (str[len] != '-')
			str[len] = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		len;
	long	temp_n;

	len = 0;
	temp_n = n;
	if (temp_n == 0)
		len++;
	while (temp_n != 0)
	{
		len++;
		temp_n /= 10;
	}
	len += n < 0;
	dest = (char *)ft_malloc(sizeof(char) * (len + 1), 69);
	fill_string(dest, n, len);
	return (dest);
}
