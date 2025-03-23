/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:27:32 by yabarhda          #+#    #+#             */
/*   Updated: 2025/03/23 14:17:49 by yabarhda         ###   ########.fr       */
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
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char				**args;
	char				*input_file;
	char				*output_file;
	int					append_mode;
	char				*heredoc_delim;
	struct s_cmd	*next;
}	t_cmd;

void	shell_loop(void);
void	free_tokens(t_token *tokens);
void	add_token(t_token **head, t_token *new_token);
void	ft_strncpy(char *dest, const char *src, size_t size);
void	ft_strncat(char *dest, const char *src, size_t size);
void	skip_whites(char **input);
void	tokenize_redirects(t_token **head, char **input);

int		word_len(char *input);
int		tokenize_else(t_token **head, char **input);
int		single_quote_handle(t_token **head, char **input, char quote);

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);

size_t	ft_strlen(const char *s);

t_token	*create_token(t_token_type type, char *value);
t_token	*tokenize_input(char *input);

#endif
