/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:57:21 by lfirmin           #+#    #+#             */
/*   Updated: 2025/10/08 16:21:46 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

int	init_data(t_data *data, char *path)
{
	if (!data)
		return (ft_error(ERROR_INIT_DATA), 1);
	data->texture = malloc(sizeof(t_textures));
	if (!data->texture)
		return (ft_error(ERROR_INIT_TEX), 1);
	init_parsing(&data->parsing);
	init_textures(data->texture);
	if (!data->texture)
	{
		free(data);
		return (1);
	}
	data->map = NULL;
	data->map_path = path;
	return (0);
}

int	world_init_from_parsing(t_world *world, t_data *data)
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

int	init_game_data(t_game *g, t_data *data, char *map_file)
{
	ft_memset(g, 0, sizeof(t_game));
	if (init_data(data, map_file))
		return (1);
	if (parsing(data))
	{
		free_textures(data->texture);
		free_data(data);
		return (1);
	}
	g->colors.floor = rgb_to_int(data->texture->floor[0],
			data->texture->floor[1], data->texture->floor[2]);
	g->colors.ceil = rgb_to_int(data->texture->ceiling[0],
			data->texture->ceiling[1], data->texture->ceiling[2]);
	if (world_init_from_parsing(&g->world, data) != 0)
		return (printf("World init failed\n"), 1);
	free_char_array(data->map);
	data->map = NULL;
	return (0);
}

void	init_player_direction(t_player_init *p, char direction)
{
	p->dx = 0;
	p->dy = 0;
	if (direction == 'S')
		p->dy = -1;
	else if (direction == 'N')
		p->dy = 1;
	else if (direction == 'E')
		p->dx = 1;
	else if (direction == 'W')
		p->dx = -1;
}

int	init_mlx_and_textures(t_game *g, t_data *data)
{
	t_texpaths	tex;

	if (init_window(g, 1024, 768, "cub3D") != 0)
		return (1);
	tex.no = data->texture->north;
	tex.so = data->texture->south;
	tex.we = data->texture->west;
	tex.ea = data->texture->east;
	if (textures_load(g, &tex) != 0)
		g->has_tex = 0;
	return (0);
}
