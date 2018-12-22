/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 13:46:51 by vkaidans          #+#    #+#             */
/*   Updated: 2018/09/13 13:46:59 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	vs_game_over(t_map *map)
{
	if (system("pgrep afplay"))
		system("afplay sound/violin.mp3 &");
	vs_render(map);
	mlx_put_image_to_window(map->mlx, map->window, map->tex[8]->img, 400, 200);
	mlx_string_put(map->mlx, map->window, 450, 480, 0, "Too slooooooooow");
}

static void	vs_take_loli(t_map *map)
{
	system("afplay sound/tuturu.mp3 &");
	map->map[(int)map->posx][(int)map->posy] = 0;
	map->stat.loli--;
	map->stat.score++;
	map->stat.time_left += 5;
}

int			vs_loop(t_map *map)
{
	if (vs_second_pass())
		vs_status(map, &map->stat);
	if (map->stat.time_left)
	{
		if (map->in.move_forward)
			vs_move(map, 0.14);
		if (map->in.move_backward)
			vs_move(map, -0.14);
		if (map->in.move_left)
			vs_strafe(map, 0.07);
		if (map->in.move_right)
			vs_strafe(map, -0.07);
		if (map->in.turn_right)
			vs_rotate(map, -0.045);
		if (map->in.turn_left)
			vs_rotate(map, 0.045);
		if (map->map[(int)map->posx][(int)map->posy] < 0)
			vs_take_loli(map);
		vs_render(map);
	}
	else
		vs_game_over(map);
	return (0);
}
