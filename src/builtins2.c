/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:12:46 by mbarrah           #+#    #+#             */
/*   Updated: 2025/05/01 17:50:48 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

static int	is_valid_flag(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	if (s[i] != '-')
		return (1);
	while (s[++i])
	{
		if (s[i] != 'n')
			return (1);
	}
	return (0);
}

void	ft_echo(t_cmd *cmd)
{
	int (n_flag), i = 1;
	n_flag = is_valid_flag(cmd->args[i]);
	if (!n_flag)
		while (!is_valid_flag(cmd->args[++i]))
			;
	while (cmd->args[i])
	{
		write(1, cmd->args[i], ft_strlen(cmd->args[i]));
		if (cmd->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (n_flag)
		write(1, "\n", 1);
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
	check_in(cmd, -1);
	check_out(cmd, -1);
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
