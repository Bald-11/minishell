/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 20:53:16 by yabarhda          #+#    #+#             */
/*   Updated: 2025/04/10 13:10:18 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

int	ft_isalnum(int c)
{
	return (((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		|| (c >= 48 && c <= 57) || (c == '_'));
}

char	*ft_strdup(const char *s)
{
	size_t	src_len;
	size_t	i;

	i = 0;
	char *(d);
	if (!s)
		return (NULL);
	src_len = ft_strlen(s);
	d = (char *)malloc((src_len + 1) * sizeof(char));
	if (!d)
		return (NULL);
	while (i < src_len)
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	word_len(char *input)
{
	int (i);
	i = 0;
	while (input[i] && !(ft_isspace(input[i]) || input[i] == '|'
			|| input[i] == '>' || input[i] == '<'))
		i++;
	return (i);
}

void	skip_whites(char **input)
{
	while (**input && ft_isspace(**input))
		(*input)++;
}
