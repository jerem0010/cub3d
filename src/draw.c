#include "cub3d.h"

void	draw_background(t_game *g)
{
	int	x, y, half = g->gfx.h / 2;

	for (y = 0; y < g->gfx.h; y++)
	{
		for (x = 0; x < g->gfx.w; x++)
		{
			if (y < half)
				img_put_pixel(&g->gfx.frame, x, y, g->colors.ceil);
			else
				img_put_pixel(&g->gfx.frame, x, y, g->colors.floor);
		}
	}
}

/* aussi exposée dans raycast.c, mais on garde la déclaration ici pour réutiliser ailleurs */
void	draw_vline(t_game *g, int x, int y0, int y1, int color)
{
	if (y0 < 0) y0 = 0;
	if (y1 >= g->gfx.h) y1 = g->gfx.h - 1;
	for (int y = y0; y <= y1; y++)
		img_put_pixel(&g->gfx.frame, x, y, color);
}
