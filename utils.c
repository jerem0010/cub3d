// utils.c
#include "cub3d.h"

void put_pixel(t_img *img, int x, int y, int color) {
    if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H) return;
    char *dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int*)dst = (unsigned int)color;
}

int get_tex_color(t_tex *t, int tx, int ty) {
    if (tx < 0) tx = 0; if (tx >= t->w) tx = t->w - 1;
    if (ty < 0) ty = 0; if (ty >= t->h) ty = t->h - 1;
    char *p = t->img.addr + ty * t->img.line_len + tx * (t->img.bpp / 8);
    return *(unsigned int*)p;
}
