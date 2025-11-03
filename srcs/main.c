/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:56:25 by lfirmin           #+#    #+#             */
/*   Updated: 2025/11/03 09:06:01 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

int	setup_and_run(t_game *g, t_data *data)
{
	t_player_init	p;

	p.px = data->parsing.player[0] + 0.5;
	p.py = data->parsing.player[1] + 0.5;
	init_player_direction(&p, data->parsing.player[2]);
	player_init(g, p);
	if (init_mlx_and_textures(g, data) != 0)
		return (1);
	g->data = data;
	setup_hooks(g);
	get_next_line(-2);
	mlx_loop(g->gfx.mlx);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	g;
	t_data	data;

	if (ac != 2)
		return (printf("Usage: ./cub3d <map.cub>\n"), 1);
	if (init_game_data(&g, &data, av[1]) != 0)
		return (1);
	if (setup_and_run(&g, &data) != 0)
		return (1);
	world_free(&g.world);
	free_textures(data.texture);
	free_data(&data);
	return (0);
}
