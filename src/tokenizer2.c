/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:01:24 by yabarhda          #+#    #+#             */
/*   Updated: 2025/03/24 20:44:36 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/main.h"

void	append_char(char **str, char c)
{
	char *(new);
	int (len);
	len = ft_strlen(*str);
	new = (char *)malloc(len + 2);
	ft_strcpy(new, *str);
	new[len] = c;
	new[len + 1] = '\0';
	free(*str);
	*str = new;
}

void	append_string(char **str, char *append)
{
	char *(new);
	new = (char *)malloc(ft_strlen(*str) + ft_strlen(append) + 1);
	ft_strcpy(new, *str);
	ft_strcat(new, append);
	free(*str);
	*str = new;
}

void	env_var_handle(char **input, char **result)
{
	(*input)++;
	int (i);
	char *(var_name), *(value);
	var_name = (char *)malloc(1);
	if (!var_name)
		return ;
	var_name[0] = '\0';
	i = 0;
	while (ft_isalnum((*input)[i]))
		append_char(&var_name, (*input)[i++]);
	if (var_name[0] != '\0')
	{
		value = getenv(var_name);
		if (value)
			append_string(result, value);
	}
	else
		append_char(result, '$');
	free(var_name);
	*input += i;
}

int	tokenize_else(t_token **head, char **input)
{
	char *(result);
	result = malloc(1);
	if (!result)
		return (0);
	result[0] = '\0';
	while (**input && !ft_isspace(**input) && **input != '|'
		&& **input != '>' && **input != '<')
	{
		if (**input == '\'')
			single_quote_handle(input, &result);
		else if (**input == '"')
			double_quote_handle(input, &result);
		else if (**input == '$')
			env_var_handle(input, &result);
		else
		{
			append_char(&result, **input);
			(*input)++;
		}
	}
	if (result[0] != '\0')
		add_token(head, create_token(T_ARG, result));
	free(result);
	(*input)--;
	return (1);
}
