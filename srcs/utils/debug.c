/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:23:51 by lfirmin           #+#    #+#             */
/*   Updated: 2025/08/23 13:23:51 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void print_char_array_debug(char **arr, char *name)
{
    int i = 0;

    printf("=== %s ===\n", name ? name : "CHAR ARRAY");

    if (!arr)
    {
        printf("Array is NULL\n");
        return;
    }

    while (arr[i])
    {
        printf("[%d] (%zu chars): '%s'\n", i, strlen(arr[i]), arr[i]);
        i++;
    }
    printf("Total lines: %d\n", i);
    printf("==============\n");
}
