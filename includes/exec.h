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
	int		wall_nsew[4];
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
	char	**grid;
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
typedef struct s_data	t_data;

typedef struct s_game
{
	t_mlx		gfx;
	t_colors	colors;
	t_input		in;
	t_world		world;
	t_cam		cam;
	double		move_speed;
	double		rot_speed;

	t_tex		tex[4];
	int			has_tex;

	t_data		*data;
}	t_game;

typedef struct s_texpaths
{
	const char	*no;
	const char	*so;
	const char	*we;
	const char	*ea;
}	t_texpaths;

typedef struct s_player_init
{
	double	px;
	double	py;
	double	dx;
	double	dy;
}	t_player_init;

typedef struct s_texline
{
	t_tex	*tex;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		y0;
	int		y1;
}	t_texline;

typedef struct s_vline
{
	int	y0;
	int	y1;
	int	color;
}	t_vline;

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	int		tex_id;
}	t_ray;

typedef struct s_col
{
	int		draw_start;
	int		draw_end;
	int		line_h;
	double	perp_dist;
}	t_col;

typedef struct s_texdraw
{
	int		x;
	t_ray	*r;
	t_tex	*t;
	t_col	c;
}	t_texdraw;

/* init.c */
int				init_window(t_game *g, int w, int h, char *title);
void			cleanup_window(t_game *g);

/* hooks.c */
int				on_destroy(t_game *g);
int				on_keydown(int key, t_game *g);
int				on_keyup(int key, t_game *g);
void			setup_hooks(t_game *g);

/* image.c */
void			img_put_pixel(t_img *img, int x, int y, int color);

/* draw.c */
void			draw_background(t_game *g);
void			draw_vline(t_game *g, int x, t_vline v);

/* world.c */
// int		world_init_demo(t_world *w);
void			world_free(t_world *w);

/* player.c */
void			player_init(t_game *g, t_player_init p);
void			player_update(t_game *g);

/* raycast.c */
void			raycast_frame(t_game *g);

/* loop.c */
int				game_loop(t_game *g);

/* textures.c */
int				textures_load(t_game *g, t_texpaths *paths);
void			textures_free(t_game *g);
unsigned int	tex_get_pixel(t_tex *t, int x, int y);

/* draw.c */
void			draw_background(t_game *g);
void			draw_tex_vline(t_game *g, int x, t_texline l);
void			draw_column(t_game *g, int x, t_ray *r);

#endif
