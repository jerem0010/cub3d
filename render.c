// render.c
#include "cub3d.h"

static int is_wall(t_app *a, int mx, int my) {
    if (mx < 0 || my < 0 || mx >= a->map_w || my >= a->map_h) return 1;
    return (a->map[my][mx] == '1');
}

static void move_player(t_app *a) {
    double ms = a->move_speed;
    double rs = a->rot_speed;

    // forward/back
    if (a->keys.w) {
        double nx = a->px + a->dirx * ms;
        double ny = a->py + a->diry * ms;
        if (!is_wall(a, (int)nx, (int)a->py)) a->px = nx;
        if (!is_wall(a, (int)a->px, (int)ny)) a->py = ny;
    }
    if (a->keys.s) {
        double nx = a->px - a->dirx * ms;
        double ny = a->py - a->diry * ms;
        if (!is_wall(a, (int)nx, (int)a->py)) a->px = nx;
        if (!is_wall(a, (int)a->px, (int)ny)) a->py = ny;
    }
    // strafe
    if (a->keys.a) {
        double nx = a->px - a->diry * ms;
        double ny = a->py + a->dirx * ms;
        if (!is_wall(a, (int)nx, (int)a->py)) a->px = nx;
        if (!is_wall(a, (int)a->px, (int)ny)) a->py = ny;
    }
    if (a->keys.d) {
        double nx = a->px + a->diry * ms;
        double ny = a->py - a->dirx * ms;
        if (!is_wall(a, (int)nx, (int)a->py)) a->px = nx;
        if (!is_wall(a, (int)a->px, (int)ny)) a->py = ny;
    }
    // rotation
    if (a->keys.left || a->keys.right) {
        double angle = (a->keys.left ? -rs : rs);
        double olddirx = a->dirx;
        a->dirx = a->dirx * cos(angle) - a->diry * sin(angle);
        a->diry = olddirx * sin(angle) + a->diry * cos(angle);
        double oldplanex = a->planex;
        a->planex = a->planex * cos(angle) - a->planey * sin(angle);
        a->planey = oldplanex * sin(angle) + a->planey * cos(angle);
    }
}

static void draw_vertical_line_tex(t_app *a, int x, int drawStart, int drawEnd,
                                   t_tex *tex, int texX, double step, double texPos) {
    if (drawStart < 0) drawStart = 0;
    if (drawEnd >= WIN_H) drawEnd = WIN_H - 1;

    // plafond (optionnel: couleur unie)
    for (int y = 0; y < drawStart; ++y)
        put_pixel(&a->frame, x, y, 0x0080A0); // bleu doux

    for (int y = drawStart; y <= drawEnd; ++y) {
        int texY = (int)texPos & (tex->h - 1); // textures power-of-two → masque ok
        texPos += step;
        int color = get_tex_color(tex, texX, texY);
        put_pixel(&a->frame, x, y, color);
    }
    // sol
    for (int y = drawEnd + 1; y < WIN_H; ++y)
        put_pixel(&a->frame, x, y, 0x404040);
}

void render_frame(t_app *a) {
    // clear: pas nécessaire si on redraw tout (plafond/sol + murs)
    for (int x = 0; x < WIN_W; ++x) {
        // camX dans [-1, 1]
        double cameraX = 2.0 * x / (double)WIN_W - 1.0;
        double rayDirX = a->dirx + a->planex * cameraX;
        double rayDirY = a->diry + a->planey * cameraX;

        int mapX = (int)a->px;
        int mapY = (int)a->py;

        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);
        double sideDistX, sideDistY;
        int stepX, stepY;

        if (rayDirX < 0) { stepX = -1; sideDistX = (a->px - mapX) * deltaDistX; }
        else             { stepX =  1; sideDistX = (mapX + 1.0 - a->px) * deltaDistX; }
        if (rayDirY < 0) { stepY = -1; sideDistY = (a->py - mapY) * deltaDistY; }
        else             { stepY =  1; sideDistY = (mapY + 1.0 - a->py) * deltaDistY; }

        int hit = 0, side = 0;
        while (!hit) {
            if (sideDistX < sideDistY) { sideDistX += deltaDistX; mapX += stepX; side = 0; }
            else                        { sideDistY += deltaDistY; mapY += stepY; side = 1; }
            if (is_wall(a, mapX, mapY)) hit = 1;
        }

        double perpWallDist = (side == 0)
            ? (mapX - a->px + (1 - stepX) / 2.0) / rayDirX
            : (mapY - a->py + (1 - stepY) / 2.0) / rayDirY;
        if (perpWallDist < 1e-6) perpWallDist = 1e-6;

        int lineHeight = (int)(WIN_H / perpWallDist);
        int drawStart = -lineHeight / 2 + WIN_H / 2;
        int drawEnd   =  lineHeight / 2 + WIN_H / 2;

        // texture selection: 0=N,1=E,2=S,3=W (à adapter selon ta map)
        int tex_id;
        if (side == 0 && rayDirX > 0) tex_id = 3; // W
        else if (side == 0 && rayDirX < 0) tex_id = 1; // E
        else if (side == 1 && rayDirY > 0) tex_id = 0; // N
        else tex_id = 2; // S
        t_tex *tex = &a->tex[tex_id];

        // point d'impact sur le mur
        double wallX = (side == 0) ? (a->py + perpWallDist * rayDirY)
                                   : (a->px + perpWallDist * rayDirX);
        wallX -= floor(wallX);

        int texX = (int)(wallX * (double)tex->w);
        if (side == 0 && rayDirX > 0) texX = tex->w - texX - 1;
        if (side == 1 && rayDirY < 0) texX = tex->w - texX - 1;

        double step = (double)tex->h / (double)lineHeight;
        double texPos = (drawStart - WIN_H / 2 + lineHeight / 2) * step;

        draw_vertical_line_tex(a, x, drawStart, drawEnd, tex, texX, step, texPos);

        a->zbuf[x] = perpWallDist;
    }

    mlx_put_image_to_window(a->mlx, a->win, a->frame.ptr, 0, 0);
}

int update(t_app *a) {
    move_player(a);
    render_frame(a);
    return 0;
}
