/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:56:25 by lfirmin           #+#    #+#             */
/*   Updated: 2025/10/07 12:14:42 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_error(char *message)
{
	int	len;

	len = 0;
	while (message[len])
		len++;
	write(2, ERROR_PREFIX, 6);
	write(2, message, len);
	write(2, "\n", 1);
}

void	free_char_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int	ft_arrlen(char **arr)
{
	int	i;

	while (arr[i])
		i++;
	return (i);
}

void	print_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		printf("%s", array[i]);
		i++;
	}
}

int	ft_strlen_2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}
