/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:51:55 by jbartosi          #+#    #+#             */
/*   Updated: 2023/07/27 16:18:38 by jbartosi         ###   ########.fr       */
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
# include "Libft/libft.h"
# include "minilibx/mlx.h"

# define SCREENWIDTH 1280
# define SCREENHEIGHT 720
# define TEXTUREWIDTH 64
# define TEXTUREHEIGHT 64

typedef struct s_info
{
	int		move_y;
	int		move_x;
	int		rotate;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	time;
	double	oldTime;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapY;
	int		mapX;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	prepWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		color;
	int		draw;
	double	frameTime;
	double	moveSpeed;
	double	rotSpeed;
	double	oldDirX;
	double	oldPlaneX;
	int		textNum;
	double	wallX;
	int		textX;
	int		textY;
	double	step;
	double	texPos;
	float	rayDirX0;
	float	rayDirY0;
	float	rayDirX1;
	float	rayDirY1;
	int		p;
	float	posZ;
	float	rowDistance;
	float	floorStepX;
	float	floorStepY;
	float	floorX;
	float	floorY;
	int		cellX;
	int		cellY;
	int		tx;
	int		ty;
	int		floorTexture;
	int		ceilingTexture;
	double	*Zbuffer;
	double	spriteX;
	double	spriteY;
	double	invDet;
	double	transformX;
	double	transformY;
	int		spriteScreenX;
	int		spriteHeight;
	int		spriteWidth;
	int		drawStartX;
	int		drawStartY;
	int		drawEndX;
	int		drawEndY;
	int		texX;
	int		d;
	int		texY;
	int		stripe;
	int		part;
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

typedef struct s_box
{
	void		*mlx;
	void		*win;
	t_image		image;
	t_image		*textures;
	t_sprite	*sprites;
	int			n_sprites;
	char		**map;
	t_info		info;
	size_t		timer;
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
