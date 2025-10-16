/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelghou <abelghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:32:47 by abelghou          #+#    #+#             */
/*   Updated: 2024/07/23 20:47:15 by abelghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strlen_g(const char *str);
char	*ft_strchr_gnl(const char *s, int i);
char	*ft_strdup_g(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*get_next_line(int fd);

#endif