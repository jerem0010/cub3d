/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:56:25 by lfirmin           #+#    #+#             */
/*   Updated: 2025/10/08 16:25:42 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

void	print_int_array(int *array, int size)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (i < size)
	{
		ft_putnbr_fd(array[i], 1);
		if (i < size - 1)
			write(1, ", ", 2);
		i++;
	}
	write(1, "\n", 1);
}
void debug(t_data data)
{
	printf("map:\n\n");
	print_array(data.map);
	printf("\n");
	printf("c: ");
	fflush(stdout);
	print_int_array(data.texture->ceiling, 3);
	printf("f: ");
	fflush(stdout);
	print_int_array(data.texture->floor, 3);
	printf("p: ");
	fflush(stdout);
	print_int_array(data.parsing.player, 3);
	printf("\n");
	printf("\ntexture:\n\n");
	printf("%s\n", data.texture->east);
	printf("%s\n", data.texture->north);
	printf("%s\n", data.texture->west);
	printf("%s\n", data.texture->south);
}
int	main(int ac, char **av)
{
	t_data	data;

	init_data(&data, av[1]);
	if (parsing(&data));
		debug(data);
	free_char_array(data.parsing.raw_map);
	free_textures(data.texture);
	free_data(&data);
}
