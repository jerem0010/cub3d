/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-neze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:20:00 by jle-neze          #+#    #+#             */
/*   Updated: 2025/10/29 18:20:00 by jle-neze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	draw_textured(t_game *g, t_texdraw d)
{
	double		wall_x;
	int			tex_x;
	double		step;
	double		tex_pos;
	t_texline	l;

	if (d.r->side == 0)
		wall_x = g->cam.pos_y + d.c.perp_dist * d.r->ray_dir_y;
	else
		wall_x = g->cam.pos_x + d.c.perp_dist * d.r->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)d.t->w);
	if ((d.r->side == 0 && d.r->ray_dir_x > 0)
		|| (d.r->side == 1 && d.r->ray_dir_y < 0))
		tex_x = d.t->w - tex_x - 1;
	step = (double)d.t->h / (double)d.c.line_h;
	tex_pos = (d.c.draw_start - g->gfx.h / 2 + d.c.line_h / 2) * step;
	l.tex = d.t;
	l.tex_x = tex_x;
	l.step = step;
	l.tex_pos = tex_pos;
	l.y0 = d.c.draw_start;
	l.y1 = d.c.draw_end;
	draw_tex_vline(g, d.x, l);
}

static void	set_tex_id(t_ray *r)
{
	if (r->side == 0)
	{
		if (r->step_x < 0)
			r->tex_id = 2;
		else
			r->tex_id = 3;
	}
	else
	{
		if (r->step_y < 0)
			r->tex_id = 1;
		else
			r->tex_id = 0;
	}
}

static void	draw_color_column(t_game *g, int x, t_ray *r, t_col c)
{
	t_vline	v;

	v.y0 = c.draw_start;
	v.y1 = c.draw_end;
	v.color = g->colors.wall_nsew[r->tex_id];
	if (r->side == 1)
		v.color = (v.color & 0xFEFEFE) >> 1;
	draw_vline(g, x, v);
}

void	draw_column(t_game *g, int x, t_ray *r)
{
	t_tex		*t;
	t_col		c;
	t_texdraw	d;

	if (r->side == 0)
		c.perp_dist = r->side_dist_x - r->delta_dist_x;
	else
		c.perp_dist = r->side_dist_y - r->delta_dist_y;
	if (c.perp_dist < 1e-6)
		c.perp_dist = 1e-6;
	c.line_h = (int)(g->gfx.h / c.perp_dist);
	c.draw_start = -c.line_h / 2 + g->gfx.h / 2;
	c.draw_end = c.line_h / 2 + g->gfx.h / 2;
	set_tex_id(r);
	if (!g->has_tex)
		return (draw_color_column(g, x, r, c));
	t = &g->tex[r->tex_id];
	d.x = x;
	d.r = r;
	d.t = t;
	d.c = c;
	draw_textured(g, d);
}
