/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:56:55 by mbarrah           #+#    #+#             */
/*   Updated: 2025/06/15 19:30:57 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>

int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		ft_strchr_ex(const char *s, char c);

int		ft_printf(const char *s, ...);
int		ft_putchar_ft(char c);
int		ft_putstr_ft(char *s);
int		ft_putnbr_unsigned_ft(unsigned int n);
int		ft_putnbr_ft(int n);
int		ft_putnbr_hexa_c_ft(unsigned int n);

char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_getenv(char *var, t_env *env);
char	*ft_strjoin_ex(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	**ft_envp(t_env *env);
char	*ft_strcpy(char *dest, char *src);
char	*ft_itoa(int n);

void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_strtol(char *str);
void	ft_strncat(char *dest, const char *src, size_t size);
void	ft_strncpy(char *dest, const char *src, size_t size);
void	ft_popnode(t_env **env, char *value);
void	*ft_malloc(size_t size, int flag);

size_t	ft_strlen(const char *str);

#endif