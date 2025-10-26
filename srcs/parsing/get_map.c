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
	{
		free_char_array(data->parsing.raw_map);
		return (1);
	}
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
	while (line != NULL)
	{
		free(line);
		line = get_next_line(-1);
	}
	get_next_line(-2);
	return (nb_line);
}

char	*clean_line(char *raw_line)
{
	char	*cleaned;

	if (!raw_line)
		return (NULL);
	cleaned = ft_strtrim(raw_line, " \t\n\r");
	return (cleaned);
}
