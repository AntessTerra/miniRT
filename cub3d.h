/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:51:55 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:04:47 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include <sys/socket.h>
# include <sys/ioctl.h>
# include <net/if.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/epoll.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <dirent.h>
# include <pthread.h>
# include "Libft/libft.h"
# include "minilibx/mlx.h"
# include "cute_png/cute_png.h"
# include "cute_sound/cute_sound.h"
# include <signal.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <errno.h>

# define MOUSE_CONTROL 0
# define SCREENWIDTH 1280
# define SCREENHEIGHT 720
# define TEXTUREWIDTH 64
# define TEXTUREHEIGHT 64
# define UDIV 1
# define VDIV 1
# define VMOVE 0.0
# define MINIMAP_OFFSET 10
# define PI (atan(1) * 4)

typedef struct s_ray
{
	int		end_x;
	int		end_y;
}				t_ray;

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
	double	start_dir_x;
	double	start_dir_y;
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
	double	ene_move_speed;
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
	double	pos_z;
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
	double	now_angle;
	int		text_n;
	double	pitch;
	int		is_floor;
	float	cam_z;
	int		up_down;
	int		distance;
	t_ray	*ray;
	int		to_destroy;
	int		flipped;
	int		door;
	int		door_x;
	int		door_y;
	double	door_dist_x;
	double	door_dist_y;
	int		door_side;
}				t_info;

typedef struct s_image
{
	void			*img;
	unsigned char	*addr;
	int				bits_pp;
	int				line_len;
	int				endian;
	int				height;
	int				width;
	int				n_col;
	int				n_row;
	int				one_x;
	int				one_y;
	char			*name;
}				t_image;

# define IDLE 0
# define AWAKE 1

# define CLOSE 0
# define OPEN 1

# define UP 0
# define DOWN 1
# define LEFT 2
# define RIGHT 3

// Texture numbers
typedef enum e_texture_numbers
{
	WALL,
	BRICKS,
	JAIL,
	FLOOR,
	BABY = 10,
	NERVE_ENDING,
	LEECH,
	ISAAC = 20,
	LARRY_JR_HEAD = 30,
	LARRY_JR_BODY,
	GRIM,
	TEAR = 40,
	YAY,
	KEY = 43,
	UI_PICKUPS,
	UI_HEARTS,
	UI_STATS,
	ITEMS,
	ITEM_ALTAR,
	TROPHY,
	PAUSE_MENU,
	TITLE_MENU,
	START_MENU,
	MENU_BACK,
	OPTIONS_MENU,
	OPTIONS_MENU_DARK,
	FONT,
	FONT_GRAY,
	WIFI,
	DEATH_ANIMATION
}				t_texture_numbers;

//Game states
typedef enum e_game_state
{
	RUNNING,
	RUNNING_LAN,
	CONNECTION_LOST,
	IN_TITLE_MENU,
	IN_START_MENU,
	IN_START_OPTIONS,
	IN_PAUSE_MENU,
	IN_PAUSE_OPTIONS,
	HOSTING_GAME,
	JOINING_GAME,
	LOSE,
	DOWNED,
	REVIVING,
	WIN
}				t_game_state;

typedef enum e_partner_state
{
	ALIVE,
	PARTNER_DOWNED,
	PARTNER_REVIVING,
}				t_partner_state;

//Connection states
typedef enum t_conn_state
{
	SERVER_LISTENING,
	SERVER_READY,
	CLIENT_WAITING_FOR_INPUT,
	CLIENT_LISTENING,
	CLIENT_SERVER_NOT_FOUND,
	CLIENT_READY
}				t_conn_state;

typedef struct s_partner
{
	t_info			info;
	int				cry;
	int				fire_rate;
	int				max_hp;
	int				hp;
	struct timeval	last_tear;
	struct timeval	hit_time;
	struct timeval	death_time;
	char			message[1024];
	t_partner_state	state;
}				t_partner;

typedef struct s_sprite_data
{
	double					x;
	double					y;
	double					start_x;
	double					start_y;
	double					travel;
	int						id;
	t_texture_numbers		texture;
	double					dist;
	double					partner_dist;
	double					dir_x;
	double					dir_y;
	int						state;
	int						frame;
	int						hp;
	int						n_seg;
	int						start_n_seg;
	int						seg;
	int						hit;
	struct timeval			hit_time;
	int						opening;
	struct timeval			action_time;
	int						sound;
}				t_sprite_data;

typedef struct s_sprite
{
	t_sprite_data		*data;
	struct s_sprite		*prev;
	struct s_sprite		*next;
}				t_sprite;

typedef struct s_item_data
{
	int				id;
	int				texture;
}				t_item_data;

typedef struct s_item
{
	t_item_data			*data;
	struct s_item		*prev;
	struct s_item		*next;
}				t_item;

//Sound tracks
typedef enum e_sound_tracks
{
	ANGRY,
	DIE,
	DOOR,
	FAIL,
	FANFARE,
	KEY_PICKUP,
	OW,
	PAIN,
	SHOT,
	SPLASH,
	DEATH_GARRYS
}				t_sound_tracks;

typedef struct s_track
{
	cs_loaded_sound_t	loaded;
	cs_play_sound_def_t	def;
}				t_track;

typedef struct s_box
{
	char			*map_filename;
	char			**env;
	void			*mlx;
	void			*win;
	t_image			image;
	t_image			shaders;
	t_image			*textures;
	t_sprite		*sprites;
	t_item			*items;
	struct s_player
	{
		int				hp;
		int				max_hp;
		int				n_key;
		int				speed;
		int				range;
		int				fire_rate;
		int				shot_speed;
		int				dmg;
		int				cry;
		int				state;
		int				frame;
		int				hit;
		int				dist_from_partner;
		struct timeval	last_tear;
		struct timeval	hit_time;
	}				player;

	t_partner		partner;
	t_partner		packet;
	int				n_sprites;
	char			**map;
	int				map_width;
	int				map_height;
	t_info			info;
	struct timeval	time;
	struct timeval	old_time;
	struct s_mouse
	{
		int		x;
		int		y;
		double	xdistance;
		double	ydistance;
	}					mouse;
	int				hud;
	t_game_state	game_state;
	t_conn_state	conn_state;
	struct timeval	fin_time;
	int				pause_menu_choice;
	int				start_menu_choice;
	int				options_menu_choice;
	int				mouse_hidden;
	struct				s_sound
	{
		cs_context_t	*ctx;
		t_track			music;
		float			music_volume;
		t_track			sfx[20];
		float			sfx_volume;
		struct			s_play
		{
			cs_playing_sound_t	*play;
		}				playing[50];
	}					sound;

	char				*host_ip;
	char				input_ip[15];
	int 				input_ip_index;
	int					server_sock;
	struct sockaddr_in	server_addr;
	socklen_t			addr_len;
	struct timeval		conn_time;
	struct timeval		last_message_time;
	int					frame;
	int					epoll_sock;
	struct epoll_event	events[5];
}				t_box;

//shape rect used for drawing minimap
typedef struct s_rect
{
	int			x;
	int			y;
	double		width;
	double		height;
	int			fill_color;
	int			border_color;
	int			border_width;
}				t_rect;

//shape line
typedef struct s_line
{
	int			begin_x;
	int			begin_y;
	int			end_x;
	int			end_y;
	int			color;
	int			width;
}				t_line;

//Hook.c
int			exit_hook(t_box *box);
int			key_press(int key, t_box *box);
int			key_release(int key, t_box *box);
int			mouse_press(int keycode, int x, int y, t_box *box);
int			mouse_release(int keycode, int x, int y, t_box *box);
int			mouse_move(int x, int y, t_box *box);

//Parser.c
void		parser(t_box *box, int fd);
void		sprite_append(t_box *box, float x, float y, int texture);
void		sprite_remove(t_box *box, t_sprite *to_rem);
t_sprite	*find_seg(t_box *box, int seg);
t_sprite	*find_door(t_box *box, int x, int y);

//Items.c
void		item_append(t_box *box, t_sprite *sprite);
void		item_remove(t_box *box, t_item *to_rem);
t_item		*find_item(t_box *box, int id);

//Values.c
void		init_vals(t_box *box);
void		init_textures(t_box *box);
void		init_sounds(t_box *box);
void		reset_vals(t_box *box);
int			free_sprites(t_box *box);
int			free_map(t_box *box);
void		free_stuff(t_box *box);
void		bubble_sort_sprites(t_box *box);

//Draw_image.c
void		redraw(t_box *box);
int			extract_color(unsigned char *pixel);
void		my_mlx_pyxel_put(t_image *image, int x, int y, int color);
void		my_mlx_put_image_to_window(t_box *box, t_image *image, \
				int x, int y, int sprite_id);
t_image		*new_image(void *mlx, t_image *image, int width, int height);
void		clear_image(t_image *image);
void		png_file_to_image(void *mlx, t_image *image, char *file);
t_image		*img_resize(void *mlx_ptr, t_image *src_img, float n_times_bigger);
void		split_spritesheet(t_image *image, int n_col, \
				int n_row, int one_x, int one_y);
void		apply_fog(t_box *box, double dist);
uint32_t	pixel_visibility(float fade);
void		hit_mark(t_box *box, t_sprite *sprite);

//Casting.c
void		cast_floor(t_box *box);
void		cast_wall(t_box *box);
void		cast_obj(t_box *box);

//Minimap.c
void		drawMinimap(t_box *box);
void		draw_map(t_box *box);
int			get_fill_color(char grid_item, t_box *box, int i, int j);
void		draw_player(t_box *box);
void		draw_rays(t_box *box);

//Graphics.c
void		draw_rect(t_rect *rect, t_box *box);
void		draw_line(t_line *line, t_box *box);
void		string_to_blacktext(t_box *box, int x, int y, char *str);
void		string_to_graytext(t_box *box, int x, int y, char *str);

//Sound.c
void		load_audio_file(t_track *dst, char *path);
void		sound_play(t_box *box, t_track *sound);

//Movement.c
void		cal_move(t_box *box);
void		cal_sprite_move(t_box *box);
void		action_door(t_box *box);

//Main.c
int			count_sprites(t_box *box);

//Multiplayer.c
int			get_ip(t_box* box);
int			init_server(t_box *box, int port);
int			init_client(t_box *box, int port);

void		send_update(t_box *box, char *message);
int 		receive_message(t_box *box, int fd, struct sockaddr_in *client_address, socklen_t *client_address_len);

#endif
