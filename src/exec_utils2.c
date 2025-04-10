/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:38:12 by yabarhda          #+#    #+#             */
/*   Updated: 2025/04/10 13:08:17 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

static int	mini_env_expand(t_data *data, char *input, int fd, int *j)
{
	char *(tmp), *(value);
	tmp = ft_strdup("");
	if (!tmp)
		return (0);
	while (ft_isalnum(input[*j]))
		append_char(&tmp, input[(*j)++]);
	if (tmp[0])
	{
		value = ft_getenv(tmp, data->env);
		if (value)
			write(fd, value, ft_strlen(value));
		else
			return (0);
	}
	else
		return (0);
	free(tmp);
	return (1);
}

static void	heredoc_env(t_data *data, char *input, int fd)
{
	int (i), j = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			j = i + 1;
			if (!mini_env_expand(data, input, fd, &j))
				return ;
			i += j;
		}
		else
		{
			write(fd, &input[i], 1);
			i++;
		}
	}
}

static void	heredoc_handle(t_data *data, int *tmp_fd, char *file)
{
	char *(input);
	*tmp_fd = open("/tmp/minishell.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	while (1)
	{
		input = readline("> ");
		if (!ft_strcmp(input, file))
			break ;
		heredoc_env(data, input, *tmp_fd);
		write(*tmp_fd, "\n", 1);
		free(input);
	}
	close(*tmp_fd);
	*tmp_fd = open("/tmp/minishell.txt", O_RDONLY);
}

void	check_in(t_cmd *cmd, int index)
{
	t_redir *(tmp);
	int (tmp_fd);
	tmp_fd = -1;
	tmp = cmd->redir;
	while (tmp)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_HEREDOC)
		{
			if (tmp_fd != -1)
				close(tmp_fd);
			if (tmp->type == REDIR_IN)
				tmp_fd = open(tmp->file, O_RDONLY);
			else if (tmp->type == REDIR_HEREDOC)
				heredoc_handle(cmd->data, &tmp_fd, tmp->file);
			if (tmp_fd == -1)
				(check_access(tmp->file), free_n_exit(cmd, 1));
		}
		tmp = tmp->next;
	}
	if (tmp_fd != -1)
		cmd->in = tmp_fd;
	else if (index != 0 && index != -1)
		cmd->in = cmd->data->pipe[index - 1][0];
}

void	check_out(t_cmd *cmd, int index)
{
	t_redir *(tmp);
	int (tmp_fd);
	tmp_fd = -1;
	tmp = cmd->redir;
	while (tmp)
	{
		if (tmp->type == REDIR_OUT || tmp->type == REDIR_APPEND)
		{
			if (tmp_fd != -1)
				close(tmp_fd);
			if (tmp->type == REDIR_OUT)
				tmp_fd = open(tmp->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			else if (tmp->type == REDIR_APPEND)
				tmp_fd = open(tmp->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (tmp_fd == -1)
				(check_access(tmp->file), free_n_exit(cmd, 1));
		}
		tmp = tmp->next;
	}
	if (tmp_fd != -1)
		cmd->out = tmp_fd;
	else if (index != -1 && index != cmd->data->cc - 1)
		cmd->out = cmd->data->pipe[index][1];
}
