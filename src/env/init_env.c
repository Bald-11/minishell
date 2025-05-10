/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:56:52 by mbarrah           #+#    #+#             */
/*   Updated: 2025/05/10 11:54:20 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include "../../inc/utils.h"
#include "../../inc/shell.h"

t_env	*new_env_node(char *key, char *value)
{
	t_env	*new;

	new = ft_malloc(sizeof(t_env), -42);
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

void	add_env_node(t_env **env, t_env *new)
{
	t_env	*temp;

	if (!*env)
	{
		*env = new;
		return ;
	}
	temp = *env;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	parse_env_var(t_env **env, char *env_str)
{
	char	*key;
	char	*value;
	char	*equals;
	t_env	*new;

	equals = ft_strchr(env_str, '=');
	if (!equals)
	{
		key = ft_strdup(env_str);
		value = NULL;
	}
	else
	{
		key = ft_strndup(env_str, equals - env_str);
		value = ft_strdup(equals + 1);
	}
	new = new_env_node(key, value);
	if (new)
		add_env_node(env, new);
}

t_env	*init_env(char **env)
{
	t_env	*env_list;
	int		i;

	env_list = NULL;
	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		parse_env_var(&env_list, env[i]);
		i++;
	}
	return (env_list);
}

void	print_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	printf("--- Environment Variables ---\n");
	while (temp)
	{
		if (temp->value)
			printf("%s=%s\n", temp->key, temp->value);
		else
			printf("%s\n", temp->key);
		temp = temp->next;
	}
	printf("----------------------------\n");
}
