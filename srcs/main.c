#include "cub.h"

int main(int ac, char **av)
{
    t_data data;
    init_data(&data, av[1]);
    parsing(&data);
    free_char_array(data.parsing.raw_map);
    free_textures(data.texture);
    free_data(&data);
}