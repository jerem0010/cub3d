/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-neze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:25:13 by jle-neze          #+#    #+#             */
/*   Updated: 2025/09/12 18:25:17 by jle-neze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <stdlib.h>

// static const char *demo_map[] = {
// 	"111111111111",
// 	"100000000001",
// 	"100011110001",
// 	"100000010001",
// 	"101111010001",
// 	"100100010001",
// 	"10010N010001", /* N = start dir nord, on l'ignore ici (juste info) */
// 	"100000000001",
// 	"111111111111",
// 	NULL
// };
static const char *demo_map[] = {
	"111111111111",
	"100000000001",
	"100000000001",
	"100000000001", 
	"100000001111",
	"100000000001",
	"100000000001", /* N = start dir nord, on l'ignore ici (juste info) */
	"100000000001",
	"111111111111",
	NULL
};

int	world_init_demo(t_world *w)
{
	int h = 0;
	while (demo_map[h])
		h++;
	w->h = h;
	w->w = 0;
	for (int i = 0; i < h; i++)
	{
		int len = 0;
		while (demo_map[i][len]) len++;
		if (len > w->w) w->w = len;
	}
	w->grid = (char **)malloc(sizeof(char *) * (h + 1));
	if (!w->grid) return (1);
	for (int y = 0; y < h; y++)
	{
		w->grid[y] = (char *)malloc(w->w + 1);
		if (!w->grid[y]) return (1);
		for (int x = 0; x < w->w; x++)
		{
			char c = demo_map[y][x];
			if (c == 0) c = '1';
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				c = '0';
			w->grid[y][x] = c;
		}
		w->grid[y][w->w] = '\0';
	}
	w->grid[h] = NULL;
	return (0);
}

void	world_free(t_world *w)
{
	if (!w->grid) return ;
	for (int y = 0; y < w->h; y++)
		free(w->grid[y]);
	free(w->grid);
	w->grid = NULL;
}
