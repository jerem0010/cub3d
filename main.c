// main.c
#include "cub3d.h"
#include <stdio.h>
#include <string.h>

// ---- TEMP: petite map de test fermée (a remplacer par le parsing) ----
static char *gmap[] = {
    "111111111111",
    "100000000001",
    "101111011101",
    "100100010001",
    "101100010001",
    "100000000001",
    "111111111111",
    NULL
};

static int map_w(char **m){ int w=0; for(int i=0;m[0][i];++i) w++; return w; }
static int map_h(char **m){ int h=0; while(m[h]) h++; return h; }

// Charge texture XPM via mlx_xpm_file_to_image (ou via parsing)
static void load_tex(t_app *a, int id, const char *path){
    t_tex *t = &a->tex[id];
    t->img.ptr = mlx_xpm_file_to_image(a->mlx, (char*)path, &t->w, &t->h);
    if (!t->img.ptr){ fprintf(stderr,"Texture load fail: %s\n", path); exit(1); }
    t->img.addr = mlx_get_data_addr(t->img.ptr, &t->img.bpp, &t->img.line_len, &t->img.endian);
}

int main(void) {
    t_app a;
    memset(&a, 0, sizeof(a));

    a.mlx = mlx_init();
    if (!a.mlx) return 1;
    a.win = mlx_new_window(a.mlx, WIN_W, WIN_H, "cub3d");
    a.frame.ptr = mlx_new_image(a.mlx, WIN_W, WIN_H);
    a.frame.addr = mlx_get_data_addr(a.frame.ptr, &a.frame.bpp, &a.frame.line_len, &a.frame.endian);

    // map (remplace par le résultat de ton parsing)
    a.map = gmap;
    a.map_w = map_w(a.map);
    a.map_h = map_h(a.map);

    // player init (à placer selon la map/parsed spawn + direction N/E/S/W)
    a.px = 2.5; a.py = 2.5;
    a.dirx = -1.0; a.diry = 0.0;
    a.planex = 0.0; a.planey = 0.66;

    a.move_speed = 0.08;
    a.rot_speed = 0.05;

    a.zbuf = malloc(sizeof(double) * WIN_W);
    if (!a.zbuf) return 1;

    // charge 4 textures (exemples de chemins)
    load_tex(&a, 0, "tex_north.xpm");
    load_tex(&a, 1, "tex_east.xpm");
    load_tex(&a, 2, "tex_south.xpm");
    load_tex(&a, 3, "tex_west.xpm");

    // hooks
    mlx_hook(a.win, 2, 1L<<0, key_press, &a);      // KeyPress
    mlx_hook(a.win, 3, 1L<<1, key_release, &a);    // KeyRelease
    mlx_hook(a.win, 17, 0, close_win, &a);         // DestroyNotify
    mlx_loop_hook(a.mlx, update, &a);

    mlx_loop(a.mlx);
    return 0;
}
