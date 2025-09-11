#include "cub3d.h"
#include "keys.h"

int	main(void)
{
	t_game	g;

	/* couleurs de base */
	g.colors.floor = 0x2D2D2D;
	g.colors.ceil  = 0x87CEEB;
	g.colors.wall_nsew[0] = 0xFF3333; /* N */
	g.colors.wall_nsew[1] = 0x33FF33; /* S */
	g.colors.wall_nsew[2] = 0x3333FF; /* E */
	g.colors.wall_nsew[3] = 0xFFFF33; /* W */

	/* init input */
	g.in = (t_input){0,0,0,0,0,0}; /* toutes touches relâchées ducoup a 0 et 1 quand appuye*/

	if (world_init_demo(&g.world) != 0)
		return (1);

	/* fenetre + framebuffer */
	if (init_window(&g, 1024, 768, "cub3D") != 0)
		return (world_free(&g.world), 1);

	if (textures_load(&g,
		"assets/north.xpm", "assets/south.xpm",
		"assets/west.xpm",  "assets/east.xpm") != 0)
	{
		/* Pas bloquant dev: on peut continuer en couleurs unies */
		g.has_tex = 0;
	}

	/* place le joueur dans un couloir safe */
	player_init(&g, 2.5, 2.5, 1.0, 0.0);
	draw_background(&g);

	mlx_put_image_to_window(g.gfx.mlx, g.gfx.win, g.gfx.frame.ptr, 0, 0);
	setup_hooks(&g);
	mlx_loop(g.gfx.mlx);

	world_free(&g.world);
	return (0);
}
// typedef struct s_game
// {
// 	t_mlx		gfx;
// 	t_colors	colors;
// 	t_input		in;
// 	t_world		world;
// 	t_cam		cam;
// 	double		move_speed;
// 	double		rot_speed;
// }	t_game;
