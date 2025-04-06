/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 08:22:11 by yabarhda          #+#    #+#             */
/*   Updated: 2025/04/06 19:00:07 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

int	count_cmds(t_cmd *cmd)
{
	t_cmd *tmp = cmd;
	int count = 1;
	while (tmp->next)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

char	*filename(char *cmd, t_data *data)
{
	char *(path), *(c_path);
	char **(arr);
	int (i);
	i = -1;
	if (!ft_strchr_ex(cmd, '/'))
		return (cmd);
	path = ft_getenv("PATH", data->env);
	if (!path)
		return (cmd);
	arr = ft_split(path, ':');
	if (!arr)
		return (cmd);
	while (arr[++i])
	{
		c_path = ft_strjoin_ex(arr[i], cmd);
		if (!access(c_path, F_OK))
			return (c_path);
		free(c_path);
	}
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (cmd);
}

void	free_n_exit(t_cmd *cmd, int status)
{
	if (cmd->in != 0)
		close(cmd->in);
	if (cmd->out != 1)
		close(cmd->out);
	if (cmd->data->pid)
		free(cmd->data->pid);
	free_env(cmd->data->env);
	free_cmds(cmd);
	exit(status);
}

void	exec_c(t_cmd *cmd, t_data *data)
{
	/* if (isbuiltin(cmd->args[0]))
	{
		// do something here
		printf("do something here\n"), exit(0);
	}
	else */
	if (1)
	{
		if (cmd->in != 0)
		{
			dup2(cmd->in, 0);
			close(cmd->in);
		}
		if (cmd->out != 1)
		{
			dup2(cmd->out, 1);
			close(cmd->out);
		}
		if (execve(filename(cmd->args[0], data), cmd->args, data->env) == -1)
		{
			if (errno == 2)
				print_error(cmd->args[0], 1), free_n_exit(cmd, 127);
			else
				print_error(cmd->args[0], 2), free_n_exit(cmd, 126);
		}
	}
}

void	open_pipes(t_data *data)
{
	int	i;

	i = 0;
	data->pipe = (int **)malloc(sizeof(int *) * (data->cc - 1));
	if (!data->pipe)
		return ;
	while (i < (data->cc - 1))
	{
		data->pipe[i] = (int *)malloc(sizeof(int) * 2);
		if (!data->pipe[i] || pipe(data->pipe[i]) == -1)
			free_n_exit(data);
		i++;
	}
}

void	close_all_pipes(t_data *data)
{
	int (i);
	i = -1;
	while (++i < (data->cc - 1))
	{
		close(data->pipe[i][0]);
		close(data->pipe[i][1]);
	}
}

void	execute(t_cmd *cmd, t_data *data, int i)
{
	check_in(cmd, data, i);
	check_out(cmd, data, i);
	if (i == 0)
		(check_in(cmd, data, i), dup2(cmd->in, 0), close(cmd->in));
	else
		dup2(s->pipe[i - 1][0], 0);
	if (i == (s->ac - 1))
		(check_out(a, s), dup2(s->out, 1), close(s->out));
	else
		dup2(s->pipe[i][1], 1);
	close_all_pipes(s);
	av = ft_split(a[i + 2 + s->o_ap], ' ');
	if (!av || !av[0])
		(print_error(a[0], 13, av[0]), free(av), free_n_exit(s, 126));
	if (execve(filename(av[0], envp, s), av, envp) == -1)
	{
		if (errno == 2)
			(print_error(a[0], 127, av[0]), free_arr(av), free_n_exit(s, 127));
		else
		{
			(print_error(a[0], errno, av[0]), free_arr(av));
			free_n_exit(s, 126);
		}
	}
}

void	multi_cmd_handle(t_cmd *cmd, t_data *data)
{
	int (i);
	i = 0;
	data->pid = (pid_t *)malloc(data->cc * sizeof(pid_t));
	if (!data->pid)
	{
		printf("minishell: fork error\n");
		return ;
	}
	open_pipes(data);
	while (i < data->cc)
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			free_n_exit(cmd, 1);
		if (data->pid[i] == 0)
			execute(cmd, data, i);
		i++;
	}
	close_all_pipes(data);
	i = 0;
	while (i < data->cc && waitpid(data->pid[i], &data->status, 0) > 0)
		i++;
	int temp;
	if (WIFEXITED(data->status))
	{
		temp = WEXITSTATUS(data->status);
		data->status = temp;
	}
	else if (WIFSIGNALED(data->status))
	{
		temp = WTERMSIG(data->status);
		data->status = temp;
	}
}

void	check_access(char *file)
{
	if (access(file, F_OK) == -1)
		print_error(file, 3);
	else if (access(file, W_OK) == -1)
		print_error(file, 2);
}

void	check_out(t_cmd *cmd)
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
				check_access(tmp->file), free_n_exit(cmd, 1);
		}
		tmp = tmp->next;
	}
	if (tmp_fd != -1)
		cmd->out = tmp_fd;
}

void	here_doc_handle(int *tmp_fd, char *file)
{
	*tmp_fd = open("/tmp/minishell.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	while (1)
	{
		char *(input);
		input = readline("> ");
		if (!ft_strcmp(input, file))
			break ;
		write(*tmp_fd, input, ft_strlen(input));
		write(*tmp_fd, "\n", 1);
		free(input);
	}
	close(*tmp_fd);
	*tmp_fd = open("/tmp/minishell.txt", O_RDONLY);	
}

void	check_in(t_cmd *cmd)
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
				here_doc_handle(&tmp_fd, tmp->file);
			if (tmp_fd == -1)
				check_access(tmp->file), free_n_exit(cmd, 1);
		}
		tmp = tmp->next;
	}
	if (tmp_fd != -1)
		cmd->in = tmp_fd;
}

int	exec_cmds(t_cmd *cmd, t_data *data)
{
	pid_t (pid);
	int (temp);
	data->cc = count_cmds(cmd);
	if (data->cc == 1)
	{
		/* if (isbuiltin(cmd->args[0]))
			exec_b(cmd); */
		if (1)
		{
			pid = fork();
			if (!pid)
			{
				check_in(cmd);
				check_out(cmd);
				exec_c(cmd, data);
			}
			waitpid(pid, &data->status, 0);
			if (WIFEXITED(data->status))
			{
				temp = WEXITSTATUS(data->status);
				data->status = temp;
			}
			else if (WIFSIGNALED(data->status))
			{
				temp = WTERMSIG(data->status);
				data->status = temp;
			}
		}
	}
	else
		multi_cmd_handle(cmd, data);
	return (0);
}
