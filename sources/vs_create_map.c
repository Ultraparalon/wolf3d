/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_create_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 09:56:00 by vkaidans          #+#    #+#             */
/*   Updated: 2018/09/14 09:56:28 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	vs_convert(int *dest, char **card)
{
	while (*card)
		*dest++ = ft_atoi(*card++);
}

void		vs_create_map(t_map *map, t_pack *pack)
{
	int	**pole;

	if (!(map->map = (int **)ft_memalloc(sizeof(int *) * (map->y + 1))))
		ft_error("couldn't allocate memory");
	pole = map->map;
	while (pack)
	{
		if (!(*pole = (int *)ft_memalloc(sizeof(int) * (map->x + 1))))
			ft_error("couldn't allocate memory");
		vs_convert(*pole, pack->card);
		pack = pack->next;
		pole++;
	}
}

static void	vs_fill_skybox(int **box)
{
	int i;

	i = -1;
	while (++i < 3)
		if (!(box[i] = (int *)ft_memalloc(sizeof(int) * 3)))
			ft_error("couldn't allocate memory");
	box[0][1] = 1;
	box[1][0] = 1;
	box[1][2] = 1;
	box[2][1] = 1;
}

int			**vs_create_skybox(void)
{
	int **ret;

	if (!(ret = (int **)malloc(sizeof(int *) * 4)))
		ft_error("couldn't allocate memory");
	vs_fill_skybox(ret);
	return (ret);
}
