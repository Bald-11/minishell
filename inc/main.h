/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:27:32 by yabarhda          #+#    #+#             */
/*   Updated: 2025/04/25 16:26:32 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define RESET   "\033[0m"
# define BLACK   "\033[30m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"
# define BOLD    "\033[1m"

typedef enum e_token_type
{
	T_ARG,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
	T_DQUOTE,
	T_SQUOTE,
	T_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type		type;
	char				*file;
	struct s_redir		*next;
}	t_redir;

typedef struct s_data
{
	int					status;
	int					cc;
	int					heredoc_f;
	int					**pipe;
	char				**env;
	pid_t				*pid;
}	t_data;

typedef struct s_cmd
{
	char				**args;
	int					in;
	int					out;
	t_redir				*redir;
	t_data				*data;
	struct s_cmd		*next;
}	t_cmd;

void	shell_loop(t_data *data);
void	free_tokens(t_token *tokens);
void	add_token(t_token **head, t_token *new_token);
void	ft_strncpy(char *dest, const char *src, size_t size);
void	ft_strncat(char *dest, const char *src, size_t size);
void	skip_whites(char **input);
void	tokenize_redirects(t_token **head, char **input, t_data *data);
void	free_cmds(t_cmd *cmd);
void	single_quote_handle(t_token **head, char **input, char **result);
void	double_quote_handle(t_token **head, char **input, \
	char **result, t_data *data);
void	append_char(char **str, char c);
void	env_var_handle(char **input, char **result, t_data *data);
void	cd(char *path);
void	print_error(char *str, int err);
void	free_env(char **env);
void	free_n_exit(t_cmd *cmd, int status);
void	close_all_pipes(t_data *data);
void	check_access(char *file);
void	free_n_exit(t_cmd *cmd, int status);
void	check_in(t_cmd *cmd, int index);
void	check_out(t_cmd *cmd, int index);
void	set_exit_status(t_data *data);
void	exec_b(t_cmd *cmd);
void	ft_cd(char *path);
void	ft_echo(char **args);
void	ft_pwd(t_cmd *cmd);
void	ft_env(t_data *data);
void	exit_shell(t_cmd *cmd);
void	ft_exit(t_cmd *cmd);
void	ft_strtol(char *str);

int		word_len(char *input);
int		tokenize_else(t_token **head, char **input, t_data *data);
int		add_arg_to_cmd(t_cmd *cmd, char *arg);
int		add_redir(t_cmd *cmd, t_redir_type type, char *file);
int		ft_isalnum(int c);
int		ft_isspace(int c);
int		handle_redirection(t_cmd *cmd, t_token *token);
int		exec_cmds(t_cmd *cmd, t_data *data);
int		ft_strchr_ex(const char *s, char c);
int		ft_strcmp(char *s1, char *s2);
int		isbuiltin(char *cmd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		count_cmds(t_cmd *cmd);
int		ft_atoi(const char *str);

char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strcat(char *dest, char *src);
char	**ft_split(char const *s, char c);
char	*ft_strjoin_ex(char const *s1, char const *s2);
char	*ft_getenv(char *var, char **env);
char	*ft_itoa(int n);
char	*filename(char *cmd, t_data *data);

size_t	ft_strlen(const char *s);

t_token	*create_token(t_token_type type, char *value);
t_token	*tokenize_input(char *input, t_data *data);

t_cmd	*create_cmd(t_data *data);
t_cmd	*parse_tokens(t_token *token, t_data *data);
t_cmd	*init_cmd(t_cmd **head, t_data *data);

t_redir	*create_redir(t_redir_type type, char *file);

#endif
