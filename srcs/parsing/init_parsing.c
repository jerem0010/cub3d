/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:33:00 by lfirmin           #+#    #+#             */
/*   Updated: 2025/10/07 10:14:37 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

int	init_parsing(t_data_parsing *parsing)
{
	if (!parsing)
		return (ft_error(ERROR_INIT_PARS), 1);
	parsing->fd_map = 0;
	parsing->raw_map = NULL;
	return (0);
}

int	init_textures(t_textures *textures)
{
	int	i;

	if (!textures)
		return (ft_error(ERROR_INIT_TEX), 1);
	textures->north = NULL;
	textures->south = NULL;
	textures->east = NULL;
	textures->west = NULL;
	i = 0;
	while (i < 3)
	{
		textures->floor[i] = -1;
		textures->ceiling[i] = -1;
		i++;
	}
	return (0);
}

int	free_textures(t_textures *textures)
{
	if (!textures)
		return (0);
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->east)
		free(textures->east);
	if (textures->west)
		free(textures->west);
	return (0);
}
