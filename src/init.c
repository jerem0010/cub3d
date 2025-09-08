#include "cub3d.h"

int	init_window(t_game *g, int w, int h, char *title)
{
	g->gfx.w = w;
	g->gfx.h = h;
	g->gfx.mlx = mlx_init();
	if (!g->gfx.mlx)
		return (1);
	g->gfx.win = mlx_new_window(g->gfx.mlx, w, h, title);
	if (!g->gfx.win)
		return (1);
	g->gfx.frame.ptr = mlx_new_image(g->gfx.mlx, w, h);
	if (!g->gfx.frame.ptr)
		return (1);
	g->gfx.frame.addr = mlx_get_data_addr(g->gfx.frame.ptr, &g->gfx.frame.bpp,
			&g->gfx.frame.line_len, &g->gfx.frame.endian);
	g->gfx.frame.w = w;
	g->gfx.frame.h = h;
	return (0);
}
