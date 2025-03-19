/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:28:19 by yabarhda          #+#    #+#             */
/*   Updated: 2025/03/19 22:25:02 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

char	*mini_line()
{
	char	*input;

	input = readline("$ ");
	if (input && input[0])
		add_history(input);
	return (input);
}

void	mini_loop()
{
	char	*input;

	while (1)
	{
		input = mini_line();
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		free(input);
	}
}

int	main(void)
{
	mini_loop();
	return (0);
}
