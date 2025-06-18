/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:20:46 by yabarhda          #+#    #+#             */
/*   Updated: 2025/06/18 19:45:31 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

void	handle_sigint(int sig);
void	signals_interactive(void);
void	signals_child(void);
void	signals_exec(void);
void	signals_heredoc(void);

#endif