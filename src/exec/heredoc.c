/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:41:05 by yabarhda          #+#    #+#             */
/*   Updated: 2025/07/20 10:56:42 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/exec.h"
#include "../../inc/shell.h"
#include "../../inc/globals.h"
#include "../../inc/signals.h"
#include "../../inc/utils.h"

void	heredoc_handle(t_data *data, char *file, char *dlimit)
{
	char *(input);
	int fd = open(file, O_WRONLY);
	if (!fd)
		return ;
	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			close(fd);
			free_n_exit(131, data->input);
		}
		if (!ft_strcmp(input, dlimit))
			break ;
		// need to add variable expansion
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
	}
	close(fd);
	free_n_exit(0, data->input);
}

int	heredoc_sig_status(char *dlimit, int status)
{
	if (WIFSIGNALED(status))
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return (0);
	}
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 130)
			return (0);
		else if (WEXITSTATUS(status) == 131)
			return(ft_printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", dlimit), 1);
	}	
	return (1);
}

int	heredoc_check(t_data *data)
{
	t_cmd *tmp = data->cmd;
	while (tmp)
	{
		t_redir *re_tmp = tmp->redir;
		while (re_tmp)
		{
			if (re_tmp->type == REDIR_HEREDOC)
			{
				re_tmp->file = get_heredoc_file();
				if (!re_tmp->file)
					return (print_error("try harder", 4), 0);
				int pid, status;
				pid = fork();
				if (!pid)
				{
					signals_heredoc_child();
					heredoc_handle(data, re_tmp->file, re_tmp->dlimit);
				}
				waitpid(pid, &status, 0);
				if (!heredoc_sig_status(re_tmp->dlimit, status))
					return (heredoc_cleanup(data->cmd), 0);
			}
			re_tmp = re_tmp->next;
		}
		tmp = tmp->next;
	}
	return (1);
}

char	*get_heredoc_file(void)
{
	for (long i = 0; i < LONG_MAX; i++)
	{
		char *file = ft_strjoin("/tmp/minishell_", ft_strjoin(ft_itoa(i), ".txt"));
		if (access(file , F_OK))
		{
			int fd = open(file, O_CREAT | O_TRUNC , 0644);
			close(fd);
			return (file);
		}
	}
	return (NULL);
}

void	heredoc_cleanup(t_cmd *cmd)
{
	t_cmd	*cmd_tmp;
	t_redir	*redir_tmp;

	cmd_tmp = cmd;
	while (cmd_tmp)
	{
		redir_tmp = cmd_tmp->redir;
		while (redir_tmp)
		{
			if (redir_tmp->type == REDIR_HEREDOC)
				unlink(redir_tmp->file);
			redir_tmp = redir_tmp->next;
		}
		cmd_tmp = cmd_tmp->next;
	}
}
