/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:17:58 by lfirmin           #+#    #+#             */
/*   Updated: 2025/08/22 14:17:58 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

int parsing(t_data *data)
{
    if (check_file(data->map_path, &data->parsing) == 1)
        return (1);
    get_map(data);
    close(data->parsing.fd_map);
    close(data->parsing.fd_map_dup);
    if (check_colors(data->texture) == 1)
        return (1);
    return (0);
}