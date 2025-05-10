/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:20:46 by yabarhda          #+#    #+#             */
/*   Updated: 2025/05/09 15:22:20 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "shell.h"
# include "utils.h"
# include "env.h"
# include "input.h"
# include "parser.h"
# include "exec.h"

void	handle_sigint(int sig);
void	handle_sigint_exec(int sig);
void	setup_signals_interactive(void);
void	setup_signals_child(void);
void	setup_signals_exec(void);

#endif