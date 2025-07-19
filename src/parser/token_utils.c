/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:56:32 by mbarrah           #+#    #+#             */
/*   Updated: 2025/07/17 18:29:35 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/utils.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_flag(char *str)
{
	return (str && str[0] == '-');
}

static t_token_type	handle_pipe(int *cmd_position, int *after_pipe)
{
	*cmd_position = 1;
	*after_pipe = 1;
	return (T_PIPE);
}

static t_token_type	handle_redirection(char *str)
{
	if (ft_strcmp(str, "<") == 0)
		return (T_REDIR_IN);
	else if (ft_strcmp(str, ">") == 0)
		return (T_REDIR_OUT);
	else if (ft_strcmp(str, ">>") == 0)
		return (T_APPEND);
	else if (ft_strcmp(str, "<<") == 0)
		return (T_HEREDOC);
	return (T_ARG);
}

static t_token_type	handle_command(char *str, int *cmd_position, int *after_pipe)
{
	if (*cmd_position == 1 && (*after_pipe || *cmd_position == 1))
	{
		*after_pipe = 0;
		(*cmd_position)++;
		return (T_CMD);
	}
	else if (is_flag(str))
	{
		(*cmd_position)++;
		return (T_FLAG);
	}
	(*cmd_position)++;
	return (T_ARG);
}

t_token_type	get_token_type(char *str)
{
	static int	cmd_position = 1;
	static int	after_pipe = 0;

	if (!str)
	{
		cmd_position = 1;
		after_pipe = 0;
		return (T_EOF);
	}
	if (!*str)
		return (T_EOF);
	else if (ft_strcmp(str, "|") == 0)
		return (handle_pipe(&cmd_position, &after_pipe));
	else if (is_special_char(str[0]))
	{
		cmd_position++;
		return (handle_redirection(str));
	}
	return (handle_command(str, &cmd_position, &after_pipe));
}

char	*extract_quoted_token(char *input, int *i, char quote_type)
{
	char	*result;
	char	*temp;

	(*i)++;
	result = ft_strdup("");
	while (input[*i] && input[*i] != quote_type)
	{
		if (input[*i] == '\\' && quote_type == '\"')
		{
			(*i)++;
			if (input[*i])
			{
				temp = ft_strndup(input + *i, 1);
				result = ft_strjoin(result, temp);
				// free(temp);
			}
		}
		else
		{
			temp = ft_strndup(input + *i, 1);
			result = ft_strjoin(result, temp);
			// free(temp);
		}
		(*i)++;
	}
	if (input[*i])
		(*i)++;
	return (result);
}

static char	*extract_special_token(char *input, int *i)
{
	int		start;

	start = *i;
	if ((input[*i] == '>' || input[*i] == '<') && input[*i + 1] == input[*i])
	{
		*i += 2;
		return (ft_strndup(input + start, 2));
	}
	(*i)++;
	return (ft_strndup(input + start, 1));
}

#include <stdio.h>

char	*extract_token_value(char *input, int *i)
{
	int		len;
	char	*result;
	char	*temp;
	char	*new_result;

	while (input[*i] && is_whitespace(input[*i]))
		(*i)++;
	if (!input[*i])
		return (NULL);
	if (input[*i] == '$' && is_quote(input[*i + 1]))
		(*i)++;
	// if (input[*i] == '\'' || input[*i] == '\"')
	// 	return (extract_quoted_token(input, i, input[*i]));
	if (is_special_char(input[*i]))
		return (extract_special_token(input, i));
	result = ft_strdup("");
	while (input[*i] && !is_whitespace(input[*i]) && !is_special_char(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			temp = extract_quoted_token(input, i, input[*i]);
			if (temp)
			{
				new_result = ft_strjoin(result, temp);
				result = new_result;
			}
		}
		else
		{
			len = 0;
			while (input[*i + len] && !is_whitespace(input[*i + len]) && 
				!is_special_char(input[*i + len]) && 
				input[*i + len] != '\'' && input[*i + len] != '\"')
				len++;
			if (len > 0)
			{
				temp = ft_strndup(input + *i, len);
				new_result = ft_strjoin(result, temp);
				result = new_result;
				*i += len;
			}
		}
	}
	return (result);
}
