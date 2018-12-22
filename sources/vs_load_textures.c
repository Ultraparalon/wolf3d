/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_load_testures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 13:22:11 by vkaidans          #+#    #+#             */
/*   Updated: 2018/08/31 13:22:13 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_img	*vs_create_texture(t_map *map, char *file)
{
	t_img *img;

	if (!(img = malloc(sizeof(t_img))))
		ft_error("couldn't allocate memory");
	if (!(img->img = mlx_xpm_file_to_image(map->mlx,
		file, &img->width, &img->height)))
		ft_error(file);
	img->addr = (int *)mlx_get_data_addr(img->img,
		&img->bit_per_pix, &img->size_line, &img->endian);
	return (img);
}

t_img			**vs_load_textures(t_map *map)
{
	t_img **tex;

	if (!(tex = (t_img **)ft_memalloc(sizeof(t_img *) * 20)))
		ft_error("couldn't allocate memory");
	tex[0] = vs_create_texture(map, "textures/blue.XPM");
	tex[1] = vs_create_texture(map, "textures/red.XPM");
	tex[2] = vs_create_texture(map, "textures/purplestone.XPM");
	tex[3] = vs_create_texture(map, "textures/yellow.XPM");
	tex[4] = vs_create_texture(map, "textures/mossy.XPM");
	tex[5] = vs_create_texture(map, "textures/bluestone.XPM");
	tex[6] = vs_create_texture(map, "textures/redbrick.XPM");
	tex[7] = vs_create_texture(map, "textures/greystone.XPM");
	tex[8] = vs_create_texture(map, "textures/slowpoke.XPM");
	tex[9] = vs_create_texture(map, "textures/girl.XPM");
	tex[11] = vs_create_texture(map, "textures/night.XPM");
	tex[12] = vs_create_texture(map, "textures/grass.XPM");
	tex[13] = vs_create_texture(map, "textures/left.XPM");
	tex[14] = vs_create_texture(map, "textures/right.XPM");
	tex[15] = vs_create_texture(map, "textures/detected.XPM");
	tex[16] = vs_create_texture(map, "textures/danger.XPM");
	tex[17] = vs_create_texture(map, "textures/cool.XPM");
	return (tex);
}

static void		vs_sound(char *str)
{
	int fd;

	if ((fd = open(str, O_RDWR)) < 0)
		ft_error("file missing");
	close(fd);
}

void			vs_check_sound(void)
{
	vs_sound("sound/always.mp3");
	vs_sound("sound/little.mp3");
	vs_sound("sound/prison.mp3");
	vs_sound("sound/schism.mp3");
	vs_sound("sound/stinkfist.mp3");
	vs_sound("sound/tuturu.mp3");
	vs_sound("sound/violin.mp3");
	vs_sound("sound/takeonme.mp3");
}
