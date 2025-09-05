/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:57:21 by lfirmin           #+#    #+#             */
/*   Updated: 2025/08/22 18:57:21 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

int init_data(t_data *data, char *path)
{
    if (!data)
        return (ft_error(ERROR_INIT_DATA), 1);
    data->texture = malloc(sizeof(t_textures));
    if (!data->texture)
        return (ft_error(ERROR_INIT_TEX), 1);
    init_parsing(&data->parsing);
    init_textures(data->texture);
    data->map = NULL;
    data->map_path = path;
    return (0);
}

void free_data(t_data *data)
{
    if (!data)
        return;
    if (data->texture)
        free(data->texture);
}

