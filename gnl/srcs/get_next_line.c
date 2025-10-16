/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelghou <abelghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 21:31:24 by abelghou          #+#    #+#             */
/*   Updated: 2024/07/24 18:17:55 by abelghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

static char	*sort_and_store(int fd, char *buf, char *backup)
{
	int		read_line;
	char	*char_temp;

	read_line = 1;
	while (read_line != 0)
	{
		read_line = read(fd, buf, BUFFER_SIZE);
		if (read_line == -1)
			return (0);
		else if (read_line == 0)
			break ;
		buf[read_line] = '\0';
		if (!backup)
			backup = ft_strdup_g("");
		if (!backup)
			return (NULL);
		char_temp = backup;
		backup = ft_strjoin(char_temp, buf);
		free(char_temp);
		char_temp = NULL;
		if (ft_strchr_gnl (buf, '\n'))
			break ;
	}
	return (backup);
}

static char	*extract(char *line)
{
	size_t	count;
	char	*backup;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0' || line[1] == '\0')
		return (0);
	backup = ft_substr(line, count + 1, ft_strlen_g(line) - count);
	if (!backup)
		return (NULL);
	if (*backup == '\0')
	{
		free (backup);
		backup = NULL;
	}
	line[count + 1] = '\0';
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	char		*temp;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(backup), backup = NULL, NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free(backup), backup = NULL, NULL);
	line = sort_and_store(fd, buf, backup);
	free(buf);
	buf = NULL;
	if (!line)
		return (free(backup), backup = NULL, NULL);
	backup = extract(line);
	temp = ft_strdup_g(line);
	free(line);
	if (!temp)
		return (free(backup), backup = NULL, NULL);
	return (temp);
}

// int main()
// {
// 	int fd;
// 	char *line;
// 	fd = open("fd.txt", O_RDONLY);
// 	while((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	line = get_next_line(fd);
// 	close(fd);
// }