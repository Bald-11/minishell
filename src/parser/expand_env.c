/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:56:41 by mbarrah           #+#    #+#             */
/*   Updated: 2025/05/03 15:21:02 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell.h"

int	is_env_char(char c)
{
	return ((c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9') ||
			c == '_');
}

char	*get_env_value(char *key, t_env *env)
{
	t_env	*current;

	if (!key || !*key)
		return (NULL);
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

static int	handle_special_char(char *str, int *i, int *length)
{
	if (str[*i] == '?')
	{
		*length += 2;
		(*i)++;
		return (1);
	}
	return (0);
}

static int	process_env_var(char *str, int *i, t_env *env, int *length)
{
	int		key_len;
	char	*key;
	char	*value;

	key_len = 0;
	if (handle_special_char(str, i, length))
		return (1);
	while (str[*i + key_len] && is_env_char(str[*i + key_len]))
		key_len++;
	key = ft_strndup(str + *i, key_len);
	value = get_env_value(key, env);
	*length += value ? ft_strlen(value) : 0;
	free(key);
	*i += key_len;
	return (1);
}

int	calculate_expanded_length(char *str, t_env *env)
{
	int		i;
	int		length;
	int		in_squote;

	length = 0;
	i = 0;
	in_squote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_squote)
			in_squote = 1;
		else if (str[i] == '\'' && in_squote)
			in_squote = 0;
		if (str[i] == '$' && !in_squote && str[i + 1] &&
			(is_env_char(str[i + 1]) || str[i + 1] == '?'))
		{
			i++;
			process_env_var(str, &i, env, &length);
		}
		else
		{
			length++;
			i++;
		}
	}
	return (length);
}

static void	copy_env_value(char *result, int *j, char *value)
{
	int	k;

	k = 0;
	while (value[k])
		result[(*j)++] = value[k++];
}

static void	handle_expansion(char *str, int *i, char *result, int *j, t_env *env)
{
	int		key_len;
	char	*key;
	char	*value;

	key_len = 0;
	if (str[*i] == '?')
	{
		result[(*j)++] = '0';
		(*i)++;
		return;
	}
	while (str[*i + key_len] && is_env_char(str[*i + key_len]))
		key_len++;
	key = ft_strndup(str + *i, key_len);
	value = get_env_value(key, env);
	if (value)
		copy_env_value(result, j, value);
	free(key);
	*i += key_len;
}

char	*expand_env_vars(char *str, t_env *env)
{
	char	*result;
	int		i;
	int		j;
	int		in_squote;

	if (!str)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (calculate_expanded_length(str, env) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_squote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_squote)
			in_squote = 1;
		else if (str[i] == '\'' && in_squote)
			in_squote = 0;
		if (str[i] == '$' && !in_squote && str[i + 1] &&
			(is_env_char(str[i + 1]) || str[i + 1] == '?'))
		{
			i++;
			handle_expansion(str, &i, result, &j, env);
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

void	expand_tokens(t_token *tokens, t_env *env)
{
	t_token	*current;
	char	*expanded_value;

	current = tokens;
	while (current)
	{
		if (current->value && ft_strchr(current->value, '$'))
		{
			expanded_value = expand_env_vars(current->value, env);
			if (expanded_value)
			{
				free(current->value);
				current->value = expanded_value;
			}
		}
		current = current->next;
	}
}
