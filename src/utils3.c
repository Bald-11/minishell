/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:25:54 by yabarhda          #+#    #+#             */
/*   Updated: 2025/04/05 10:37:15 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

char	*ft_strcpy(char *dest, char *src)
{
	int (i);
	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, char *src)
{
	int (i), j = ft_strlen(dest);
	i = 0;
	while (src[i])
		dest[j++] = src[i++];
	dest[j] = '\0';
	return (dest);
}

int	ft_strchr_ex(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strjoin_ex(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1) + 1;
	s2_len = ft_strlen(s2);
	dest = (char *)malloc((s1_len + s2_len) * (sizeof(char) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i] && i < s1_len - 1)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i++] = '/';
	dest[i] = '\0';
	ft_strncat(dest, s2, s2_len + s1_len + 1);
	return (dest);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return (s1[i] - s2[i]);
}
