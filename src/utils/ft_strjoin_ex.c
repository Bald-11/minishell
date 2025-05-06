/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_ex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:05:46 by yabarhda          #+#    #+#             */
/*   Updated: 2025/05/06 14:49:45 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

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
	dest = (char *)ft_malloc((s1_len + s2_len) * (sizeof(char) + 1), 69);
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
