/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:07:29 by lfirmin           #+#    #+#             */
/*   Updated: 2025/10/07 12:09:03 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

int	hasinvalidchar(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != 'c' && map[y][x] != ' ' && map[y][x] != '	'
					&& map[y][x] != '\n')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	validate_map(char **map, int *player)
{
	int		result;
	char	**map_cp;

	map_cp = ft_arrcpy(map);
	result = check_map_char(map);
	if (result == 1)
		return (free_char_array(map_cp), ft_error(ERROR_PLAYER), 1);
	if (result == 2)
		return (free_char_array(map_cp), ft_error(ERROR_CHAR), 1);
	find_player_pos(map, player);
	if (flood_fill(map_cp, player[0], player[1]))
		return (free_char_array(map_cp), ft_error(ERROR_NOT_CLOSE), 1);
	rep_ex_wall(map_cp, player[0], player[1]);
	if (hasinvalidchar(map_cp))
		return (free_char_array(map_cp), ft_error(ERROR_CHAR), 1);
	free_char_array(map_cp);
	return (0);
}
