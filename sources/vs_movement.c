/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_movement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 11:40:42 by vkaidans          #+#    #+#             */
/*   Updated: 2018/09/14 11:40:43 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	vs_move(t_map *m, double speed)
{
	if (m->map[(int)(m->posx + m->dirx * 2 * speed)][(int)(m->posy)] < 1)
		m->posx += m->dirx * speed;
	if (m->map[(int)(m->posx)][(int)(m->posy + m->diry * 2 * speed)] < 1)
		m->posy += m->diry * speed;
}

void	vs_strafe(t_map *m, double speed)
{
	if (m->map[(int)(m->posx - m->diry * 2 * speed)][(int)(m->posy)] < 1)
		m->posx -= m->diry * speed;
	if (m->map[(int)(m->posx)][(int)(m->posy + m->dirx * 2 * speed)] < 1)
		m->posy += m->dirx * speed;
}

void	vs_rotate(t_map *map, double rotate)
{
	double old_dirx;
	double old_planex;

	old_dirx = map->dirx;
	old_planex = map->planex;
	map->dirx = map->dirx * cos(rotate) - map->diry * sin(rotate);
	map->diry = old_dirx * sin(rotate) + map->diry * cos(rotate);
	map->planex = map->planex * cos(rotate) - map->planey * sin(rotate);
	map->planey = old_planex * sin(rotate) + map->planey * cos(rotate);
}
