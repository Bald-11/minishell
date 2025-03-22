/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:01:24 by yabarhda          #+#    #+#             */
/*   Updated: 2025/03/22 21:19:20 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	tokenize_redirects(t_token **head, char **input)
{
	if (**(input + 1))
	{
		if (**(input + 1) == '>' || **(input + 1) == '<')
		{
			if (**input == '>')
				add_token(head, create_token(T_APPEND, ">>"));
			else if (**input == '<')
				add_token(head, create_token(T_HEREDOC, "<<"));
			(*input)++;
		}
		else
		{
			if (**input == '>')
				add_token(head, create_token(T_REDIR_OUT, ">"));
			else if (**input == '<')
				add_token(head, create_token(T_REDIR_IN, "<"));
		}
	}
	else
	{
		if (**input == '>')
			add_token(head, create_token(T_REDIR_OUT, ">"));
		else if (**input == '<')
			add_token(head, create_token(T_REDIR_IN, "<"));
	}
}

void	expand_env_var(t_token **head, char *arg)
{
	char	*env_var;

	env_var = getenv(arg);
	if (!env_var)
		add_token(head, create_token(T_ARG, ""));
	else
		add_token(head, create_token(T_ARG, env_var));
}

int	tokenize_else(t_token **head, char **input)
{
	int (len), is_env_v = 0;
	char *(token);
	if (**input == '$')
	{
		(*input)++;
		is_env_v = 1;
	}
	len = word_len(*input);
	token = (char *)malloc(sizeof(char) * (len + 1));
	if (!token)
	{
		if (*head)
			free_tokens(*head);
		return (0);
	}
	ft_strncpy(token, *input, len + 1);
	if (is_env_v)
		expand_env_var(head, token);
	else
		add_token(head, create_token(T_ARG, token));
	free(token);
	*input += len - 1;
	return (1);
}

int	single_quote_handle(t_token **head, char **input, char quote)
{
	int		len;
	char	*temp;

	len = ft_strchr(*input, quote) - *input;
	temp = malloc(len + 1);
	if (!temp)
	{
		if (*head)
			free_tokens(*head);
		return (0);
	}
	ft_strncpy(temp, *input, len + 1);
	add_token(head, create_token(T_ARG, temp));
	free(temp);
	*input += len;
	return (1);
}
