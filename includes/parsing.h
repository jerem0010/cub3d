/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:08:04 by lfirmin           #+#    #+#             */
/*   Updated: 2025/10/07 12:16:07 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

struct					s_data;
typedef struct s_data	t_data;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		floor[3];
	int		ceiling[3];
}	t_textures;

typedef struct s_data_parsing
{
	char	**raw_map;
	int		fd_map;
	int		fd_map_dup;
	int		player[3];
}	t_data_parsing;
//player -> 0 = x, 1 = y, 2 = head

//parsing
int		parsing(t_data *data);

//check_file
int		check_extension(char *map_path);
int		check_file(char *map_path, t_data_parsing *parsing);

//get_map
int		get_map(t_data *data);
int		line_counter(int fd);
int		put_map_on_array(t_data *data);
char	*clean_line(char *raw_line);

//init_parsing
int		init_parsing(t_data_parsing *parsing);
int		init_textures(t_textures *textures);
int		free_textures(t_textures *textures);

//line_detect
int		is_config_line(char *line);
int		is_empty_line(char *line);
int		is_texture_line(char *line);
int		is_color_line(char *line);
int		check_extension_2(char *str);

//get_textures
int		get_texture_path(char *line, t_textures *texture, int *j);
int		validate_and_convert_rgb(char **parts, int rgb[3]);
int		get_rgb_values(char *line, int rgb[3]);
int		is_valid_number(char *str);

//check_colors
int		check_colors(t_textures *texture);
int		is_rgb(int color[3]);

// check_map
int		check_map_char(char **map);
void	find_player_pos(char **map, int *player);
int		flood_fill(char **map_cp, int x, int y);
int		rep_ex_wall(char **map_cp, int x, int y);
int		check_char_and_count(char c, int *p);

//check_map_2
int		hasivalidchar(char **map);
int		validate_map(char **map, int *player);

#endif
