/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_render_iface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 16:26:32 by vkaidans          #+#    #+#             */
/*   Updated: 2018/09/11 16:26:34 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	mlx_number_put(t_map *map, int num, int y, int x)
{
	char *tmp;

	tmp = ft_itoa(num);
	mlx_string_put(map->mlx, map->window, x, y, 0xFFFFFF, tmp);
	free(tmp);
}

void		vs_render_iface(t_map *m)
{
	if (m->stat.time_left && !m->stat.loli)
		mlx_put_image_to_window(m->mlx, m->window, m->tex[17]->img, 478, 700);
	else if (m->check)
		mlx_put_image_to_window(m->mlx, m->window, m->tex[15]->img, 478, 700);
	else if (m->stat.time_left < 10)
		mlx_put_image_to_window(m->mlx, m->window, m->tex[16]->img, 478, 700);
	else
		mlx_put_image_to_window(m->mlx, m->window, m->stat.tex->img, 478, 700);
	m->check = 0;
	mlx_string_put(m->mlx, m->window, 612, 710, 0xFFFFFF, "time: ");
	mlx_number_put(m, m->stat.time_left, 710, 675);
	mlx_string_put(m->mlx, m->window, 612, 730, 0xFFFFFF, "loli: ");
	mlx_number_put(m, m->stat.loli, 730, 675);
	mlx_string_put(m->mlx, m->window, 612, 750, 0xFFFFFF, "score: ");
	mlx_number_put(m, m->stat.score, 750, 675);
	if (!m->stat.loli)
		mlx_string_put(m->mlx, m->window, 420, 10, 0xFFFFFF,
			"press 'space' to continue");
}
