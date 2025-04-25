/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:12:46 by mbarrah           #+#    #+#             */
/*   Updated: 2025/04/25 16:20:39 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	ft_echo(char **args)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (args[1] && !ft_strcmp(args[1], "-n"))
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
}

static int	ft_exit_input(char *s, int *status)
{
	int (i), f = 0;
	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
		{
			f = 1;
			break ;
		}
		i++;
	}
	ft_strtol(s);
	if ((errno == ERANGE) || f)
	{
		printf("minishell: exit: %s: numeric argument required\n", s);
		*status = 2;
		return (0);		
	}
	*status = ft_atoi(s);
	return (1);
}

void	ft_exit(t_cmd *cmd)
{
	int (i);
	i = 0;
	while (cmd->args[i])
		i++;
	printf("exit\n");
	if (cmd->args[1])
	{
		if (!ft_exit_input(cmd->args[1], &cmd->data->status))
			exit_shell(cmd);
		if (i > 2)
		{
			printf("minishell: exit: too many arguments\n");
			cmd->data->status = 1;
			return ;
		}
	}
	exit_shell(cmd);
}
