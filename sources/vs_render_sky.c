/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_sky_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 10:43:51 by vkaidans          #+#    #+#             */
/*   Updated: 2018/09/04 12:55:23 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	vs_dda(t_render *rend, int **skybox)
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
		if (skybox[rend->mapx][rend->mapy] > 0)
			break ;
	}
}

void		vs_render_sky(t_map *map, t_render *rend, int x)
{
	int y;

	y = -1;
	rend->mapx = 1;
	rend->mapy = 1;
	vs_get_step_side(rend, 1.5, 1.5);
	vs_dda(rend, map->skybox);
	vs_get_distance(rend, 1.5, 1.5);
	vs_get_wall(rend, 1, 1);
	vs_get_xcoor(rend, 512);
	while (++y < 400)
	{
		vs_img_set_pixel(map->img, x, y,
				map->tex[11]->addr[SKY * (y >> 1) + rend->tx_x]);
	}
}
