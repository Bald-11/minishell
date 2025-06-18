/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:56:38 by mbarrah           #+#    #+#             */
/*   Updated: 2025/06/18 18:10:02 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/utils.h"
#include "../../inc/shell.h"

t_cmd	*create_cmd(t_data *data)
{
	t_cmd	*cmd;

	cmd = ft_malloc(sizeof(t_cmd), 3);
	cmd->args = NULL;
	cmd->in = 0;
	cmd->out = 1;
	cmd->redir = NULL;
	cmd->data = data;
	cmd->next = NULL;
	return (cmd);
}

void	add_cmd(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (!*head)
	{
		*head = new_cmd;
		return;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
}

t_redir	*create_redir(t_redir_type type, char *file)
{
	t_redir	*redir;

	redir = ft_malloc(sizeof(t_redir), 59);
	if (type == REDIR_HEREDOC)
	{
		redir->dlimit = ft_strdup(file);
		redir->file = NULL;
	}
	else
	{
		redir->dlimit = NULL;
		redir->file = ft_strdup(file);
	}
	redir->type = type;
	redir->quote = 0;
	redir->next = NULL;
	return (redir);
}

void	add_redir(t_redir **head, t_redir *new_redir)
{
	t_redir	*current;

	if (!*head)
	{
		*head = new_redir;
		return;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_redir;
}

static char	**create_new_args(char **old_args, int size, char *arg_value)
{
	char	**new_args;
	int		i;

	new_args = ft_malloc(sizeof(char *) * (size + 2), 3);
	i = 0;
	while (i < size)
	{
		new_args[i] = old_args[i];
		i++;
	}
	new_args[i] = ft_strdup(arg_value);
	new_args[i + 1] = NULL;
	return (new_args);
}

int	add_arg_to_cmd(t_cmd *cmd, char *arg_value)
{
	char	**new_args;
	int		size;

	size = 0;
	if (cmd->args)
	{
		while (cmd->args[size])
			size++;
	}
	new_args = create_new_args(cmd->args, size, arg_value);
	if (!new_args)
		return (0);
	// if (cmd->args)
	// 	free(cmd->args);
	cmd->args = new_args;
	return (1);
}

static int	get_redir_type(t_token_type type)
{
	if (type == T_REDIR_IN)
		return (REDIR_IN); // enum index = 0 hense the error
	else if (type == T_REDIR_OUT)
		return (REDIR_OUT);
	else if (type == T_APPEND)
		return (REDIR_APPEND);
	else if (type == T_HEREDOC)
		return (REDIR_HEREDOC);
	return (-1);
}

int	process_redirection(t_cmd *cmd, t_token **current)
{
	int		redir_type;
	t_token	*token;
	t_token	*file_token;

	token = *current;
	redir_type = get_redir_type(token->type);
	if (redir_type == -1) // was (!redir_type) which is always true
		return (0);
	file_token = token->next;
	if (!file_token)
		return (0);
	add_redir(&(cmd->redir), create_redir(redir_type, file_token->value));
	*current = file_token;
	return (1);
}

static void	free_cmd_args(t_cmd *cmd)
{
	int	i;

	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
}

static void	free_cmd_redirs(t_cmd *cmd)
{
	t_redir	*redir;
	t_redir	*next_redir;

	redir = cmd->redir;
	while (redir)
	{
		next_redir = redir->next;
		if (redir->file)
			free(redir->file);
		free(redir);
		redir = next_redir;
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return;
	free_cmd_args(cmd);
	free_cmd_redirs(cmd);
	free(cmd);
}

void	free_all_cmds(t_cmd *head)
{
	t_cmd	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free_cmd(temp);
	}
}

static void	print_cmd_args(t_cmd *cmd)
{
	int	i;

	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			printf("'%s' ", cmd->args[i]);
			i++;
		}
	}
	else
		printf("(none)");
}

static void	print_cmd_redirs(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	if (redir)
		printf("  Redirections:\n");
	while (redir)
	{
		printf("    ");
		if (redir->type == REDIR_IN)
			printf("< ");
		else if (redir->type == REDIR_OUT)
			printf("> ");
		else if (redir->type == REDIR_APPEND)
			printf(">> ");
		else if (redir->type == REDIR_HEREDOC)
			printf("<< ");
		printf("'%s'\n", redir->file);
		redir = redir->next;
	}
}

void	print_cmds(t_cmd *head)
{
	t_cmd	*current;
	int		cmd_count;

	current = head;
	cmd_count = 1;
	printf("--- Commands ---\n");
	while (current)
	{
		printf("Command %d:\n", cmd_count++);
		printf("  Args: ");
		print_cmd_args(current);
		printf("\n");
		print_cmd_redirs(current);
		current = current->next;
		if (current)
			printf("  |\n");
	}
	printf("---------------\n");
}

static int	handle_token(t_cmd *current_cmd, t_token **current)
{
	if ((*current)->type == T_REDIR_IN || (*current)->type == T_REDIR_OUT ||
		(*current)->type == T_APPEND || (*current)->type == T_HEREDOC)
	{
		if (!process_redirection(current_cmd, current))
			return (0);
	}
	else if ((*current)->type == T_CMD || (*current)->type == T_ARG ||
			(*current)->type == T_FLAG)
	{
		if (!add_arg_to_cmd(current_cmd, (*current)->value))
			return (0);
	}
	return (1);
}

t_cmd	*parse_commands(t_token *tokens, t_data *data)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;
	t_token	*current;

	cmd_list = NULL;
	current_cmd = NULL;
	current = tokens;
	while (current)
	{
		if (!current_cmd)
		{
			current_cmd = create_cmd(data);
			add_cmd(&cmd_list, current_cmd);
		}
		if (current->type == T_PIPE)
			current_cmd = NULL;
		else if (!handle_token(current_cmd, &current))
		{
			// free_all_cmds(cmd_list);
			return (NULL);
		}
		current = current->next;
	}
	return (cmd_list);
}
