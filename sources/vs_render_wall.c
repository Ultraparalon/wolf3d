/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_render_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 16:01:35 by vkaidans          #+#    #+#             */
/*   Updated: 2018/09/04 12:48:38 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	vs_dda(t_render *rend, int **map)
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
			break ;
	}
}

static int	vs_mandatory(t_map *map, t_render *rend, t_sidekick *sk)
{
	if (rend->side && rend->stepy < 0)
		return (map->tex[0]->addr[TEX_SIZE * sk->tx_y + rend->tx_x]);
	else if (rend->side && rend->stepy > 0)
		return (map->tex[1]->addr[TEX_SIZE * sk->tx_y + rend->tx_x]);
	else if (!rend->side && rend->stepx < 0)
		return (map->tex[2]->addr[TEX_SIZE * sk->tx_y + rend->tx_x]);
	return (map->tex[3]->addr[TEX_SIZE * sk->tx_y + rend->tx_x]);
}

static int	vs_normal(t_map *map, t_render *rend, t_sidekick *sk)
{
	int color;

	color = map->tex[map->map[rend->mapx][rend->mapy] - 1]->
		addr[TEX_SIZE * sk->tx_y + rend->tx_x];
	if (rend->side == 1)
		color = (color >> 1) & 8355711;
	return (color);
}

void		vs_render_wall(t_map *map, t_render *rend, int x)
{
	t_sidekick sk;

	rend->mapx = (int)map->posx;
	rend->mapy = (int)map->posy;
	vs_get_step_side(rend, map->posy, map->posx);
	vs_dda(rend, map->map);
	vs_get_distance(rend, map->posy, map->posx);
	vs_get_line(rend);
	vs_get_wall(rend, map->posy, map->posx);
	vs_get_xcoor(rend, 64);
	while (++rend->draw_s < rend->draw_e)
	{
		sk.d = (rend->draw_s << 8) - (W_HEIGHT << 7)
			+ (rend->line_h << 7);
		sk.tx_y = (((sk.d << 6) / rend->line_h)) >> 8;
		if (map->in.mode)
			sk.color = vs_mandatory(map, rend, &sk);
		else
			sk.color = vs_normal(map, rend, &sk);
		vs_img_set_pixel(map->img, x, rend->draw_s, sk.color);
	}
}
