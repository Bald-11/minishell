/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:28:19 by yabarhda          #+#    #+#             */
/*   Updated: 2025/03/21 19:50:55 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

char	*get_input()
{
	char	*input;

	input = readline("$ ");
	if (input && input[0])
		add_history(input);
	return (input);
}

t_token *create_token(t_token_type type, char *value)
{
    t_token *token;
    
    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    token->value = strdup(value);
    token->next = NULL;
    return (token);
}

void add_token(t_token **head, t_token *new_token)
{
    t_token *current;
    
    if (!*head)
    {
        *head = new_token;
        return;
    }
    current = *head;
    while (current->next)
        current = current->next;
    current->next = new_token;
}

// pwd | ls << dst | cat -e << d | echo >> pwd.txt

int	word_len(char *input)
{
	int i = 0;
    while (input[i] && !(input[i] == 32 || input[i] == '|' || 
		input[i] == '>' || input[i] == '<'))
		i++;
	return (i);
}

void	ft_strncpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

t_token	*tokenize_input(char *input)
{
	t_token	*head;
	char	*temp;
	int		len;

	head = NULL;
	temp = NULL;
	len = 0;
	while (*input)
	{
		while (*input && *input == 32)
			input++;
		if (*input == '|')
			add_token(&head, create_token(T_PIPE, "|"));
		else if (*input == '>' || *input == '<')
		{
			if (*(input + 1) == '>' || *(input + 1) == '<')
			{
				if (*input == '>')
					add_token(&head, create_token(T_APPEND, ">>"));
				else if (*input == '<')
					add_token(&head, create_token(T_HEREDOC, "<<"));
				input++;
			}
			else
			{
				if (*input == '>')
					add_token(&head, create_token(T_REDIR_OUT, ">"));
				else if (*input == '<')
					add_token(&head, create_token(T_REDIR_IN, "<"));			
			}
		}
		else
		{
			if (*input == '"' || *input == '\'')
			{
				printf("quotes not handled yet\n");
			}
			else
			{
				len = word_len(input);
				temp = (char *)malloc(sizeof(char) * (len + 1));
				if (!temp)
					return (NULL); // need to free the linked list first
				ft_strncpy(temp, input, len + 1);
				add_token(&head, create_token(T_ARG, temp));
				free(temp);
				input += len - 1;
			}
		}
		input++;
	}
	add_token(&head, create_token(T_EOF, "EOF"));
	return (head);
}

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens;
		tokens = tokens->next;
		free(temp->value);
		free(temp);
	}
}

void	print_tokens(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	printf("\n\n");
	while (temp)
	{
		printf("TOKEN TYPE: %d\tTOKEN: %s\n", temp->type, temp->value);
		temp = temp->next;
	} 
	printf("\n\n");
}

void	shell_loop()
{
	char		*input;
	t_token		*tokens;
	// t_command	*cmds;

	while (1)
	{
		input = get_input();
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (input[0] == '\0')
			continue ;
		tokens = tokenize_input(input);
		print_tokens(tokens);
		// cmds = parse_tokens(tokens);
		// exec_cmds(cmds);
        free_tokens(tokens);
        // free_cmds(cmds);
        free(input);
	}
}

int	main(void)
{
	shell_loop();
	return (0);
}
