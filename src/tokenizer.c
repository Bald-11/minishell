/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:59:50 by yabarhda          #+#    #+#             */
/*   Updated: 2025/03/22 21:18:20 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

int	double_q_env_expand(char **current, char **result, char *close_quote)
{
	char *(var_name), var_value, old_res;
	int (var_len);
	var_len = 0;
	(*current)++;
	while ((*current + var_len) < close_quote && (isalnum((*current)[var_len])
		|| (*current)[var_len] == '_'))
		var_len++;
	var_name = malloc(var_len + 1);
	if (!var_name)
		return (free(*result), 0);
	ft_strncpy(var_name, *current, var_len + 1);
	var_value = getenv(var_name);
	if (var_value)
	{
		old_res = *result;
		*result = ft_strjoin(old_res, var_value);
		free(old_res);
		if (!*result)
			return (0);
	}
	free(var_name);
	*current += var_len;
	return (1);
}

int	in_quote_loop(char **current, char **result, char *close_quote)
{
	char	temp[2];

	char *(old_res);
	if (**current == '$')
	{
		if (!double_q_env_expand(current, result, close_quote))
			return (0);
	}
	else
	{
		temp[0] = **current;
		temp[1] = '\0';
		old_res = *result;
		*result = ft_strjoin(old_res, temp);
		free(old_res);
		if (!*result)
			return (0);
		(*current)++;
	}
	return (1);
}

int	double_quote_handle(t_token **head, char **input, char quote)
{
	char *(close_quote), *result, *current;
	close_quote = ft_strchr(*input, quote);
	result = malloc(1);
	if (!result)
	{
		if (*head)
			free_tokens(*head);
		return (0);
	}
	result[0] = '\0';
	current = *input;
	while (current < close_quote)
	{
		if (!in_quote_loop(&current, &result, close_quote))
		{
			if (*head)
				free_tokens(*head);
			return (0);
		}
	}
	add_token(head, create_token(T_ARG, result));
	*input = close_quote;
	return (free(result), 1);
}

int	tokenize_quotes(t_token **head, char **input)
{
	char	quote;

	quote = **input;
	(*input)++;
	if (!ft_strchr(*input, quote))
	{
		if (*head)
			free_tokens(*head);
		return (printf("minishell: syntax error: unclosed quote\n"), 0);
	}
	if (quote == '\'')
	{
		if (!single_quote_handle(head, input, quote))
			return (0);
	}
	else if (quote == '"')
	{
		if (!double_quote_handle(head, input, quote))
			return (0);
	}
	return (1);
}

t_token	*tokenize_input(char *input)
{
	t_token	*head;

	head = NULL;
	while (*input)
	{
		skip_whites(&input);
		if (*input == '|')
			add_token(&head, create_token(T_PIPE, "|"));
		else if (*input == '>' || *input == '<')
			tokenize_redirects(&head, &input);
		else if (*input == '"' || *input == '\'')
		{
			if (!tokenize_quotes(&head, &input))
				return (NULL);
		}
		else
		{
			if (!tokenize_else(&head, &input))
				return (NULL);
		}
		input++;
	}
	add_token(&head, create_token(T_EOF, "EOF"));
	return (head);
}
