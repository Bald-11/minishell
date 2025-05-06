/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:57:01 by mbarrah           #+#    #+#             */
/*   Updated: 2025/05/06 17:04:02 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "shell.h"
# include "utils.h"
# include "env.h"
# include "input.h"
# include "parser.h"
# include "exec.h"

int				check_quotes(char *input);
int				is_quote(char c);
int				is_whitespace(char c);
int				is_special_char(char c);
int				is_flag(char *str);
int				check_syntax(t_token *tokens);
int				check_pipe_syntax(t_token *tokens);
int				check_redirection_syntax(t_token *tokens);
int				add_arg_to_cmd(t_cmd *cmd, char *arg_value);
int				process_redirection(t_cmd *cmd, t_token **current);
int				is_env_char(char c);

char			*extract_token_value(char *input, int *i);
char			*extract_quoted_token(char *input, int *i, char quote_type);
char			*expand_env_vars(char *str, t_env *env);
char			*get_env_value(char *key, t_env *env);

void			add_token(t_token **head, t_token *new_token);
void			free_tokens(t_token *head);
void			print_tokens(t_token *head);
void			reset_token_state(void);
void			add_cmd(t_cmd **head, t_cmd *new_cmd);
void			add_redir(t_redir **head, t_redir *new_redir);
void			free_cmd(t_cmd *cmd);
void			free_all_cmds(t_cmd *head);
void			print_cmds(t_cmd *head);
void			expand_tokens(t_token *tokens, t_env *env);

t_token			*tokenize(char *input);
t_token			*create_token(t_token_type type, char *value);

t_cmd			*create_cmd(t_data *data);
t_cmd			*parse_commands(t_token *tokens, t_data *data);

t_redir			*create_redir(t_redir_type type, char *file);

t_token_type	get_token_type(char *str);

#endif