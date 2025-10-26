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

// void	print_int_array(int *array, int size)
// {
// 	int	i;

// 	if (!array)
// 		return ;
// 	i = 0;
// 	while (i < size)
// 	{
// 		ft_putnbr_fd(array[i], 1);
// 		if (i < size - 1)
// 			write(1, ", ", 2);
// 		i++;
// 	}
// 	write(1, "\n", 1);
// }
// void debug(t_data data)
// {
// 	printf("map:\n\n");
// 	print_array(data.map);
// 	printf("\n");
// 	printf("c: ");
// 	fflush(stdout);
// 	print_int_array(data.texture->ceiling, 3);
// 	printf("f: ");
// 	fflush(stdout);
// 	print_int_array(data.texture->floor, 3);
// 	printf("p: ");
// 	fflush(stdout);
// 	print_int_array(data.parsing.player, 3);
// 	printf("\n");
// 	printf("\ntexture:\n\n");
// 	printf("%s\n", data.texture->east);
// 	printf("%s\n", data.texture->north);
// 	printf("%s\n", data.texture->west);
// 	printf("%s\n", data.texture->south);
// }

// int	main(int ac, char **av)
// {
// 	t_data	data;

// 	init_data(&data, av[1]);
// 	if (parsing(&data));
// 		debug(data);
// 	free_char_array(data.parsing.raw_map);
// 	free_textures(data.texture);
// 	free_data(&data);
// }

int rgb_to_int(int r, int g, int b)
{
	if (r < 0) r = 0;
	if (r > 255) r = 255;
	if (g < 0) g = 0;
	if (g > 255) g = 255;
	if (b < 0) b = 0;
	if (b > 255) b = 255;
	return ((r << 16) | (g << 8) | b);
}

static int	world_init_from_parsing(t_world *world, t_data *data)
{
	int	y;

	world->h = 0;
	while (data->map[world->h])
		world->h++;
	world->w = ft_strlen(data->map[0]);

	world->grid = malloc(sizeof(char *) * (world->h + 1));
	if (!world->grid)
		return (1);
	y = 0;
	while (y < world->h)
	{
		world->grid[y] = ft_strdup(data->map[y]);
		if (!world->grid[y])
			return (1);
		y++;
	}
	world->grid[world->h] = NULL;
	return (0);
}


// int	main(int ac, char **av)
// {
// 	t_game	g;
// 	t_data	data;

// 	if (ac != 2)
// 		return (printf("Usage: ./cub3d <map.cub>\n"), 1);

// 	init_data(&data, av[1]);
// 	if (parsing(&data))
// 		return (printf("Parsing error\n"), 1);
// 	free_char_array(data.parsing.raw_map);

// 	/* init couleurs et textures */
// 	g.colors.floor = rgb_to_int(data.texture->floor[0], data.texture->floor[1], data.texture->floor[2]); // ok jai change le fonction rgb_to_int elle attend 3 int le r le g et le b 
// 	g.colors.ceil  = rgb_to_int(data.texture->ceiling[0], data.texture->ceiling[1], data.texture->ceiling[2]);
// 	if (textures_load(&g,
// 			data.texture->north, data.texture->south,
// 			data.texture->west, data.texture->east) != 0)
// 		g.has_tex = 0;

// 	/* init map et player */
// 	if (world_init_from_parsing(&g.world, &data) != 0)
// 		return (printf("World init failed\n"), 1);
// 	double dx = 0, dy = 0;
// 	if (data.parsing.player[2] == 'N') dy = -1;
// 	if (data.parsing.player[2] == 'S') dy =  1;
// 	if (data.parsing.player[2] == 'E') dx =  1;
// 	if (data.parsing.player[2] == 'W') dx = -1;
// 	player_init(&g,
// 		data.parsing.player[0] + 0.5,
// 		data.parsing.player[1] + 0.5,
// 		dx, dy);

// 	/* window + loop */
// 	if (init_window(&g, 1024, 768, "cub3D") != 0)
// 		return (1);
// 	setup_hooks(&g);
// 	mlx_loop(g.gfx.mlx);

// 	world_free(&g.world);
// 	free_data(&data);
// 	return (0);
// }

int	main(int ac, char **av)
{
	t_game	g;
	t_data	data;

	if (ac != 2)
		return (printf("Usage: ./cub3d <map.cub>\n"), 1);

	memset(&g, 0, sizeof(t_game));  // IMPORTANT : initialiser g

	init_data(&data, av[1]);
	if (parsing(&data))
	{
		free_textures(data.texture);
		free_data(&data);
		return (1);
	}

	/* init couleurs */
	g.colors.floor = rgb_to_int(data.texture->floor[0], data.texture->floor[1], data.texture->floor[2]);
	g.colors.ceil  = rgb_to_int(data.texture->ceiling[0], data.texture->ceiling[1], data.texture->ceiling[2]);

	/* init map et player */
	if (world_init_from_parsing(&g.world, &data) != 0)
		return (printf("World init failed\n"), 1);
	/* Libérer data->map après la duplication vers world->grid */
	free_char_array(data.map);
	data.map = NULL;
	
	double dx = 0, dy = 0;
	if (data.parsing.player[2] == 'S') dy = -1;
	if (data.parsing.player[2] == 'N') dy =  1;
	if (data.parsing.player[2] == 'E') dx =  1;
	if (data.parsing.player[2] == 'W') dx = -1;
	player_init(&g,
		data.parsing.player[0] + 0.5,
		data.parsing.player[1] + 0.5,
		dx, dy);

	/* window AVANT textures ! */
	if (init_window(&g, 1024, 768, "cub3D") != 0)
		return (1);

	/* MAINTENANT on charge les textures */
	if (textures_load(&g,
			data.texture->north, data.texture->south,
			data.texture->west, data.texture->east) != 0)
		g.has_tex = 0;

	/* Passer data à g pour le cleanup */
	g.data = &data;
	
	setup_hooks(&g);
	/* Vider le buffer gnl avant de rentrer dans mlx_loop */
	get_next_line(-2);
	mlx_loop(g.gfx.mlx);

	world_free(&g.world);
	free_textures(data.texture);
	free_data(&data);

	return (0);
}