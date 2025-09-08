#include "cub3d.h"

void	player_init(t_game *g, double px, double py, double dx, double dy)
{
	g->cam.pos_x = px;
	g->cam.pos_y = py;
	g->cam.dir_x = dx;
	g->cam.dir_y = dy;
	/* FOV ≈ 66° → plane perpendiculaire (0.66) */
	g->cam.plane_x = -dy * 0.66;
	g->cam.plane_y =  dx * 0.66;
	g->move_speed = 0.07; /* ajuste si besoin */
	g->rot_speed  = 0.05; /* rad/frame */
}

/* petits helpers collision */
static int is_wall(t_world *w, int mx, int my)
{
	if (mx < 0 || my < 0 || mx >= w->w || my >= w->h) return (1);
	return (w->grid[my][mx] == '1');
}

void	player_update(t_game *g)
{
	double nx, ny;

	/* Avancer/retour W/S */
	if (g->in.w)
	{
		nx = g->cam.pos_x + g->cam.dir_x * g->move_speed;
		ny = g->cam.pos_y + g->cam.dir_y * g->move_speed;
		if (!is_wall(&g->world, (int)nx, (int)g->cam.pos_y)) g->cam.pos_x = nx;
		if (!is_wall(&g->world, (int)g->cam.pos_x, (int)ny)) g->cam.pos_y = ny;
	}
	if (g->in.s)
	{
		nx = g->cam.pos_x - g->cam.dir_x * g->move_speed;
		ny = g->cam.pos_y - g->cam.dir_y * g->move_speed;
		if (!is_wall(&g->world, (int)nx, (int)g->cam.pos_y)) g->cam.pos_x = nx;
		if (!is_wall(&g->world, (int)g->cam.pos_x, (int)ny)) g->cam.pos_y = ny;
	}
	/* Strafe A/D (gauche/droite) */
	if (g->in.a)
	{
		nx = g->cam.pos_x - g->cam.dir_y * g->move_speed;
		ny = g->cam.pos_y + g->cam.dir_x * g->move_speed;
		if (!is_wall(&g->world, (int)nx, (int)g->cam.pos_y)) g->cam.pos_x = nx;
		if (!is_wall(&g->world, (int)g->cam.pos_x, (int)ny)) g->cam.pos_y = ny;
	}
	if (g->in.d)
	{
		nx = g->cam.pos_x + g->cam.dir_y * g->move_speed;
		ny = g->cam.pos_y - g->cam.dir_x * g->move_speed;
		if (!is_wall(&g->world, (int)nx, (int)g->cam.pos_y)) g->cam.pos_x = nx;
		if (!is_wall(&g->world, (int)g->cam.pos_x, (int)ny)) g->cam.pos_y = ny;
	}
	/* Rotation gauche/droite */
	if (g->in.left || g->in.right)
	{
		double rs = g->rot_speed * (g->in.right ? 1.0 : -1.0);
		double old_dir_x = g->cam.dir_x;
		g->cam.dir_x = g->cam.dir_x * cos(rs) - g->cam.dir_y * sin(rs);
		g->cam.dir_y = old_dir_x * sin(rs) + g->cam.dir_y * cos(rs);
		double old_plane_x = g->cam.plane_x;
		g->cam.plane_x = g->cam.plane_x * cos(rs) - g->cam.plane_y * sin(rs);
		g->cam.plane_y = old_plane_x * sin(rs) + g->cam.plane_y * cos(rs);
	}
}
