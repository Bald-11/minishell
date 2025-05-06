/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:57:06 by mbarrah           #+#    #+#             */
/*   Updated: 2025/05/06 17:04:09 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "shell.h"
# include "utils.h"
# include "env.h"
# include "input.h"
# include "parser.h"
# include "exec.h"

t_env	*new_env_node(char *key, char *value);
t_env	*init_env(char **env);

void	add_env_node(t_env **env, t_env *new);
void	parse_env_var(t_env **env, char *env_str);
// void	free_env(t_env *env);
void	print_env(t_env *env);

#endif