#include "cub3d.h"

// /* petite fonction utilitaire: trace une ligne verticale remplie */
// void	draw_vline(t_game *g, int x, int y0, int y1, int color)
// {
// 	if (y0 < 0) y0 = 0;
// 	if (y1 >= g->gfx.h) y1 = g->gfx.h - 1;
// 	for (int y = y0; y <= y1; y++)
// 		img_put_pixel(&g->gfx.frame, x, y, color);
// }

// void	raycast_frame(t_game *g)
// {
// 	for (int x = 0; x < g->gfx.w; x++)
// 	{
// 		double camera_x = 2.0 * x / (double)g->gfx.w - 1.0;
// 		double ray_dir_x = g->cam.dir_x + g->cam.plane_x * camera_x;
// 		double ray_dir_y = g->cam.dir_y + g->cam.plane_y * camera_x;

// 		int map_x = (int)g->cam.pos_x;
// 		int map_y = (int)g->cam.pos_y;

// 		double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray_dir_x);
// 		double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1.0 / ray_dir_y);

// 		int step_x, step_y;
// 		double side_dist_x, side_dist_y;

// 		if (ray_dir_x < 0)
// 		{
// 			step_x = -1;
// 			side_dist_x = (g->cam.pos_x - map_x) * delta_dist_x;
// 		}
// 		else
// 		{
// 			step_x = 1;
// 			side_dist_x = (map_x + 1.0 - g->cam.pos_x) * delta_dist_x;
// 		}
// 		if (ray_dir_y < 0)
// 		{
// 			step_y = -1;
// 			side_dist_y = (g->cam.pos_y - map_y) * delta_dist_y;
// 		}
// 		else
// 		{
// 			step_y = 1;
// 			side_dist_y = (map_y + 1.0 - g->cam.pos_y) * delta_dist_y;
// 		}

// 		int hit = 0;
// 		int side = 0; /* 0:x, 1:y */

// 		while (!hit)
// 		{
// 			if (side_dist_x < side_dist_y)
// 			{
// 				side_dist_x += delta_dist_x;
// 				map_x += step_x;
// 				side = 0;
// 			}
// 			else
// 			{
// 				side_dist_y += delta_dist_y;
// 				map_y += step_y;
// 				side = 1;
// 			}
// 			if (map_x < 0 || map_y < 0 || map_x >= g->world.w || map_y >= g->world.h
// 				|| g->world.grid[map_y][map_x] == '1')
// 				hit = 1;
// 		}
// 		double perp_wall_dist;
// 		if (side == 0)
// 			perp_wall_dist = (side_dist_x - delta_dist_x);
// 		else
// 			perp_wall_dist = (side_dist_y - delta_dist_y);

// 		int line_h = (int)(g->gfx.h / (perp_wall_dist > 1e-6 ? perp_wall_dist : 1e-6));
// 		int draw_start = -line_h / 2 + g->gfx.h / 2;
// 		int draw_end = line_h / 2 + g->gfx.h / 2;

// 		/* Couleur: simple code NSEW selon step & side */
// 		int color_idx;
// 		if (side == 0)
// 			color_idx = (step_x < 0) ? 2 /* E */ : 3 /* W */;
// 		else
// 			color_idx = (step_y < 0) ? 1 /* S */ : 0 /* N */;

// 		int color = g->colors.wall_nsew[color_idx];
// 		if (side == 1) color = (color & 0xFEFEFE) >> 1; /* ombre simple */

// 		draw_vline(g, x, draw_start, draw_end, color);
// 	}
// }

/* 2eme test de la meme focntion (pas encore choisi laquelle)*/

void	raycast_frame(t_game *g)
{
	for (int x = 0; x < g->gfx.w; x++)
	{
		double camera_x = 2.0 * x / (double)g->gfx.w - 1.0;
		double ray_dir_x = g->cam.dir_x + g->cam.plane_x * camera_x;
		double ray_dir_y = g->cam.dir_y + g->cam.plane_y * camera_x;

		int map_x = (int)g->cam.pos_x;
		int map_y = (int)g->cam.pos_y;

		double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray_dir_x);
		double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1.0 / ray_dir_y);

		int step_x, step_y;
		double side_dist_x, side_dist_y;

		if (ray_dir_x < 0) { step_x = -1; side_dist_x = (g->cam.pos_x - map_x) * delta_dist_x; }
		else               { step_x =  1; side_dist_x = (map_x + 1.0 - g->cam.pos_x) * delta_dist_x; }
		if (ray_dir_y < 0) { step_y = -1; side_dist_y = (g->cam.pos_y - map_y) * delta_dist_y; }
		else               { step_y =  1; side_dist_y = (map_y + 1.0 - g->cam.pos_y) * delta_dist_y; }

		int hit = 0, side = 0;
		while (!hit)
		{
			if (side_dist_x < side_dist_y) { side_dist_x += delta_dist_x; map_x += step_x; side = 0; }
			else                           { side_dist_y += delta_dist_y; map_y += step_y; side = 1; }
			if (map_x < 0 || map_y < 0 || map_x >= g->world.w || map_y >= g->world.h
			 || g->world.grid[map_y][map_x] == '1')
				hit = 1;
		}

		double perp_wall_dist = (side == 0) ? (side_dist_x - delta_dist_x) : (side_dist_y - delta_dist_y);
		if (perp_wall_dist < 1e-6) perp_wall_dist = 1e-6;

		int line_h    = (int)(g->gfx.h / perp_wall_dist);
		int draw_start = -line_h / 2 + g->gfx.h / 2;
		int draw_end   =  line_h / 2 + g->gfx.h / 2;

		int color_idx;
		if (side == 0) color_idx = (step_x < 0) ? 2 /* E */ : 3 /* W */;
		else           color_idx = (step_y < 0) ? 1 /* S */ : 0 /* N */;

		int color = g->colors.wall_nsew[color_idx];
		if (side == 1) color = (color & 0xFEFEFE) >> 1; /* ombre simple */

		draw_vline(g, x, draw_start, draw_end, color); /* impl. dans draw.c */
	}
}

