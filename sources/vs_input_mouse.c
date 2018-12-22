/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_input_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 13:21:56 by vkaidans          #+#    #+#             */
/*   Updated: 2018/07/18 13:21:58 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	hook_mousemove(int x, int y, t_map *map)
{
	static double	lx;

	(void)y;
	vs_rotate(map, -((double)(x - lx) / 200));
	lx = x;
	return (0);
}
