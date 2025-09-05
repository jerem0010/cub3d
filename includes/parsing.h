/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:08:04 by lfirmin           #+#    #+#             */
/*   Updated: 2025/08/22 14:18:06 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

struct s_data;
typedef struct s_data t_data;

typedef struct s_textures
{
    char *north; //Path to texture.xmp
    char *south; //Path to texture.xmp
    char *east; //Path to texture.xmp
    char *west; //Path to texture.xmp
    int  floor[3]; //RGB: [0] = R, [1] = G, [2] = B
    int  ceiling[3]; //RGB: [0] = R, [1] = G, [2] = B
}   t_textures;

typedef struct s_data_parsing
{
     char **raw_map;
     int    fd_map;
     int    fd_map_dup;
}    t_data_parsing;

//parsing
int parsing(t_data *data);

//check_file
int    check_extension(char *map_path);
int check_file(char *map_path, t_data_parsing *parsing);

//get_map
int get_map(t_data *data);
int line_counter(int fd);
int put_map_on_array(t_data *data);
char *clean_line(char *raw_line);

//init_parsing
int init_parsing(t_data_parsing *parsing);
int init_textures(t_textures *textures);
int free_textures(t_textures *textures);

//line_detect
int is_config_line(char *line);
int is_empty_line(char *line);
int is_texture_line(char *line);
int is_color_line(char *line);

//get_textures
int get_texture_path(char *line, t_textures *texture);
int get_rgb_values(char *line, int rgb[3]);

//check_colors
int check_colors(t_textures *texture);
int is_rgb(int  color[3]);
#endif