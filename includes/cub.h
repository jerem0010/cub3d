
#ifndef CUB_H
#define CUB_H

#include "parsing.h"
#include "messages.h"
#include "../libft/include/libft.h"
#include "../gnl/include/get_next_line.h"

typedef struct s_data
{
    char **map;
    char *map_path;
    t_textures *texture;
    t_data_parsing parsing;
} t_data;

//////utils/////
//utils
void    ft_error(char *message);
void free_char_array(char **array);
//init
int init_data(t_data *data, char *path);
void free_data(t_data *data);

/////debug
void print_char_array_debug(char **arr, char *name);

#endif