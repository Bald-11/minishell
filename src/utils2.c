/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 20:53:16 by yabarhda          #+#    #+#             */
/*   Updated: 2025/03/22 21:15:07 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	word_len(char *input)
{
	int (i);
	i = 0;
	while (input[i] && !(input[i] == 32 || input[i] == '|' || input[i] == '>'
			|| input[i] == '<'))
		i++;
	return (i);
}

void	skip_whites(char **input)
{
	while (**input && ft_isspace(**input))
		(*input)++;
}
