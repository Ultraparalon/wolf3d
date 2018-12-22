/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 17:30:20 by vkaidans          #+#    #+#             */
/*   Updated: 2018/09/03 16:23:49 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		vs_img_set_pixel(t_img *img, int x, int y, int color)
{
	if (x < 0 || x >= W_WIDTH || y < 0 || y >= W_HEIGHT)
		return ;
	img->addr[x + (y << 10)] = color;
}

static void	vs_init_render(t_map *map, t_render *rend, int x)
{
	rend->camera = (x << 1) / (double)W_WIDTH - 1;
	rend->ray_dirx = map->dirx + map->planex * rend->camera;
	rend->ray_diry = map->diry + map->planey * rend->camera;
	rend->delta_dstx = fabs(1 / rend->ray_dirx);
	rend->delta_dsty = fabs(1 / rend->ray_diry);
}

void		vs_render(t_map *map)
{
	t_render	rend;
	int			x;

	x = -1;
	while (++x < W_WIDTH)
	{
		vs_init_render(map, &rend, x);
		vs_render_sky(map, &rend, x);
		vs_render_wall(map, &rend, x);
		vs_render_floor(map, &rend, x);
		vs_render_object(map, &rend, x);
	}
	mlx_put_image_to_window(map->mlx, map->window, map->img->img, 0, 0);
	vs_render_iface(map);
}
