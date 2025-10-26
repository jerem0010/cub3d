/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:07:29 by lfirmin           #+#    #+#             */
/*   Updated: 2025/10/07 10:11:50 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

int	check_char_and_count(char c, int *p)
{
	if (c == '1' || c == '0' || c == ' ' || c == '\n')
		return (0);
	else if (c == 'S' || c == 'N' || c == 'E' || c == 'W')
	{
		(*p)++;
		return (0);
	}
	else
		return (2);
}

int	check_map_char(char **map)
{
	int	i;
	int	j;
	int	p;
	int	ret;

	i = 0;
	p = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			ret = check_char_and_count(map[i][j], &p);
			if (ret != 0)
				return (ret);
			j++;
		}
		i++;
	}
	if (p != 1)
		return (1);
	return (0);
}

void	find_player_pos(char **map, int *player)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'S' || map[i][j] == 'N' ||
					map[i][j] == 'E' || map[i][j] == 'W')
			{
				player[0] = j;
				player[1] = i;
				player[2] = map[i][j];
				return ;
			}
			j++;
		}
		i++;
	}
}

int	flood_fill(char **map_cp, int x, int y)
{
	if (!map_cp || y < 0 || x < 0 || !map_cp[y] || !map_cp[y][x])
		return (1);
	if (map_cp[y][x] == 'v')
		return (0);
	if (map_cp[y][x] == '1')
	{
		map_cp[y][x] = 'v';
		return (0);
	}
	if (map_cp[y][x] == '0' || map_cp[y][x] == 'N' || map_cp[y][x] == 'S'
			|| map_cp[y][x] == 'E' || map_cp[y][x] == 'W')
	{
		map_cp[y][x] = 'v';
		if (flood_fill(map_cp, x + 1, y))
			return (1);
		if (flood_fill(map_cp, x - 1, y))
			return (1);
		if (flood_fill(map_cp, x, y + 1))
			return (1);
		if (flood_fill(map_cp, x, y - 1))
			return (1);
		return (0);
	}
	return (1);
}

int	ft_strlen_2d(char **str) {
	int i;

	i = 0;
	while (str[i])
		++i;

	return i;
}

int	rep_ex_wall(char **map_cp, int x, int y)
{
	int	len;

	len = 0;
	if (y < 0 || x < 0)
		return (0);
	if (!map_cp[y])
		return (0);
	len = ft_strlen(map_cp[y]);
	if (x >= (int)len)
		return (0);
	if (map_cp[y][x] == '1')
		map_cp[y][x] = 'v';
	if (map_cp[y][x] == 'v')
	{
		map_cp[y][x] = 'c';
		rep_ex_wall(map_cp, x + 1, y);
		rep_ex_wall(map_cp, x - 1, y);
		rep_ex_wall(map_cp, x, y + 1);
		rep_ex_wall(map_cp, x, y - 1);
	}
	return (0);
}
