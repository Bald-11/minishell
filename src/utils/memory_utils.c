/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtarza <mtarza@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 02:43:22 by yabarhda          #+#    #+#             */
/*   Updated: 2025/08/01 06:08:07 by mtarza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_redirections(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs;
		redirs = redirs->next;
		if (tmp->type == TOKEN_HEREDOC)
			unlink(tmp->target);
	}
}

void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->redirs)
		free_redirections(ast->redirs);
}
