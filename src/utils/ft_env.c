/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:44:17 by yabarhda          #+#    #+#             */
/*   Updated: 2025/05/05 15:05:42 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/utils.h"

static int	list_len(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 1;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	arr = NULL;
}

char	**ft_envp(t_env *env)
{
	int		i;
	t_env	*tmp;
	char	**envp;

	i = 0;
	tmp = env;
	envp = (char **)malloc(sizeof(char *) * list_len(env));
	if (!envp)
		return (NULL);
	while (tmp)
	{
		envp[i] = (char *)malloc(sizeof(char) * (ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2));
		if (!envp[i])
			return (free_arr(envp), NULL);
		ft_strncpy(envp[i], tmp->key, ft_strlen(tmp->key) + 1);
		ft_strncat(envp[i], "=", ft_strlen(tmp->key) + 2);
		ft_strncat(envp[i], tmp->value, ft_strlen(tmp->value) + ft_strlen(tmp->key) + 2);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
