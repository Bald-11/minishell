/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 15:28:17 by yabarhda          #+#    #+#             */
/*   Updated: 2025/06/18 18:17:29 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "types.h"

int		count_cmds(t_cmd *cmd);
int		isbuiltin(char *cmd);
int		is_valid_flag(char *s);
int		ft_exit_input(char *s, int *status);
int		heredoc_check(t_data *data);

char	*filename(char *cmd, t_data *data);
char	*get_heredoc_file(void);

void	check_access(char *file);
void	check_in(t_cmd *cmd, int index);
void	check_out(t_cmd *cmd, int index);
void	open_pipes(t_cmd *cmd);
void	close_all_pipes(t_data *data);
void	set_exit_status(int *status);
void	free_n_exit(int status, char *input);
void	print_error(char *str, int err);
void	exec_cmds(t_cmd *cmd);
void	update_env(t_env **head, char *value);
void	print_sorted_env(t_env *env);
void	exit_shell(t_cmd *cmd, int f);
void	exec_b(t_cmd *cmd);
void	execute(t_cmd *cmd, t_data *data, int i);
void	heredoc_handle(t_data *data, char *file, char *dlimit);
void	update_env_node(t_env *env, char *key, char *value);
void	heredoc_cleanup(t_cmd *cmd);

/* built-ins */

void	ft_cd(t_cmd *cmd, char *path);
void	ft_echo(t_cmd *cmd);
void	ft_pwd(t_cmd *cmd);
void	ft_export(t_cmd *cmd);
void	ft_unset(t_cmd *cmd);
void	ft_env(t_env *env);
void	ft_exit(t_cmd *cmd, int f);

/* end-of-built-ins */

#endif