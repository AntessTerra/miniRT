/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:51:55 by jbartosi          #+#    #+#             */
/*   Updated: 2023/08/15 17:25:25 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include "Libft/libft.h"
# include "minilibx/mlx.h"

# define SCREENWIDTH 1280
# define SCREENHEIGHT 720
# define TEXTUREWIDTH 512
# define TEXTUREHEIGHT 512
# define UDIV 1
# define VDIV 1
# define VMOVE 0.0

typedef struct s_info
{
	int		move_y;
	int		move_x;
	int		rotate;
	int		sprint;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_y;
	int		map_x;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	prep_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
	int		draw;
	double	frame_time;
	double	move_speed;
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;
	int		text_num;
	double	wall_x;
	int		text_x;
	int		text_y;
	double	step;
	double	tex_pos;
	float	ray_dir_x0;
	float	ray_dir_y0;
	float	ray_dir_x1;
	float	ray_dir_y1;
	int		p;
	float	pos_z;
	float	row_distance;
	float	floor_step_x;
	float	floor_step_y;
	float	floor_x;
	float	floor_y;
	int		cell_x;
	int		cell_y;
	int		tx;
	int		ty;
	int		floor_texture;
	int		ceiling_texture;
	double	*zbuffer;
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_x;
	int		draw_start_y;
	int		draw_end_x;
	int		draw_end_y;
	int		tex_x;
	int		d;
	int		tex_y;
	int		stripe;
	int		part;
	int		v_move_screen;
	double	dx;
	double	dy;
	double	t_angle;
	int		text_n;
}				t_info;

typedef struct s_image
{
	void			*img;
	unsigned char	*addr;
	int				bits_pp;
	int				line_len;
	int				endian;
}				t_image;

typedef struct s_sprite
{
	double	x;
	double	y;
	int		texture;
	double	dist;
}				t_sprite;

typedef struct s_player
{
	t_image		h_bar;
	int			h_state;
	int			h_offset;
	t_image		gun_overlay;
	t_image		gun_hotbar;
	int			has_gun;
}				t_player;

typedef struct s_box
{
	void			*mlx;
	void			*win;
	t_image			image;
	t_image			*textures;
	t_sprite		*sprites;
	int				n_sprites;
	t_image			*sheva;
	t_image			*meat;
	t_image			*coin;
	t_image			*handgun;
	char			**map;
	t_info			info;
	size_t			timer;
	struct timeval	time;
	struct timeval	old_time;
	t_player		player;
}				t_box;

int		exit_hook(t_box *box);
int		key_press(int key, t_box *box);
int		key_release(int key, t_box *box);
void	parser(t_box *box, int fd);
void	redraw(t_box *box);
void	init_vals(t_box *box);
void	init_textures(t_box *box);
void	reset_vals(t_box *box);
void	bubble_sort_sprites(t_box *box);

#endif
