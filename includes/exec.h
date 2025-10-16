/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-neze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:17:48 by jle-neze          #+#    #+#             */
/*   Updated: 2025/09/12 18:17:51 by jle-neze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdlib.h>
# include <stdint.h>
# include <math.h>
# include <../minilibx-linux/mlx.h>

/* Image (framebuffer) */
typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}	t_img;

/* Contexte MLX */
typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		w;
	int		h;
	t_img	frame;
}	t_mlx;

/* Couleurs de base */
typedef struct s_colors
{
	int		floor;
	int		ceil;
	int		wall_nsew[4]; /* 0:N 1:S 2:E 3:W → couleurs simples pour l’instant */
}	t_colors;

/* Entrées clavier (état des touches) */
typedef struct s_input
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_input;

/* Monde (map) */
typedef struct s_world
{
	int		w;
	int		h;
	char	**grid; /* '0' vide, '1' mur */
}	t_world;

/* Caméra / joueur (Raycasting) */
typedef struct s_cam
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_cam;

typedef struct s_tex
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}	t_tex;

/* State principal */
typedef struct s_game
{
	t_mlx		gfx;
	t_colors	colors;
	t_input		in;
	t_world		world;
	t_cam		cam;
	double		move_speed;
	double		rot_speed;

	/* --- Textures --- */
	t_tex		tex[4];    /* 0:N 1:S 2:E 3:W */
	int			has_tex;  /* 1 si chargées OK */
}	t_game;

/* init.c */
int		init_window(t_game *g, int w, int h, char *title);

/* hooks.c */
int		on_destroy(t_game *g);
int		on_keydown(int key, t_game *g);
int		on_keyup(int key, t_game *g);
void	setup_hooks(t_game *g);

/* image.c */
void	img_put_pixel(t_img *img, int x, int y, int color);

/* draw.c */
void	draw_background(t_game *g);
void	draw_vline(t_game *g, int x, int y0, int y1, int color);

/* world.c */
int		world_init_demo(t_world *w);
void	world_free(t_world *w);

/* player.c */
void	player_init(t_game *g, double px, double py, double dx, double dy);
void	player_update(t_game *g);

/* raycast.c */
void	raycast_frame(t_game *g);

/* loop.c */
int		game_loop(t_game *g);

/* textures.c */
int  textures_load(t_game *g, const char *no, const char *so,
                   const char *we, const char *ea);
void textures_free(t_game *g);
unsigned int tex_get_pixel(t_tex *t, int x, int y);

/* draw.c */
void draw_background(t_game *g);
void draw_vline(t_game *g, int x, int y0, int y1, int color);
void draw_tex_vline(t_game *g, int x, int y0, int y1,
                    t_tex *tex, int tex_x, double step, double tex_pos);


#endif
