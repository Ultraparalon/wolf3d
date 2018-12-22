/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 18:03:41 by vkaidans          #+#    #+#             */
/*   Updated: 2018/09/04 14:09:47 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_img	*vs_new_img(void *mlx, int height, int width)
{
	t_img *img;

	if (!(img = malloc(sizeof(t_img))))
		ft_error("couldn't allocate memory");
	if (!(img->img = mlx_new_image(mlx, width, height)))
		ft_error("couldn't create image");
	img->addr = (int *)mlx_get_data_addr(img->img,
			&img->bit_per_pix, &img->size_line, &img->endian);
	return (img);
}

static t_map	*vs_create(void)
{
	t_map *map;

	if (!(map = malloc(sizeof(t_map))))
		ft_error("couldn't allocate memory");
	if (!(map->mlx = mlx_init()))
		ft_error("couldn't init");
	if (!(map->window = mlx_new_window(map->mlx, W_WIDTH, W_HEIGHT, "Wolf3d")))
		ft_error("couldn't init");
	return (map);
}

static void		vs_init(t_map *map)
{
	map->check = 0;
	map->stat.time_left = 0;
	map->stat.tex = map->tex[13];
	map->stat.loli = 0;
	map->stat.score = 0;
	map->y = 0;
	map->dirx = -1;
	map->diry = 0;
	map->planex = 0;
	map->planey = 0.66;
	map->in.move_forward = 0;
	map->in.move_backward = 0;
	map->in.move_left = 0;
	map->in.move_right = 0;
	map->in.turn_left = 0;
	map->in.turn_right = 0;
	map->in.mode = 0;
}

static void		vs_wizard(char *file)
{
	t_map *map;

	srand(time(0));
	map = vs_create();
	map->img = vs_new_img(map->mlx, W_HEIGHT, W_WIDTH);
	map->skybox = vs_create_skybox();
	map->tex = vs_load_textures(map);
	vs_check_sound();
	vs_init(map);
	if (file)
		vs_read_file(map, file);
	else
		vs_map_gen(map);
	vs_map_valid(map);
	mlx_hook(map->window, 17, 0, vs_red_button, map);
	mlx_hook(map->window, 2, 0, vs_key_down, map);
	mlx_hook(map->window, 3, 0, vs_key_up, map);
	mlx_hook(map->window, 6, 0, hook_mousemove, map);
	mlx_loop_hook(map->mlx, vs_loop, map);
	mlx_loop(map->mlx);
}

int				main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (ft_strstr(argv[1], "dev"))
			ft_error("ha ha, very funny");
		vs_wizard(argv[1]);
	}
	else
		vs_wizard(NULL);
	return (0);
}
