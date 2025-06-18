/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:08:11 by yabarhda          #+#    #+#             */
/*   Updated: 2025/06/18 18:22:56 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/shell.h"
#include "../../inc/utils.h"
#include "../../inc/parser.h"
#include "../../inc/exec.h"

void	append_char(char **str, char c)
{
	char *(new);
	int (len);
	len = ft_strlen(*str);
	new = (char *)ft_malloc(len + 2, 64);
	ft_strcpy(new, *str);
	new[len] = c;
	new[len + 1] = '\0';
	*str = new;
}

/*static int	mini_env_expand(t_data *data, char *input, int fd, int *j)
{
	char *(tmp), *(value);
	tmp = ft_strdup("");
	if (!tmp)
		return (0);
	while (is_env_char(input[*j]))
		append_char(&tmp, input[(*j)++]);
	if (tmp[0])
	{
		value = ft_getenv(tmp, data->env);
		if (value)
			write(fd, value, ft_strlen(value));
		else
			return (0);
	}
	else
		return (0);
	return (1);
}

static void	heredoc_env(t_data *data, char *input, int fd)
{
	int (i), j = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$')
		{
			j = i + 1;
			if (!mini_env_expand(data, input, fd, &j))
				return ;
			i += j;
		}
		else
		{
			write(fd, &input[i], 1);
			i++;
		}
	}
}*/
