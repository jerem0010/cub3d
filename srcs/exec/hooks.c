/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-neze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:19:19 by jle-neze          #+#    #+#             */
/*   Updated: 2025/09/12 18:19:22 by jle-neze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "keys.h"
#include <stdlib.h>

int	on_destroy(t_game *g)
{
	if (g->gfx.frame.ptr)
		mlx_destroy_image(g->gfx.mlx, g->gfx.frame.ptr);
	textures_free(g);
	world_free(&g->world);
	if (g->gfx.win)
		mlx_destroy_window(g->gfx.mlx, g->gfx.win);
	exit(0);
	return (0);
}


static void set_key(int key, t_game *g, int press)
{
	if (key == KEY_W) g->in.w = press;
	if (key == KEY_A) g->in.a = press;
	if (key == KEY_S) g->in.s = press;
	if (key == KEY_D) g->in.d = press;
	if (key == KEY_LEFT) g->in.left = press;
	if (key == KEY_RIGHT) g->in.right = press;
}

int	on_keydown(int key, t_game *g)
{
	if (key == KEY_ESC)
		on_destroy(g);
	set_key(key, g, 1);
	return (0);
}

int	on_keyup(int key, t_game *g)
{
	set_key(key, g, 0);
	return (0);
}

void	setup_hooks(t_game *g)
{
	/* croix de fermeture */
	mlx_hook(g->gfx.win, 17, 0, on_destroy, g);
	/* KeyPress / KeyRelease */
	mlx_hook(g->gfx.win, 2, 1L<<0, on_keydown, g);
	mlx_hook(g->gfx.win, 3, 1L<<1, on_keyup, g);
	/* boucle */
	mlx_loop_hook(g->gfx.mlx, game_loop, g);
}
