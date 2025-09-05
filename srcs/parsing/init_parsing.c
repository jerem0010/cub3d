/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:33:00 by lfirmin           #+#    #+#             */
/*   Updated: 2025/08/23 13:33:00 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

int init_parsing(t_data_parsing *parsing)
{
    if (!parsing)
        return (ft_error(ERROR_INIT_PARS), 1);
    parsing->fd_map = 0;
    parsing->raw_map = NULL;
    return (0);
}

int init_textures(t_textures *textures)
{
    int i;

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

int free_textures(t_textures *textures)
{
    free(textures->north);
    free(textures->south);
    free(textures->east);
    free(textures->west);
    return (0);
}