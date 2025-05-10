/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:56:44 by mbarrah           #+#    #+#             */
/*   Updated: 2025/05/10 11:35:20 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/utils.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

static int	handle_quotes(char *input, int *i, int *in_quote, char *quote_type)
{
	if (!*in_quote && (input[*i] == '\'' || input[*i] == '\"'))
	{
		*in_quote = 1;
		*quote_type = input[*i];
	}
	else if (*in_quote && input[*i] == *quote_type)
	{
		*in_quote = 0;
		*quote_type = 0;
	}
	return (1);
}

int	check_quotes(char *input)
{
	int		i;
	char	quote_type;
	int		in_quote;

	i = 0;
	in_quote = 0;
	quote_type = 0;
	while (input[i])
	{
		handle_quotes(input, &i, &in_quote, &quote_type);
		i++;
	}
	if (in_quote)
	{
		ft_printf("minishell: syntax error: unclosed quote\n");
		return (0);
	}
	return (1);
}
