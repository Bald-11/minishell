/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:59:50 by yabarhda          #+#    #+#             */
/*   Updated: 2025/03/24 19:37:46 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

int	quote_check(char *input)
{
	int (squote), dquote = 0;
	squote = 0;
	while (*input)
	{
		if (*input == '\'' && !dquote)
			squote = !squote;
		else if (*input == '"' && !squote)
			dquote = !dquote;
		input++;
	}
	if (squote || dquote)
		return (printf("minishell: syntax error: unclosed quote\n"), 0);
	return (1);
}

void	tokenize_redirects(t_token **head, char **input)
{
	if (*(*input + 1))
	{
		if (*(*input + 1) == '>' || *(*input + 1) == '<')
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

void	single_quote_handle(char **input, char **result)
{
	char *(end);
	int (len), i = 0;
	(*input)++;
	end = ft_strchr(*input, '\'');
	if (!end)
	{
		(*input) += ft_strlen(*input);
		return ;
	}
	len = end - *input;
	while (i++ < len)
	{
		append_char(result, **input);
		(*input)++;
	}
	(*input)++;
}

void	double_quote_handle(char **input, char **result)
{
	char *(end);
	(*input)++;
	end = ft_strchr(*input, '"');
	if (!end)
	{
		(*input) += ft_strlen(*input);
		return ;
	}
	while (*input < end)
	{
		if (**input == '$')
			env_var_handle(input, result);
		else
		{
			append_char(result, **input);
			(*input)++;
		}
	}
	(*input)++;
}

t_token	*tokenize_input(char *input)
{
	t_token *(head);
	head = NULL;
	if (!quote_check(input))
		return (NULL);
	while (*input)
	{
		skip_whites(&input);
		if (*input == '|')
			add_token(&head, create_token(T_PIPE, "|"));
		else if (*input == '>' || *input == '<')
			tokenize_redirects(&head, &input);
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
