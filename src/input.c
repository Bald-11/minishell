/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:08:56 by yabarhda          #+#    #+#             */
/*   Updated: 2025/03/23 17:55:41 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

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

char	*get_input(void)
{
	char	*input;

	input = readline("$ ");
	if (input && input[0])
		add_history(input);
	return (input);
}

void	shell_loop(void)
{
	char		*input;
	t_token		*tokens;
	// t_cmd		*cmds;
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
		if (!tokens)
			continue ;
		// print_tokens(tokens);
		// cmds = parse_tokens(tokens);
		// exec_cmds(cmds);
		free_tokens(tokens);
		// free_cmds(cmds);
		free(input);
	}
}
