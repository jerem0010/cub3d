/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_detect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 11:58:39 by lfirmin           #+#    #+#             */
/*   Updated: 2025/08/24 11:58:39 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int is_config_line(char *line)
{
    char *trimmed;
    int result;

    result = 0;
    if (!line)
        return (0);
    trimmed = ft_strtrim(line, " \t\n\r");
    if (!trimmed)
        return (0);
    if (ft_strncmp(trimmed, "NO ", 3) == 0 ||
        ft_strncmp(trimmed, "SO ", 3) == 0 ||
        ft_strncmp(trimmed, "WE ", 3) == 0 ||
        ft_strncmp(trimmed, "EA ", 3) == 0 ||
        ft_strncmp(trimmed, "F ", 2) == 0 ||
        ft_strncmp(trimmed, "C ", 2) == 0)
        result = 1;
    free(trimmed);
    return (result);
}

int is_empty_line(char *line)
{
    int i;

    i = 0;
    if (!line)
        return (1);  // NULL = vide
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' &&
            line[i] != '\n' && line[i] != '\r')
            return (0);
        i++;
    }
    return (1);  // Que des whitespaces
}

int is_color_line(char *line)
{
    char *trimmed;
    int result;

    result = 0;
    if (!line)
        return (0);
    trimmed = ft_strtrim(line, " \t\n\r");
    if (!trimmed)
        return (0);
    if (ft_strncmp(trimmed, "F ", 2) == 0)
        result = 1;
    else if (ft_strncmp(trimmed, "C ", 2) == 0)
        result = 2;
    free(trimmed);
    return (result);
}

int is_texture_line(char *line)
{
    char *trimmed;
    int result;

    result = 0;
    if (!line)
        return (0);
    trimmed = ft_strtrim(line, " \t\n\r");
    if (!trimmed)
        return (0);
    if (ft_strncmp(trimmed, "NO ", 3) == 0)
        result = 1;
    else if (ft_strncmp(trimmed, "SO ", 3) == 0)
        result = 2;
    else if (ft_strncmp(trimmed, "WE ", 3) == 0)
        result = 3;
    else if (ft_strncmp(trimmed, "EA ", 3) == 0)
        result = 4;
    free(trimmed);
    return (result);
}