/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 12:37:11 by lfirmin           #+#    #+#             */
/*   Updated: 2025/10/07 10:13:41 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

static int	assign_texture(char *line, char **dest)
{
	char	*path;

	path = ft_strtrim(line + 2, " \t\n\r");
	if (!path)
		return (ft_error("Memory allocation failed"), -1);
	*dest = path;
	return (0);
}

int	get_texture_path(char *line, t_textures *texture, int *j)
{
	if (!line)
		return (-1);
	if (check_extension_2(line) && !is_color_line(line))
		return (ft_error(ERROR_NOT_XMP), 1);
	else if (is_texture_line(line) == 1 && j[0]++ == 0)
		return (assign_texture(line, &texture->north));
	else if (is_texture_line(line) == 2 && j[1]++ == 0)
		return (assign_texture(line, &texture->south));
	else if (is_texture_line(line) == 3 && j[2]++ == 0)
		return (assign_texture(line, &texture->west));
	else if (is_texture_line(line) == 4 && j[3]++ == 0)
		return (assign_texture(line, &texture->east));
	else if (is_color_line(line) == 1 && j[4]++ == 0)
		get_rgb_values(line, texture->floor);
	else if (is_color_line(line) == 2 && j[5]++ == 0)
		get_rgb_values(line, texture->ceiling);
	else
		return (ft_error(ERROR_DOUBLE), 2);
	return (0);
}

int	is_valid_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!str[i] || !(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

int	validate_and_convert_rgb(char **parts, int rgb[3])
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (!is_valid_number(parts[i]))
			return (free_char_array(parts), 1);
		rgb[i] = ft_atoi(parts[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (free_char_array(parts), 1);
	}
	return (free_char_array(parts), 0);
}

int	get_rgb_values(char *line, int rgb[3])
{
	char	*start;
	char	**parts;
	int		i;

	if (!line || !rgb)
		return (1);
	start = ft_strchr(line, ' ');
	if (!start)
		return (1);
	parts = ft_split(start + 1, ',');
	if (!parts)
		return (1);
	i = 0;
	while (parts[i])
		i++;
	if (i != 3)
		return (free_char_array(parts), 1);
	return (validate_and_convert_rgb(parts, rgb));
}
