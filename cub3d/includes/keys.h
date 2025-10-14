/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-neze <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 18:18:03 by jle-neze          #+#    #+#             */
/*   Updated: 2025/09/12 18:18:07 by jle-neze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

/* ESC */
# ifdef __APPLE__
#  define KEY_ESC      53
#  define KEY_W        13
#  define KEY_A         0
#  define KEY_S         1
#  define KEY_D         2
#  define KEY_LEFT     123
#  define KEY_RIGHT    124
# else
#  define KEY_ESC   65307
#  define KEY_W        119
#  define KEY_A        100 // a inverse au d car cest la camera qui deplace
#  define KEY_S        115
#  define KEY_D         97 // a inverse au d car cest la camera qui deplace
#  define KEY_LEFT   65361
#  define KEY_RIGHT  65363
# endif

#endif
