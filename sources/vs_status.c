/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_status.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 18:55:15 by vkaidans          #+#    #+#             */
/*   Updated: 2018/09/11 18:55:16 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		vs_second_pass(void)
{
	static int second;

	if (second != clock() / CLOCKS_PER_SEC % 2)
	{
		second = clock() / CLOCKS_PER_SEC % 2;
		return (1);
	}
	return (0);
}

void	vs_status(t_map *map, t_stat *stat)
{
	if (!stat->time_left)
	{
		if (stat->loli && !system("pgrep afplay"))
			system("killall afplay");
		stat->score = 0;
		stat->loli = 0;
		return ;
	}
	if (stat->loli)
		stat->time_left--;
	stat->tex = (stat->tex == map->tex[13]) ? map->tex[14] : map->tex[13];
	if (system("pgrep afplay"))
		vs_music();
}
