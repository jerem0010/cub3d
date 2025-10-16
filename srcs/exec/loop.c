/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-neze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:24:03 by jle-neze          #+#    #+#             */
/*   Updated: 2025/09/12 18:24:05 by jle-neze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	game_loop(t_game *g)
{
	/* 1) Update joueur selon input */
	player_update(g);
	/* 2) Dessin */
	draw_background(g);
	raycast_frame(g);
	mlx_put_image_to_window(g->gfx.mlx, g->gfx.win, g->gfx.frame.ptr, 0, 0);
	return (0);
}
/* Note: on pourrait optimiser en ne redessinant que ce qui change */
