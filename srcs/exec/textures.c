/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-neze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:24:56 by jle-neze          #+#    #+#             */
/*   Updated: 2025/09/12 18:24:58 by jle-neze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	load_one(t_game *g, t_tex *t, const char *path)
{
	t->ptr = mlx_xpm_file_to_image(g->gfx.mlx, (char *)path, &t->w, &t->h);
	if (!t->ptr)
		return (1);
	t->addr = mlx_get_data_addr(t->ptr, &t->bpp, &t->line_len, &t->endian);
	return (0);
}

int	textures_load(t_game *g, const char *no, const char *so,
		const char *we, const char *ea)
{
	if (load_one(g, &g->tex[0], no)
			|| load_one(g, &g->tex[1], so)
			|| load_one(g, &g->tex[2], we)
			|| load_one(g, &g->tex[3], ea))
	{
		textures_free(g);
		return (1);
	}
	g->has_tex = 1;
	return (0);
}

void	textures_free(t_game *g)
{
	for (int i = 0; i < 4; i++)
	{
		if (g->tex[i].ptr)
			mlx_destroy_image(g->gfx.mlx, g->tex[i].ptr);
		g->tex[i].ptr = NULL;
	}
}

unsigned int	tex_get_pixel(t_tex *t, int x, int y)
{
	char	*px = t->addr + (y * t->line_len + x * (t->bpp / 8));
	return (*(unsigned int *)px);
}
