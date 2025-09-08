#include "cub3d.h"

int	game_loop(t_game *g)
{
	/* 1) Update joueur selon input */
	player_update(g);
	/* 2) Dessin */
	draw_background(g);
	raycast_frame(g);
	mlx_put_image_to_window(g->gfx.mlx, g->gfx.win, g->gfx.frame.ptr, 0, 0);
	return (0);
}
/* Note: on pourrait optimiser en ne redessinant que ce qui change */