/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 18:32:19 by vkaidans          #+#    #+#             */
/*   Updated: 2018/09/04 14:15:33 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	vs_get_step_side(t_render *rend, double y, double x)
{
	if (rend->ray_dirx < 0)
	{
		rend->stepx = -1;
		rend->side_dstx = (x - rend->mapx) * rend->delta_dstx;
	}
	else
	{
		rend->stepx = 1;
		rend->side_dstx = (rend->mapx + 1.0 - x) * rend->delta_dstx;
	}
	if (rend->ray_diry < 0)
	{
		rend->stepy = -1;
		rend->side_dsty = (y - rend->mapy) * rend->delta_dsty;
	}
	else
	{
		rend->stepy = 1;
		rend->side_dsty = (rend->mapy + 1.0 - y) * rend->delta_dsty;
	}
}

void	vs_get_wall(t_render *rend, double posy, double posx)
{
	if (rend->side == 0)
		rend->wall = posy + rend->perp_walldst * rend->ray_diry;
	else
		rend->wall = posx + rend->perp_walldst * rend->ray_dirx;
	rend->wall -= floor((rend->wall));
}

void	vs_get_distance(t_render *rend, double posy, double posx)
{
	if (!rend->side)
		rend->perp_walldst =
		(rend->mapx - posx + (1 - rend->stepx) / 2) / rend->ray_dirx;
	else
		rend->perp_walldst =
		(rend->mapy - posy + (1 - rend->stepy) / 2) / rend->ray_diry;
}

void	vs_get_line(t_render *rend)
{
	rend->line_h = (int)(W_HEIGHT / rend->perp_walldst);
	rend->draw_s = (-rend->line_h >> 1) + (W_HEIGHT >> 1);
	if (rend->draw_s < 0)
		rend->draw_s = 0;
	rend->draw_e = (rend->line_h >> 1) + (W_HEIGHT >> 1);
	if (rend->draw_e >= W_HEIGHT)
		rend->draw_e = W_HEIGHT - 1;
}

void	vs_get_xcoor(t_render *rend, int tex_size)
{
	rend->tx_x = (int)(rend->wall * (double)tex_size);
	if (!rend->side && rend->ray_dirx > 0)
		rend->tx_x = tex_size - rend->tx_x - 1;
	if (rend->side && rend->ray_diry < 0)
		rend->tx_x = tex_size - rend->tx_x - 1;
}
