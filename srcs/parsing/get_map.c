/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:29:28 by lfirmin           #+#    #+#             */
/*   Updated: 2025/08/23 13:29:28 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int get_map(t_data *data)
{
    int nb_line;

    nb_line = line_counter(data->parsing.fd_map);
    if (nb_line <= 0)
        return (ft_error(ERROR_EMPTY), 1);
    data->parsing.raw_map = ft_calloc(nb_line + 1, sizeof(char*));
    put_map_on_array(data);
    //print_char_array_debug(data->parsing.raw_map, "debug");
    //printf("---deb_texture---\n%s\n%s\n%s\n%s\n", data->texture->north, data->texture->south, data->texture->west, data->texture->east);
   // printf("---deb_colors_f---\n%d,%d,%d\n", data->texture->floor[0], data->texture->floor[1], data->texture->floor[2]);
   // printf("---deb_colors_c---\n%d,%d,%d\n", data->texture->ceiling[0], data->texture->ceiling[1], data->texture->ceiling[2]);
    return (0);
}

int line_counter(int fd)
{
    int nb_line;
    char *line;

    line = NULL;
    nb_line = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        nb_line++;
        free(line);
    }
    free(line);
    line = get_next_line(-1);  // force cleanup
    free(line);
    return (nb_line);
}

int put_map_on_array(t_data *data)
{
    char *line;
    char *cleaned;
    int i;

    i = 0;
    while ((line = get_next_line(data->parsing.fd_map_dup)) != NULL)
    {
        if (is_config_line(line))
        {
            cleaned = clean_line(line);
            get_texture_path(cleaned, data->texture);
            free(line);
            free(cleaned);
        }
        else if (is_empty_line(line))
            free(line);
        else
            data->parsing.raw_map[i++] = line;
    }
    line = get_next_line(-1);
    if (line)
        free(line);
    data->parsing.raw_map[i] = NULL;
    return (0);
}

char *clean_line(char *raw_line)
{
    char *cleaned;
    if (!raw_line)
        return (NULL);

    cleaned = ft_strtrim(raw_line, " \t\n\r");
    return (cleaned);
}