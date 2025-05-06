/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popnode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:19:37 by yabarhda          #+#    #+#             */
/*   Updated: 2025/05/06 15:09:27 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

void	ft_popnode(t_env **env, char *value)
{
	t_env *(tmp), *(prev);
	size_t (key_len);
	tmp = *env;
	prev = tmp;
	key_len = ft_strlen(tmp->key);
	if (!ft_strncmp(tmp->key, value, key_len))
	{
		*env = tmp->next;
		return ;
	}
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, value, key_len))
		{
			prev->next = tmp->next;
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
