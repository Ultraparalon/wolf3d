/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 20:03:16 by vkaidans          #+#    #+#             */
/*   Updated: 2018/09/04 14:13:43 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			vs_red_button(t_map *map)
{
	(void)map;
	system("killall afplay");
	exit(0);
	return (0);
}

static void	vs_next_level(t_map *map)
{
	(void)map;
	ft_card_destructor((void **)map->map);
	vs_map_gen(map);
	vs_map_valid(map);
}

int			vs_key_down(int key, t_map *map)
{
	if (key == 13 || key == 126)
		map->in.move_forward = 1;
	else if (key == 1 || key == 125)
		map->in.move_backward = 1;
	else if (key == 123 || key == 12)
		map->in.turn_left = 1;
	else if (key == 124 || key == 14)
		map->in.turn_right = 1;
	else if (key == 0)
		map->in.move_left = 1;
	else if (key == 2)
		map->in.move_right = 1;
	else if (key == 49 && !map->stat.loli)
		vs_next_level(map);
	else if (key == 15 && !system("pgrep afplay"))
		system("killall afplay");
	else if (key == 53)
	{
		if (!system("pgrep afplay"))
			system("killall afplay");
		exit(0);
	}
	return (0);
}

int			vs_key_up(int key, t_map *map)
{
	if (key == 46)
		map->in.mode = (map->in.mode) ? 0 : 1;
	if (key == 13 || key == 126)
		map->in.move_forward = 0;
	else if (key == 1 || key == 125)
		map->in.move_backward = 0;
	else if (key == 123 || key == 12)
		map->in.turn_left = 0;
	else if (key == 124 || key == 14)
		map->in.turn_right = 0;
	else if (key == 0)
		map->in.move_left = 0;
	else if (key == 2)
		map->in.move_right = 0;
	return (0);
}
