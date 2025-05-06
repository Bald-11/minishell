/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:57:04 by mbarrah           #+#    #+#             */
/*   Updated: 2025/05/06 17:04:04 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "shell.h"
# include "utils.h"
# include "env.h"
# include "input.h"
# include "parser.h"
# include "exec.h"

char	*get_input(void);

void	minishell(t_data *data);

#endif