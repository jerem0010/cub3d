/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:56:25 by lfirmin           #+#    #+#             */
/*   Updated: 2025/10/07 12:14:42 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CUB_H

# define CUB_H

# include "parsing.h"
# include "../libft/include/libft.h"
# include "../gnl/include/get_next_line.h"
# include "exec.h"
# include "keys.h"

# define ERROR_PREFIX "Error\n"
# define ERROR_EXT "Invalid file extension. Only .cub files are accepted."
# define ERROR_EMPT_PATH "Invalid map file path."
# define ERROR_INIT_DATA "Initialization of the data structure failed."
# define ERROR_INIT_TEX "Initialization of the textures structure failed."
# define ERROR_INIT_PARS "Initialization of the parsing structure failed."
# define ERROR_EMPTY "You have provided an empty file."
# define ERROR_COL "The RGB values provided are not valid or absent."
# define ERROR_NULL_P "Player not found or multiple players."
# define ERROR_BAD_CHAR "Invalid character in map."
# define ERROR_POS "Player position not found."
# define ERROR_ALLOC "Allocation failed."
# define ERROR_PLAYER "Player not found or multiple players."
# define ERROR_CHAR "Invalid character in map."
# define ERROR_DOUBLE "Multiple images/colors have been provided \
for the same texture."
# define ERROR_NOT_CLOSE "Map is not closed by walls."
# define ERROR_NOT_XMP "The texture file is not an xpm image."
# define ERR_I_N "Texture file provided for north is absent or inaccessible"
# define ERR_I_S "Texture file provided for south is absent or inaccessible"
# define ERR_I_E "Texture file provided for east is absent or inaccessible"
# define ERR_I_W "Texture file provided for west is absent or inaccessible"

typedef struct s_data
{
	char			**map;
	char			*map_path;
	t_textures		*texture;
	t_data_parsing	parsing;
}	t_data;

//utils
void	ft_error(char *message);
void	free_char_array(char **array);
int		ft_arrlen(char **arr);
void	print_array(char **array);
int		ft_strlen_2d(char **str);

//init
int		init_data(t_data *data, char *path);
void	free_data(t_data *data);

#endif
