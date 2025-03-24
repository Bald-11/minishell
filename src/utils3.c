/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 19:25:54 by yabarhda          #+#    #+#             */
/*   Updated: 2025/03/24 19:33:12 by yabarhda         ###   ########.fr       */
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
