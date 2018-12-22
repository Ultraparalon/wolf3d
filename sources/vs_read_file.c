/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 14:28:28 by vkaidans          #+#    #+#             */
/*   Updated: 2018/08/29 14:28:31 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		vs_get_desu(char *file)
{
	int file_desu;

	if ((file_desu = open(file, O_RDWR)) < 0)
		ft_error("no such file");
	return (file_desu);
}

static t_pack	*vs_get_package(int file_desu)
{
	t_pack	*package;
	char	*tmp;

	package = NULL;
	while (get_next_line(file_desu, &tmp) > 0)
	{
		vs_list_pack_add(&package, vs_list_pack_new(tmp));
		ft_strdel(&tmp);
	}
	return (package);
}

static int		vs_card_size(char **card)
{
	int	len;

	len = 0;
	while (*card++)
		len++;
	return (len);
}

static void		vs_get_size(t_map *map, t_pack *pack)
{
	map->x = vs_card_size(pack->card);
	while (pack)
	{
		if (map->x != vs_card_size(pack->card))
			ft_error("bad size of map");
		map->y++;
		pack = pack->next;
	}
	if (map->x < 4 || map->y < 4)
		ft_error("map is too small");
	if (map->x > 10000 || map->y > 10000)
		ft_error("map is too large");
}

void			vs_read_file(t_map *map, char *file)
{
	t_pack	*pack;
	int		file_desu;

	file_desu = vs_get_desu(file);
	if (!(pack = vs_get_package(file_desu)))
		ft_error("no input");
	vs_get_size(map, pack);
	vs_create_map(map, pack);
	vs_list_pack_del(&pack);
	map->stat.time_left += (map->x + map->y);
}
