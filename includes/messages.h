/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:00:45 by lfirmin           #+#    #+#             */
/*   Updated: 2025/08/22 15:01:20 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MESSAGE_H
#define MESSAGE_H

#define ERROR_PREFIX "\033[1m[❌]\033[0m\033[1;31mError\033[0m: "
#define ERROR_EXT "Invalid file extension. Only .cub files are accepted."
#define ERROR_EMPT_PATH "Invalid map file path."
#define ERROR_INIT_DATA "Initialization of the data structure failed."
#define ERROR_INIT_TEX "Initialization of the textures structure failed."
#define ERROR_INIT_PARS "Initialization of the parsing structure failed."
#define ERROR_EMPTY "You have provided an empty file."
#define ERROR_COL "The RGB values provided are not valid."

#define DEBUG "test"

#endif