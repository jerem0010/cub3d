// input.c
#include "cub3d.h"
#ifdef __APPLE__
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
#else
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
#endif

int key_press(int key, t_app *a){
    if (key == KEY_ESC) close_win(a);
    if (key == KEY_W) a->keys.w = true;
    if (key == KEY_S) a->keys.s = true;
    if (key == KEY_A) a->keys.a = true;
    if (key == KEY_D) a->keys.d = true;
    if (key == KEY_LEFT) a->keys.left = true;
    if (key == KEY_RIGHT) a->keys.right = true;
    return 0;
}
int key_release(int key, t_app *a){
    if (key == KEY_W) a->keys.w = false;
    if (key == KEY_S) a->keys.s = false;
    if (key == KEY_A) a->keys.a = false;
    if (key == KEY_D) a->keys.d = false;
    if (key == KEY_LEFT) a->keys.left = false;
    if (key == KEY_RIGHT) a->keys.right = false;
    return 0;
}
int close_win(t_app *a){
    if (a->zbuf) free(a->zbuf);
    if (a->frame.ptr) mlx_destroy_image(a->mlx, a->frame.ptr);
    if (a->win) mlx_destroy_window(a->mlx, a->win);
    exit(0);
    return 0;
}
