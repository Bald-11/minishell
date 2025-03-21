/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:27:32 by yabarhda          #+#    #+#             */
/*   Updated: 2025/03/21 19:52:02 by yabarhda         ###   ########.fr       */
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
}   t_token_type;

typedef struct s_token
{
    t_token_type   type;
    char           *value;
    struct s_token *next;
}   t_token;

typedef struct s_command
{
    char    **args;
    char    *input_file;
    char    *output_file;
    int     append_mode;
    char    *heredoc_delim;
    struct s_command *next;
}   t_command;

#endif
