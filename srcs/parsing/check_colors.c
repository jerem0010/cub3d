/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:41:26 by lfirmin           #+#    #+#             */
/*   Updated: 2025/08/25 18:41:26 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

int check_colors(t_textures *texture)
{
    if (is_rgb(texture->floor))
        return (ft_error(ERROR_COL), 1);
    if (is_rgb(texture->ceiling))
        return (ft_error(ERROR_COL), 1);
    return (0);
}

int is_rgb(int  color[3])
{
    int i;

    i = 0;
    while (i < 3)
    {
        if (color[i] > 255 || color[i] < 0)
            return (1);
        i++;
    }
    return (0);
}