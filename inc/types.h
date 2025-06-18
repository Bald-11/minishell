/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 10:58:44 by yabarhda          #+#    #+#             */
/*   Updated: 2025/06/18 18:09:50 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <sys/types.h>

typedef struct s_data		t_data;
typedef struct s_cmd		t_cmd;
typedef struct s_env		t_env;
typedef struct s_redir		t_redir;
typedef struct s_token		t_token;
typedef struct s_mem		t_mem;
typedef enum e_token_type	t_token_type;
typedef enum e_redir_type	t_redir_type;

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

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

typedef struct s_redir
{
	t_redir_type		type;
	char				*file;
	char				*dlimit;
	int					quote;
	struct s_redir		*next;
}	t_redir;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}	t_env;

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
	char				*input;
	char				*hdoc_file;
	char				**envp;
	pid_t				*pid;
	t_env				*env;
	t_cmd				*cmd;
	t_token				*token;
	t_redir				*redir;
}	t_data;

typedef struct s_mem
{
	void				*ptr;
	struct s_mem		*next;
}	t_mem;

#endif