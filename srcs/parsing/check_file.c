/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:07:29 by lfirmin           #+#    #+#             */
/*   Updated: 2025/08/22 15:07:33 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int check_file(char *map_path, t_data_parsing *parsing)
{
    if (!map_path)
        return (ft_error(ERROR_EMPT_PATH), 1);
    if (check_extension(map_path))
        return (1);
    parsing->fd_map = open(map_path, O_RDONLY);
    if (parsing->fd_map < 0)
        return (perror("\033[1m[❌]\033[0m\033[1;31mError\033[0m"), 1);
    parsing->fd_map_dup = open(map_path, O_RDONLY);
    if (parsing->fd_map_dup < 0)
        return (perror("\033[1m[❌]\033[0m\033[1;31mError\033[0m"), 1);
    return (0);
}

int check_extension(char *map_path)
{
    int len_map_path;

    len_map_path = ft_strlen(map_path);
    if (len_map_path < 4)
        return (ft_error(ERROR_EXT), 1);
    if (ft_strcmp(map_path + len_map_path - 4, ".cub") != 0)
        return (ft_error(ERROR_EXT), 1);
    return (0);
}