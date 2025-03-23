/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:31:29 by yabarhda          #+#    #+#             */
/*   Updated: 2025/03/23 16:46:35 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

t_cmd *parse_tokens(t_token *tokens)
{
    t_cmd *cmd_head = NULL;
    t_cmd *current_cmd = NULL;
    int arg_index = 0;
    
    // Loop through tokens and build command structures
    while (tokens && tokens->type != T_EOF)
    {
        // Start a new command if needed
        if (!current_cmd) {
            current_cmd = create_command();
            if (!current_cmd)
                return NULL;
            // Link to list or set as head
        }
        
        // Handle different token types
        if (tokens->type == T_ARG) {
            // Add as command or argument
        }
        else if (tokens->type == T_PIPE) 
        {
            if (!token->next || token->next->type == T_PIPE || token->next->type == T_EOF) {
                return (printf("minishell: syntax error: unexpected token `|'\n"), NULL);
            }
            
            // Check if this is the first token (no command before pipe)
            if (first_token) {
                return (printf("minishell: syntax error near unexpected token `|'\n"), NULL);
            }
            // Finalize current command, prepare for next
        }
        else if (tokens->type == T_REDIR_OUT || tokens->type == T_APPEND) {
            // Handle output redirection
        }
        else if (tokens->type == T_REDIR_IN || tokens->type == T_HEREDOC) {
            // Handle input redirection
        }
        
        tokens = tokens->next;
    }
    
    return cmd_head;
}
