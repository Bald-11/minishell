/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:56:29 by mbarrah           #+#    #+#             */
/*   Updated: 2025/07/20 11:14:44 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/shell.h"

static char	*get_token_type_string(t_token_type type)
{
	if (type == T_ARG)
		return ("ARG");
	else if (type == T_CMD)
		return ("CMD");
	else if (type == T_FLAG)
		return ("FLAG");
	else if (type == T_PIPE)
		return ("PIPE");
	else if (type == T_REDIR_IN)
		return ("REDIR_IN");
	else if (type == T_REDIR_OUT)
		return ("REDIR_OUT");
	else if (type == T_APPEND)
		return ("APPEND");
	else if (type == T_HEREDOC)
		return ("HEREDOC");
	else if (type == T_DQUOTE)
		return ("DQUOTE");
	else if (type == T_SQUOTE)
		return ("SQUOTE");
	return ("UNKNOWN");
}

static void	print_token(t_token *token)
{
	char	*type_str;

	type_str = get_token_type_string(token->type);
	printf("Type: %-10s Value: '%s'\n", type_str, token->value);
}

void	print_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	printf("--- Tokens ---\n");
	while (current)
	{
		print_token(current);
		current = current->next;
	}
	printf("--------------\n");
}

void	reset_token_state(void)
{
	get_token_type(NULL);
}

t_token	*tokenize(char *input)
{
	t_token	*head;
	t_token	*new_token;
	char	*token_value;
	int		i;

	head = NULL;
	i = 0;
	reset_token_state();
	while (input[i])
	{
		if (is_whitespace(input[i]))
		{
			i++;
			continue ;
		}
		token_value = extract_token_value(input, &i);
		if (token_value)
		{
			new_token = create_token(get_token_type(token_value), token_value);
			add_token(&head, new_token);
		}
	}
	// print_tokens(head);
	return (head);
}
