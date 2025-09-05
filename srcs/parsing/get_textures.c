/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 12:37:11 by lfirmin           #+#    #+#             */
/*   Updated: 2025/08/24 12:37:11 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

int get_texture_path(char *line, t_textures *texture)
{
    if (is_texture_line(line) == 1)
        texture->north = ft_strtrim(line + 2, " \t\n\r");
    else if (is_texture_line(line) == 2)
        texture->south = ft_strtrim(line + 2, " \t\n\r");
    else if (is_texture_line(line) == 3)
        texture->west = ft_strtrim(line + 2, " \t\n\r");
    else if (is_texture_line(line) == 4)
        texture->east = ft_strtrim(line + 2, " \t\n\r");
    else if (is_color_line(line) == 1)  // F
        get_rgb_values(line, texture->floor);
    else if (is_color_line(line) == 2)  // C
        get_rgb_values(line, texture->ceiling);
    return (0);
}

int get_rgb_values(char *line, int rgb[3])
{
    char *start;
    char **parts;
    int i;

    if (!line || !rgb)
        return (1);
    start = ft_strchr(line, ' ');
    if (!start)
        return (1);
    parts = ft_split(start + 1, ',');
    if (!parts)
        return (1);
    i = 0;
    while (parts[i] && i < 3)
    {
        rgb[i] = ft_atoi(parts[i]);
        i++;
    }
    free_char_array(parts);
    return (i == 3 ? 0 : 1);
}