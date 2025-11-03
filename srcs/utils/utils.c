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

int	rgb_to_int(int r, int g, int b)
{
	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}
