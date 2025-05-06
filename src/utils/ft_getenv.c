/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:49:50 by yabarhda          #+#    #+#             */
/*   Updated: 2025/05/06 16:52:28 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

char	*ft_getenv(char *var, t_env *env)
{
	int (i), v_len = ft_strlen(var);
	t_env *(tmp);
	i = 0;
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, var, v_len))
			return (tmp->value);
		tmp = tmp->next;
		i++;
	}
	return (NULL);
}
