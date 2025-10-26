/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:07:29 by lfirmin           #+#    #+#             */
/*   Updated: 2025/10/07 10:11:50 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

static int	process_config_line(char *line, t_data *data, int *j)
{
	char	*cleaned;

	cleaned = clean_line(line);
	if (get_texture_path(cleaned, data->texture, j))
	{
		free(line);
		free(cleaned);
		return (1);
	}
	free(cleaned);
	return (0);
}

static void	flush_remaining_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}

static int	handle_line(char *line, t_data *data, int *i, int *j)
{
	if (is_config_line(line))
	{
		if (process_config_line(line, data, j))
		{
			flush_remaining_lines(-1);
			return (1);
		}
		free(line);
	}
	else if (is_empty_line(line) && *i == 0)
		free(line);
	else
		data->parsing.raw_map[(*i)++] = line;
	return (0);
}

int	put_map_on_array(t_data *data)
{
	char	*line;
	int		i;
	int		j[6];

	ft_memset(j, 0, sizeof(j));
	i = 0;
	line = get_next_line(data->parsing.fd_map_dup);
	while (line != NULL)
	{
		if (handle_line(line, data, &i, j))
			return (1);
		line = get_next_line(data->parsing.fd_map_dup);
	}
	data->parsing.raw_map[i] = NULL;
	get_next_line(-2);
	return (0);
}
