/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:17:58 by lfirmin           #+#    #+#             */
/*   Updated: 2025/10/07 10:15:24 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

int check_xpm_file(char *filepath)
{
    FILE *fd;
    
    if (!filepath)
        return (1);
    
    fd = fopen(filepath, "r");
    if (!fd)
        return (1);
    
    fclose(fd);
    return (0);
}
int check_texture_file(t_textures *texture)
{
	if (check_xpm_file(texture->north))
		return(ft_error(ERR_I_N), 1);
	if (check_xpm_file(texture->south))
		return(ft_error(ERR_I_S), 1);
	if (check_xpm_file(texture->east))
		return(ft_error(ERR_I_E), 1);
	if (check_xpm_file(texture->west))
		return(ft_error(ERR_I_W), 1);
	return (0);
}

int	parsing(t_data *data)
{
	if (check_file(data->map_path, &data->parsing) == 1)
		return (1);
	if (get_map(data))
	{
		close(data->parsing.fd_map);
		close(data->parsing.fd_map_dup);
		return (1);
	}
	close(data->parsing.fd_map);
	close(data->parsing.fd_map_dup);
	/* Vider le buffer statique du gnl une dernière fois */
	get_next_line(-2);
	if (check_colors(data->texture) == 1)
	{
		free_char_array(data->parsing.raw_map);
		return (1);
	}
	if (check_texture_file(data->texture) == 1)
	{
		free_char_array(data->parsing.raw_map);
		return (1);
	}
	if (validate_map(data->parsing.raw_map, data->parsing.player))
	{
		free_char_array(data->parsing.raw_map);
		return (1);
	}
	data->map = data->parsing.raw_map;
	data->parsing.raw_map = NULL;
	return (0);
}
