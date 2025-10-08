/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:29:28 by lfirmin           #+#    #+#             */
/*   Updated: 2025/10/07 10:13:07 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_map(t_data *data)
{
	int	nb_line;

	nb_line = line_counter(data->parsing.fd_map);
	if (nb_line <= 0)
		return (ft_error(ERROR_EMPTY), 1);
	data->parsing.raw_map = ft_calloc(nb_line + 1, sizeof(char *));
	if (put_map_on_array(data))
		return (1);
	return (0);
}

int	line_counter(int fd)
{
	int		nb_line;
	char	*line;

	line = NULL;
	nb_line = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		nb_line++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	line = get_next_line(-1);
	free(line);
	return (nb_line);
}

int	put_map_on_array(t_data *data)
{
	char	*line;
	char	*cleaned;
	int		i;
	int		j[6];

	ft_memset(j, 0, sizeof(j));
	i = 0;
	while ((line = get_next_line(data->parsing.fd_map_dup)) != NULL)
	{
		if (is_config_line(line))
		{
			cleaned = clean_line(line);
			if (get_texture_path(cleaned, data->texture, j))
			{
				free(line);
				free(cleaned);
				line = get_next_line(-1);
				if (line)
					free(line);
				return (1);
			}
			free(line);
			free(cleaned);
		}
		else if (is_empty_line(line) && i == 0)
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

char	*clean_line(char *raw_line)
{
	char	*cleaned;

	if (!raw_line)
		return (NULL);
	cleaned = ft_strtrim(raw_line, " \t\n\r");
	return (cleaned);
}
