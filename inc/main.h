/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:27:32 by yabarhda          #+#    #+#             */
/*   Updated: 2025/03/30 20:30:43 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

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

typedef struct s_cmd
{
	char				**args;
	t_redir				*redir;
	struct s_cmd		*next;
}	t_cmd;

void	shell_loop(void);
void	free_tokens(t_token *tokens);
void	add_token(t_token **head, t_token *new_token);
void	ft_strncpy(char *dest, const char *src, size_t size);
void	ft_strncat(char *dest, const char *src, size_t size);
void	skip_whites(char **input);
void	tokenize_redirects(t_token **head, char **input);
void	free_cmds(t_cmd *cmd);
void	single_quote_handle(char **input, char **result);
void	double_quote_handle(char **input, char **result);
void	append_char(char **str, char c);
void	env_var_handle(char **input, char **result);

int		word_len(char *input);
int		tokenize_else(t_token **head, char **input);
int		add_arg_to_cmd(t_cmd *cmd, char *arg);
int		add_redir(t_cmd *cmd, t_redir_type type, char *file);
int		ft_isalnum(int c);
int		ft_isspace(int c);
int		handle_redirection(t_cmd *cmd, t_token *token);

char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strcat(char *dest, char *src);

size_t	ft_strlen(const char *s);

t_token	*create_token(t_token_type type, char *value);
t_token	*tokenize_input(char *input);

t_cmd	*create_cmd(void);
t_cmd	*parse_tokens(t_token *token);
t_cmd	*init_cmd(t_cmd **head);

t_redir	*create_redir(t_redir_type type, char *file);

#endif
