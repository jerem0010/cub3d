// cub3d.h
#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <stdlib.h>
# include <stdbool.h>
# include "mlx.h"

# define WIN_W 1280
# define WIN_H 720

typedef struct s_img {
    void    *ptr;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
} t_img;

typedef struct s_tex {
    t_img   img;
    int     w, h;
} t_tex;

typedef struct s_keys {
    bool w, a, s, d, left, right;
} t_keys;

typedef struct s_app {
    void    *mlx;
    void    *win;
    t_img   frame;
    // map
    char    **map;   // rectangle, accès map[y][x]
    int     map_w, map_h;

    // player
    double  px, py;      // position
    double  dirx, diry;  // direction
    double  planex, planey; // caméra (FOV ~66° => plane longueur ~0.66)

    // movement
    double  move_speed;
    double  rot_speed;

    // textures (N,E,S,W) supposées chargées via parsing
    t_tex   tex[4];

    // zbuffer pour sprites/doors bonus
    double  *zbuf;

    t_keys  keys;
} t_app;

// utils
void    put_pixel(t_img *img, int x, int y, int color);
int     get_tex_color(t_tex *t, int tx, int ty);

// hooks
int key_press(int keycode, t_app *a);
int key_release(int keycode, t_app *a);
int close_win(t_app *a);

// loop
int update(t_app *a);
void render_frame(t_app *a);

#endif
