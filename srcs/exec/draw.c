/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-neze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:18:26 by jle-neze          #+#    #+#             */
/*   Updated: 2025/10/29 15:30:00 by jle-neze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_background(t_game *g)
{
	int	x;
	int	y;
	int	half;

	y = 0;
	half = g->gfx.h / 2;
	while (y < g->gfx.h)
	{
		x = 0;
		while (x < g->gfx.w)
		{
			if (y < half)
				img_put_pixel(&g->gfx.frame, x, y, g->colors.ceil);
			else
				img_put_pixel(&g->gfx.frame, x, y, g->colors.floor);
			x++;
		}
		y++;
	}
}

void	draw_vline(t_game *g, int x, t_vline v)
{
	int	y;

	if (v.y0 < 0)
		v.y0 = 0;
	if (v.y1 >= g->gfx.h)
		v.y1 = g->gfx.h - 1;
	y = v.y0;
	while (y <= v.y1)
	{
		img_put_pixel(&g->gfx.frame, x, y, v.color);
		y++;
	}
}

void	draw_tex_vline(t_game *g, int x, t_texline l)
{
	int				y;
	int				tex_y;
	unsigned int	color;

	if (l.y0 < 0)
	{
		l.tex_pos += l.step * (-l.y0);
		l.y0 = 0;
	}
	if (l.y1 >= g->gfx.h)
		l.y1 = g->gfx.h - 1;
	y = l.y0;
	while (y <= l.y1)
	{
		tex_y = (int)l.tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= l.tex->h)
			tex_y = l.tex->h - 1;
		color = tex_get_pixel(l.tex, l.tex_x, tex_y);
		img_put_pixel(&g->gfx.frame, x, y, (int)color);
		l.tex_pos += l.step;
		y++;
	}
}
