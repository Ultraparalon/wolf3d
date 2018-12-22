/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_object_render.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 10:17:18 by vkaidans          #+#    #+#             */
/*   Updated: 2018/09/04 12:46:03 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	vs_dda(t_render *rend, int **map)
{
	while (1)
	{
		if (rend->side_dstx < rend->side_dsty)
		{
			rend->side_dstx += rend->delta_dstx;
			rend->mapx += rend->stepx;
			rend->side = 0;
		}
		else
		{
			rend->side_dsty += rend->delta_dsty;
			rend->mapy += rend->stepy;
			rend->side = 1;
		}
		if (map[rend->mapx][rend->mapy] > 0)
			return (0);
		if (map[rend->mapx][rend->mapy] < 0)
			return (1);
	}
}

void		vs_render_object(t_map *map, t_render *rend, int x)
{
	int			check;
	t_sidekick	sk;

	rend->mapx = (int)map->posx;
	rend->mapy = (int)map->posy;
	vs_get_step_side(rend, map->posy, map->posx);
	check = vs_dda(rend, map->map);
	if (!check)
		return ;
	map->check = check;
	vs_get_distance(rend, map->posy, map->posx);
	vs_get_line(rend);
	vs_get_wall(rend, map->posy, map->posx);
	vs_get_xcoor(rend, 256);
	sk.y = rend->draw_s;
	while (++sk.y < rend->draw_e)
	{
		sk.d = (sk.y << 10) - (W_HEIGHT << 9) + (rend->line_h << 9);
		sk.tx_y = (((sk.d << 8) / rend->line_h)) >> 10;
		sk.color = map->tex[9]->addr[(sk.tx_y << 8) + rend->tx_x];
		if (sk.color && sk.color > 0x111111)
			vs_img_set_pixel(map->img, x, sk.y, sk.color);
	}
}
