/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:28:19 by yabarhda          #+#    #+#             */
/*   Updated: 2025/03/06 14:01:04 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

int	main(void)
{
	char	*prompt;
	char	*buf;
	buf = NULL;
	while (1)
	{
		prompt = readline("$ ");
		if (!strcmp(prompt, "exit"))
			break ;
		else if (!strcmp(prompt, "pwd"))
			printf("%s\n", getcwd(buf, 0));
		free(prompt);
	}
	free(prompt);
	return (0);
}
