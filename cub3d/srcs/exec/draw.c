/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-neze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:18:26 by jle-neze          #+#    #+#             */
/*   Updated: 2025/09/12 18:18:52 by jle-neze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_game *g)
{
	int	x, y, half = g->gfx.h / 2;

	for (y = 0; y < g->gfx.h; y++)
	{
		for (x = 0; x < g->gfx.w; x++)
		{
			if (y < half)
				img_put_pixel(&g->gfx.frame, x, y, g->colors.ceil);
			else
				img_put_pixel(&g->gfx.frame, x, y, g->colors.floor);
		}
	}
}

/* aussi exposée dans raycast.c, mais on garde la déclaration ici pour réutiliser ailleurs */
void	draw_vline(t_game *g, int x, int y0, int y1, int color)
{
	if (y0 < 0) y0 = 0;
	if (y1 >= g->gfx.h) y1 = g->gfx.h - 1;
	for (int y = y0; y <= y1; y++)
		img_put_pixel(&g->gfx.frame, x, y, color);
}

void	draw_tex_vline(t_game *g, int x, int y0, int y1,
		t_tex *tex, int tex_x, double step, double tex_pos)
{
	if (y0 < 0)
	{
		tex_pos += step * (-y0);
		y0 = 0;
	}
	if (y1 >= g->gfx.h)
		y1 = g->gfx.h - 1;
	for (int y = y0; y <= y1; y++)
	{
		int tex_y = (int)tex_pos;
		if (tex_y < 0) tex_y = 0;
		if (tex_y >= tex->h) tex_y = tex->h - 1;
		unsigned int color = tex_get_pixel(tex, tex_x, tex_y);
		img_put_pixel(&g->gfx.frame, x, y, (int)color);
		tex_pos += step;
	}
}
