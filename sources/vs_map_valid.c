/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_map_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 13:03:34 by vkaidans          #+#    #+#             */
/*   Updated: 2018/09/12 13:03:36 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	vs_check_val(int **map, int y_max, int x_max)
{
	int y;
	int x;
	int loli;

	loli = 0;
	y = -1;
	while (++y < y_max)
	{
		x = -1;
		while (++x < x_max)
		{
			if (!y || y == y_max - 1 || !x || x == x_max - 1)
				map[y][x] = 1;
			if (map[y][x] > 8)
				map[y][x] = 0;
			if (map[y][x] < 0)
				loli++;
		}
	}
	return (loli);
}

static int	vs_check_pos(int **map, int y, int x)
{
	int amount;

	amount = 0;
	if (map[y - 1][x])
		amount++;
	if (map[y + 1][x])
		amount++;
	if (map[y][x - 1])
		amount++;
	if (map[y][x + 1])
		amount++;
	if (amount < 4)
		return (1);
	return (0);
}

static int	vs_find_start(t_map *map)
{
	int y;
	int x;

	y = 0;
	while (++y < map->y)
	{
		x = 0;
		while (++x < map->x)
			if (map->map[y][x] == 0 && vs_check_pos(map->map, y, x))
			{
				map->posy = x + 0.5;
				map->posx = y + 0.5;
				return (0);
			}
	}
	return (1);
}

void		vs_map_valid(t_map *map)
{
	map->stat.loli = vs_check_val(map->map, map->y, map->x);
	if (vs_find_start(map))
		ft_error("nowhere to spawn");
	vs_music();
}
