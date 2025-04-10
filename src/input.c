/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:08:56 by yabarhda          #+#    #+#             */
/*   Updated: 2025/04/10 13:09:14 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

/* void	print_tokens(t_token *tokens)
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
} */

// history bug needs to be fixed with signal handler

char	*get_input(t_data *data)
{
	char *(input), *(prompt);
	if (data->status == 0)
		prompt = ft_strdup(GREEN BOLD "➜  " RESET);
	else
		prompt = ft_strdup(RED BOLD "➜  " RESET);
	if (!prompt)
		return (NULL);
	input = readline(prompt);
	free(prompt);
	if (input && input[0])
		add_history(input);
	return (input);
}

void	shell_loop(t_data *data)
{
	char *(input);
	t_token *(tokens);
	t_cmd *(cmds);
	while (1)
	{
		input = get_input(data);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (!input[0])
			continue ;
		tokens = tokenize_input(input, data);
		free(input);
		if (!tokens)
			continue ;
		cmds = parse_tokens(tokens, data);
		free_tokens(tokens);
		if (!cmds)
			continue ;
		exec_cmds(cmds, data);
		free_cmds(cmds);
	}
}
