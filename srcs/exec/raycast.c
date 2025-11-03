/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-neze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:15:00 by jle-neze          #+#    #+#             */
/*   Updated: 2025/10/29 18:15:00 by jle-neze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	init_ray_vars(t_game *g, int x, t_ray *r)
{
	double	cam;

	cam = 2.0 * x / (double)g->gfx.w - 1.0;
	r->ray_dir_x = g->cam.dir_x + g->cam.plane_x * cam;
	r->ray_dir_y = g->cam.dir_y + g->cam.plane_y * cam;
	r->map_x = (int)g->cam.pos_x;
	r->map_y = (int)g->cam.pos_y;
	if (r->ray_dir_x == 0)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1.0 / r->ray_dir_x);
	if (r->ray_dir_y == 0)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1.0 / r->ray_dir_y);
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
