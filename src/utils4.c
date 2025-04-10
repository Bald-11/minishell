/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:13:20 by yabarhda          #+#    #+#             */
/*   Updated: 2025/04/10 13:10:32 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

static void	fill_string(char *str, long n, int len)
{
	str[len] = '\0';
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
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	fill_string(dest, n, len);
	return (dest);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (-1);
	if (n == 0)
		return (0);
	i = 0;
	while (i < n - 1 && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_getenv(char *var, char **env)
{
	int (i), v_len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if ((!ft_strncmp(env[i], var, v_len)) && (env[i][v_len] == '='))
			return (env[i] + v_len + 1);
		i++;
	}
	return (NULL);
}
