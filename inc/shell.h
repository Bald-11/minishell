/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:56:58 by mbarrah           #+#    #+#             */
/*   Updated: 2025/05/05 16:37:59 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
#define SHELL_H

# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data t_data;
typedef struct s_cmd t_cmd;
typedef struct s_env t_env;
typedef struct s_redir t_redir;
typedef struct s_token t_token;

typedef enum e_token_type
{
	T_ARG,
	T_CMD,
	T_FLAG,
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
	int					quote;
	struct s_redir		*next;
}	t_redir;

typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
}   t_env;

typedef struct s_cmd
{
	char				**args;
	int					in;
	int					out;
	t_redir				*redir;
	t_data				*data;
	struct s_cmd		*next;
}	t_cmd;

typedef struct s_data
{
	int					status;
	int					cc;
	int					heredoc_f;
	int					**pipe;
	char				**envp;
	pid_t				*pid;
	t_env				*env;
	t_cmd				*cmd;
	t_token				*token;
	t_redir				*redir;
}	t_data;

void	free_data(t_data *data);

# include "utils.h"
# include "env.h"
# include "input.h"
# include "parser.h"
# include "exec.h"

#endif
