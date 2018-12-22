/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_map_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 11:56:31 by vkaidans          #+#    #+#             */
/*   Updated: 2018/09/12 11:56:35 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	vs_create(t_map *map)
{
	int **pole;
	int y;

	if (!(map->map = (int **)ft_memalloc(sizeof(int *) * (map->y + 1))))
		ft_error("couldn't allocate memory");
	pole = map->map;
	y = -1;
	while (++y < map->y)
	{
		if (!(*pole = (int *)ft_memalloc(sizeof(int) * (map->x + 1))))
			ft_error("couldn't allocate memory");
		pole++;
	}
}

static void	vs_gen_val(int **map, int y_max, int x_max)
{
	int y;
	int x;
	int tmp;

	y = -1;
	while (++y < y_max)
	{
		x = -1;
		while (++x < x_max)
		{
			tmp = rand() % 100;
			map[y][x] = (tmp > 8) ? 0 : tmp;
		}
	}
}

static int	vs_check_pos(int **map, int y, int x)
{
	int amount;

	amount = 0;
	if (map[y - 1][x] > 0)
		amount++;
	if (map[y][x - 1] > 0)
		amount++;
	if (map[y + 1][x] > 0)
		amount++;
	if (map[y][x + 1] > 0)
		amount++;
	if (amount == 3)
	{
		map[y][x] = -1;
		return (1);
	}
	if (amount == 2 &&
		((map[y][x - 1] > 0 && map[y][x + 1] > 0) ||
			(map[y - 1][x] > 0 && map[y + 1][x] > 0)))
	{
		map[y][x] = -1;
		return (1);
	}
	return (0);
}

static void	vs_loli_gen(int **map, int y_max, int x_max)
{
	int y;
	int x;
	int loli;

	loli = y_max;
	y = y_max - 1;
	while (--y > 0)
	{
		x = x_max;
		while (loli && --x > 0)
			if (!map[y][x])
				loli -= vs_check_pos(map, y, x);
	}
}

void		vs_map_gen(t_map *map)
{
	map->y = 10 + rand() % 95;
	map->x = 10 + rand() % 95;
	vs_create(map);
	vs_gen_val(map->map, map->y, map->x);
	vs_loli_gen(map->map, map->y, map->x);
	map->stat.time_left += (map->y + map->x);
}
