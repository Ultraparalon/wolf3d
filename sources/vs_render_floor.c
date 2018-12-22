/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_render_floor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:39:19 by vkaidans          #+#    #+#             */
/*   Updated: 2018/09/04 12:16:26 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	vs_get_side(t_render *rend, t_floor *f)
{
	if (rend->side == 0 && rend->ray_dirx > 0)
	{
		f->flr_wallx = rend->mapx;
		f->flr_wally = rend->mapy + rend->wall;
	}
	else if (rend->side == 0 && rend->ray_dirx < 0)
	{
		f->flr_wallx = rend->mapx + 1.0;
		f->flr_wally = rend->mapy + rend->wall;
	}
	else if (rend->side == 1 && rend->ray_diry > 0)
	{
		f->flr_wallx = rend->mapx + rend->wall;
		f->flr_wally = rend->mapy;
	}
	else
	{
		f->flr_wallx = rend->mapx + rend->wall;
		f->flr_wally = rend->mapy + 1.0;
	}
}

void		vs_render_floor(t_map *m, t_render *rend, int x)
{
	t_floor		f;
	t_sidekick	sk;

	vs_get_side(rend, &f);
	f.dst_wall = rend->perp_walldst;
	f.dist_player = 0.0;
	if (rend->draw_e < 0)
		rend->draw_e = W_HEIGHT;
	sk.y = rend->draw_e;
	while (sk.y < W_HEIGHT)
	{
		f.curr_dist = W_HEIGHT / (2.0 * sk.y - W_HEIGHT);
		f.weight = (f.curr_dist - f.dist_player) / (f.dst_wall - f.dist_player);
		f.curr_flrx = f.weight * f.flr_wallx + (1.0 - f.weight) * m->posx;
		f.curr_flry = f.weight * f.flr_wally + (1.0 - f.weight) * m->posy;
		rend->tx_x = (int)(f.curr_flrx * TEX_SIZE) % TEX_SIZE;
		sk.tx_y = (int)(f.curr_flry * TEX_SIZE) % TEX_SIZE;
		vs_img_set_pixel(m->img, x, sk.y,
			(m->tex[12]->addr[(sk.tx_y << 6) + rend->tx_x] >> 1) & 8355711);
		sk.y++;
	}
}
