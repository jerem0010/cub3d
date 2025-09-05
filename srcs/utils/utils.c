/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:56:25 by lfirmin           #+#    #+#             */
/*   Updated: 2025/08/22 14:56:25 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void    ft_error(char *message)
{
    int     len;

    len = 0;
    while (message[len])
        len++;
    write(2, ERROR_PREFIX, 31);
    write(2, message, len);
    write(2, "\n", 1);
}

void free_char_array(char **array)
{
    int i;

    if (!array)
        return;
    i = 0;
    while (array[i])
        free(array[i++]);
    free(array);
}