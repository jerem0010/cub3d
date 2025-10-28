/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-neze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:15:00 by jle-neze          #+#    #+#             */
/*   Updated: 2025/10/29 16:15:00 by jle-neze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <math.h>

static void	init_ray_vars(t_game *g, int x, t_ray *r)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)g->gfx.w - 1.0;
	r->ray_dir_x = g->cam.dir_x + g->cam.plane_x * camera_x;
	r->ray_dir_y = g->cam.dir_y + g->cam.plane_y * camera_x;
	r->map_x = (int)g->cam.pos_x;
	r->map_y = (int)g->cam.pos_y;
	r->delta_dist_x = fabs(1.0 / (r->ray_dir_x + (r->ray_dir_x == 0)));
	r->delta_dist_y = fabs(1.0 / (r->ray_dir_y + (r->ray_dir_y == 0)));
}

static void	calc_step_side(t_game *g, t_ray *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (g->cam.pos_x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - g->cam.pos_x) * r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (g->cam.pos_y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - g->cam.pos_y) * r->delta_dist_y;
	}
}

static void	perform_dda(t_game *g, t_ray *r)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_x < 0 || r->map_y < 0 || r->map_x >= g->world.w
			|| r->map_y >= g->world.h
			|| g->world.grid[r->map_y][r->map_x] == '1')
			hit = 1;
	}
}

static void	draw_column(t_game *g, int x, t_ray *r)
{
	double	perp_wall_dist;
	int		line_h;
	int		draw_start;
	int		draw_end;
	t_vline	v;
	t_texline	l;
	t_tex		*t;

	perp_wall_dist = (r->side == 0)
		? (r->side_dist_x - r->delta_dist_x)
		: (r->side_dist_y - r->delta_dist_y);
	if (perp_wall_dist < 1e-6)
		perp_wall_dist = 1e-6;
	line_h = (int)(g->gfx.h / perp_wall_dist);
	draw_start = -line_h / 2 + g->gfx.h / 2;
	draw_end = line_h / 2 + g->gfx.h / 2;
	r->tex_id = (r->side == 0)
		? ((r->step_x < 0) ? 2 : 3)
		: ((r->step_y < 0) ? 1 : 0);
	if (!g->has_tex)
	{
		v.y0 = draw_start;
		v.y1 = draw_end;
		v.color = g->colors.wall_nsew[r->tex_id];
		if (r->side == 1)
			v.color = (v.color & 0xFEFEFE) >> 1;
		draw_vline(g, x, v);
		return ;
	}
	t = &g->tex[r->tex_id];
	draw_textured_column(g, x, r, t, draw_start, line_h);
}

void	draw_textured_column(t_game *g, int x, t_ray *r, t_tex *t,
	int draw_start, int line_h)
{
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	t_texline	l;

	if (r->side == 0)
		wall_x = g->cam.pos_y + (r->side_dist_x - r->delta_dist_x) * r->ray_dir_y;
	else
		wall_x = g->cam.pos_x + (r->side_dist_y - r->delta_dist_y) * r->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)t->w);
	if ((r->side == 0 && r->ray_dir_x > 0) || (r->side == 1 && r->ray_dir_y < 0))
		tex_x = t->w - tex_x - 1;
	step = (double)t->h / (double)line_h;
	tex_pos = (draw_start - g->gfx.h / 2 + line_h / 2) * step;
	l.tex = t;
	l.tex_x = tex_x;
	l.step = step;
	l.tex_pos = tex_pos;
	l.y0 = draw_start;
	l.y1 = draw_start + line_h;
	draw_tex_vline(g, x, l);
}

void	raycast_frame(t_game *g)
{
	int		x;
	t_ray	r;

	x = 0;
	while (x < g->gfx.w)
	{
		init_ray_vars(g, x, &r);
		calc_step_side(g, &r);
		perform_dda(g, &r);
		draw_column(g, x, &r);
		x++;
	}
}
