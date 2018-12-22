/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkaidans <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 18:07:10 by vkaidans          #+#    #+#             */
/*   Updated: 2018/06/09 18:07:12 by vkaidans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include "mlx.h"
# include "fcntl.h"
# include <math.h>
# include <time.h>

# define W_WIDTH 1024
# define W_HEIGHT 800
# define TEX_SIZE 64
# define SKY 512

typedef struct	s_pack
{
	char		**card;
	void		*next;
}				t_pack;

typedef struct	s_sidekick
{
	int			y;
	int			d;
	int			tx_y;
	int			color;
}				t_sidekick;

typedef struct	s_vector
{
	int			clr;
	double		y;
	double		x;
	double		z;
}				t_vector;

typedef struct	s_draw
{
	int			delta_x;
	int			delta_y;
	int			sign_x;
	int			sign_y;
	int			border1;
	int			border2;
}				t_draw;

typedef struct	s_input
{
	char		move_forward;
	char		move_backward;
	char		move_left;
	char		move_right;
	char		turn_left;
	char		turn_right;
	char		mode;
}				t_input;

typedef	struct	s_img
{
	int			height;
	int			width;
	int			bit_per_pix;
	int			size_line;
	int			endian;
	int			*addr;
	void		*img;
}				t_img;

typedef struct	s_floor
{
	double		flr_wallx;
	double		flr_wally;
	double		dst_wall;
	double		dist_player;
	double		curr_dist;
	double		weight;
	double		curr_flrx;
	double		curr_flry;
}				t_floor;

typedef struct	s_render
{
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
	int			side;
	int			line_h;
	int			draw_s;
	int			draw_e;
	int			tx_x;
	double		camera;
	double		ray_dirx;
	double		ray_diry;
	double		side_dstx;
	double		side_dsty;
	double		delta_dstx;
	double		delta_dsty;
	double		perp_walldst;
	double		wall;
}				t_render;

typedef struct	s_stat
{
	int			loli;
	int			score;
	int			time_left;
	t_img		*tex;
}				t_stat;

typedef struct	s_map
{
	int			check;
	int			y;
	int			x;
	int			**map;
	int			**skybox;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	void		*mlx;
	void		*window;
	t_img		**tex;
	t_img		*img;
	t_input		in;
	t_stat		stat;
}				t_map;

void			vs_render(t_map *map);
int				vs_red_button(t_map *map);
int				vs_key_down(int key, t_map *map);
int				vs_key_up(int key, t_map *map);
int				hook_mousemove(int x, int y, t_map *map);
int				vs_loop(t_map *map);
void			vs_img_set_pixel(t_img *img, int x, int y, int color);
void			vs_read_file(t_map *map, char *file);
t_img			**vs_load_textures(t_map *map);
void			vs_check_sound(void);
void			vs_create_map(t_map *map, t_pack *pack);
void			vs_move(t_map *m, double speed);
void			vs_strafe(t_map *m, double speed);
void			vs_rotate(t_map *map, double rotate);
void			vs_render_wall(t_map *map, t_render *rend, int x);
void			vs_render_floor(t_map *m, t_render *rend, int x);
void			vs_render_sky(t_map *map, t_render *rend, int x);
void			vs_render_object(t_map *map, t_render *rend, int x);
void			vs_render_iface(t_map *m);
void			vs_get_step_side(t_render *rend, double posy, double posx);
void			vs_get_wall(t_render *rend, double poxy, double posx);
void			vs_get_distance(t_render *rend, double posy, double posx);
void			vs_get_line(t_render *rend);
void			vs_get_xcoor(t_render *rend, int tex_size);
int				**vs_create_skybox(void);
int				vs_second_pass(void);
void			vs_status(t_map *map, t_stat *stat);
void			vs_map_valid(t_map *map);
void			vs_map_gen(t_map *map);
void			vs_music(void);
t_pack			*vs_list_pack_new(char *str);
void			vs_list_pack_add(t_pack **dest, t_pack *new);
void			vs_list_pack_del(t_pack **pack);

#endif
