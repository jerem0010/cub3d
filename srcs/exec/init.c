/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-neze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:20:06 by jle-neze          #+#    #+#             */
/*   Updated: 2025/09/12 18:20:08 by jle-neze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	init_window(t_game *g, int w, int h, char *title)
{
	g->gfx.w = w;
	g->gfx.h = h;
	g->gfx.mlx = mlx_init();
	if (!g->gfx.mlx)
		return (1);
	g->gfx.win = mlx_new_window(g->gfx.mlx, w, h, title);
	if (!g->gfx.win)
		return (1);
	g->gfx.frame.ptr = mlx_new_image(g->gfx.mlx, w, h);
	if (!g->gfx.frame.ptr)
		return (1);
	g->gfx.frame.addr = mlx_get_data_addr(g->gfx.frame.ptr, &g->gfx.frame.bpp,
			&g->gfx.frame.line_len, &g->gfx.frame.endian);
	g->gfx.frame.w = w;
	g->gfx.frame.h = h;
	return (0);
}

void	cleanup_window(t_game *g)
{
	if (!g)
		return ;
	if (g->gfx.frame.ptr)
	{
		mlx_destroy_image(g->gfx.mlx, g->gfx.frame.ptr);
		g->gfx.frame.ptr = NULL;
	}
	if (g->gfx.win)
	{
		mlx_destroy_window(g->gfx.mlx, g->gfx.win);
		g->gfx.win = NULL;
	}
	if (g->gfx.mlx)
	{
		mlx_destroy_display(g->gfx.mlx);
		free(g->gfx.mlx);
		g->gfx.mlx = NULL;
	}
}
