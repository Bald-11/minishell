/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:08:56 by yabarhda          #+#    #+#             */
/*   Updated: 2025/03/24 20:48:52 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

/*void	print_tokens(t_token *tokens)
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

void	print_cmds(t_cmd *cmd)
{
	t_cmd	*temp;
	int		i;

	temp = cmd;
	while (temp)
	{
		i = 0;
		printf("CMD: ");
		while (temp->args[i])
			printf("%s ", temp->args[i++]);
		printf("\n");
		while (temp->redir)
		{
			printf("REDIR TYPE: %d\tFILE: %s\n", temp->redir->type, 
			temp->redir->file);
			temp->redir = temp->redir->next;
		}
		temp = temp->next;
	}
}*/

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
	char *(input);
	t_token *(tokens);
	t_cmd *(cmds);
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
		free(input);
		if (!tokens)
			continue ;
		cmds = parse_tokens(tokens);
		free_tokens(tokens);
		if (!cmds)
			continue ;
		free_cmds(cmds);
	}
}
