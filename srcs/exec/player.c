/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-neze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 16:20:00 by jle-neze          #+#    #+#             */
/*   Updated: 2025/10/28 16:20:00 by jle-neze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <math.h>

void	player_init(t_game *g, t_player_init p)
{
	g->cam.pos_x = p.px;
	g->cam.pos_y = p.py;
	g->cam.dir_x = p.dx;
	g->cam.dir_y = p.dy;
	g->cam.plane_x = -p.dy * 0.66;
	g->cam.plane_y = p.dx * 0.66;
	g->move_speed = 0.07;
	g->rot_speed = 0.05;
}

static int	is_wall(t_world *w, int mx, int my)
{
	if (mx < 0 || my < 0 || mx >= w->w || my >= w->h)
		return (1);
	return (w->grid[my][mx] == '1');
}

static void	player_move(t_game *g, double dx, double dy)
{
	double	nx;
	double	ny;

	nx = g->cam.pos_x + dx * g->move_speed;
	ny = g->cam.pos_y + dy * g->move_speed;
	if (!is_wall(&g->world, (int)nx, (int)g->cam.pos_y))
		g->cam.pos_x = nx;
	if (!is_wall(&g->world, (int)g->cam.pos_x, (int)ny))
		g->cam.pos_y = ny;
}

static void	player_rotate(t_game *g, int dir)
{
	double	rs;
	double	old_dir_x;
	double	old_plane_x;

	rs = g->rot_speed * (dir);
	old_dir_x = g->cam.dir_x;
	g->cam.dir_x = g->cam.dir_x * cos(rs) - g->cam.dir_y * sin(rs);
	g->cam.dir_y = old_dir_x * sin(rs) + g->cam.dir_y * cos(rs);
	old_plane_x = g->cam.plane_x;
	g->cam.plane_x = g->cam.plane_x * cos(rs) - g->cam.plane_y * sin(rs);
	g->cam.plane_y = old_plane_x * sin(rs) + g->cam.plane_y * cos(rs);
}

void	player_update(t_game *g)
{
	if (g->in.w)
		player_move(g, g->cam.dir_x, g->cam.dir_y);
	if (g->in.s)
		player_move(g, -g->cam.dir_x, -g->cam.dir_y);
	if (g->in.a)
		player_move(g, -g->cam.dir_y, g->cam.dir_x);
	if (g->in.d)
		player_move(g, g->cam.dir_y, -g->cam.dir_x);
	if (g->in.left)
		player_rotate(g, -1);
	else if (g->in.right)
		player_rotate(g, 1);
}
