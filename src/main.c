/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:28:19 by yabarhda          #+#    #+#             */
/*   Updated: 2025/03/18 21:58:04 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("$ ");
		if (!input)
			return (printf("exit\n"), 0);
		if (strlen(input) > 0)
			add_history(input);
		// process command
		free(input);
	}
	return (0);
}
