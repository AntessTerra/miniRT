/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:15:23 by jbartosi          #+#    #+#             */
/*   Updated: 2023/07/27 16:19:01 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	Init_textures

	Loads textures into memory
*/
void	init_textures(t_box *box)
{
	int	k;
	int	j;

	box->textures = malloc(11 * sizeof(t_image));
	box->textures[0].img = mlx_xpm_file_to_image(box->mlx, "textures/eagle.xpm", &k, &j);
	box->textures[0].addr = (unsigned char *)mlx_get_data_addr(box->textures[0].img,
			&box->textures[0].bits_pp, &box->textures[0].line_len, &box->textures[0].endian);
	box->textures[1].img = mlx_xpm_file_to_image(box->mlx, "textures/redbrick.xpm", &k, &j);
	box->textures[1].addr = (unsigned char *)mlx_get_data_addr(box->textures[1].img,
			&box->textures[1].bits_pp, &box->textures[1].line_len, &box->textures[1].endian);
	box->textures[2].img = mlx_xpm_file_to_image(box->mlx, "textures/purplestone.xpm", &k, &j);
	box->textures[2].addr = (unsigned char *)mlx_get_data_addr(box->textures[2].img,
			&box->textures[2].bits_pp, &box->textures[2].line_len, &box->textures[2].endian);
	box->textures[3].img = mlx_xpm_file_to_image(box->mlx, "textures/greystone.xpm", &k, &j);
	box->textures[3].addr = (unsigned char *)mlx_get_data_addr(box->textures[3].img,
			&box->textures[3].bits_pp, &box->textures[3].line_len, &box->textures[3].endian);
	box->textures[4].img = mlx_xpm_file_to_image(box->mlx, "textures/bluestone.xpm", &k, &j);
	box->textures[4].addr = (unsigned char *)mlx_get_data_addr(box->textures[4].img,
			&box->textures[4].bits_pp, &box->textures[4].line_len, &box->textures[4].endian);
	box->textures[5].img = mlx_xpm_file_to_image(box->mlx, "textures/mossy.xpm", &k, &j);
	box->textures[5].addr = (unsigned char *)mlx_get_data_addr(box->textures[5].img,
			&box->textures[5].bits_pp, &box->textures[5].line_len, &box->textures[5].endian);
	box->textures[6].img = mlx_xpm_file_to_image(box->mlx, "textures/wood.xpm", &k, &j);
	box->textures[6].addr = (unsigned char *)mlx_get_data_addr(box->textures[6].img,
			&box->textures[6].bits_pp, &box->textures[6].line_len, &box->textures[6].endian);
	box->textures[7].img = mlx_xpm_file_to_image(box->mlx, "textures/colorstone.xpm", &k, &j);
	box->textures[7].addr = (unsigned char *)mlx_get_data_addr(box->textures[7].img,
			&box->textures[7].bits_pp, &box->textures[7].line_len, &box->textures[7].endian);
	box->textures[8].img = mlx_xpm_file_to_image(box->mlx, "textures/barrel.xpm", &k, &j);
	box->textures[8].addr = (unsigned char *)mlx_get_data_addr(box->textures[8].img,
			&box->textures[8].bits_pp, &box->textures[8].line_len, &box->textures[8].endian);
	box->textures[9].img = mlx_xpm_file_to_image(box->mlx, "textures/pillar.xpm", &k, &j);
	box->textures[9].addr = (unsigned char *)mlx_get_data_addr(box->textures[9].img,
			&box->textures[9].bits_pp, &box->textures[9].line_len, &box->textures[9].endian);
	box->textures[10].img = mlx_xpm_file_to_image(box->mlx, "textures/greenlight.xpm", &k, &j);
	box->textures[10].addr = (unsigned char *)mlx_get_data_addr(box->textures[10].img,
			&box->textures[10].bits_pp, &box->textures[10].line_len, &box->textures[10].endian);
}

/*	Init_vals

	Sets most of the values to 0
*/
void	init_vals(t_box *box)
{
	box->info.posX = 22;
	box->info.posY = 11.5;
	box->info.dirX = -1.0;
	box->info.dirY = 0;
	box->info.planeX = 0;
	box->info.planeY = 0.66;
	box->info.time = 0;
	box->info.oldTime = 0;
	box->info.cameraX = 0;
	box->info.rayDirX = 0;
	box->info.rayDirY = 0;
	box->info.rotate = 0;
	box->info.move_x = 0;
	box->info.move_y = 0;
	box->info.hit = 0;
	box->timer = 0;
	box->info.oldDirX = 0;
	box->info.oldPlaneX = 0;
	box->info.Zbuffer = malloc(SCREENWIDTH * sizeof(double));
}

void	reset_vals(t_box *box)
{
	box->info.cameraX = 0;
	box->info.rayDirX = 0;
	box->info.rayDirY = 0;
	box->info.mapX = 0;
	box->info.mapY = 0;
	box->info.hit = 0;
	box->info.textNum = 0;
	box->info.color = 0;
}

void	swap(t_sprite *x, t_sprite *y)
{
	t_sprite	tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

void	bubble_sort_sprites(t_box *box)
{
	int	i;
	int	j;

	i = 0;
	while (i++ < box->n_sprites)
		box->sprites[i].dist = ((box->info.posX - box->sprites[i].x)
				* (box->info.posX - box->sprites[i].x)
				+ (box->info.posY - box->sprites[i].y)
				* (box->info.posY - box->sprites[i].y));
	i = 0;
	while (i++ < box->n_sprites - 1)
	{
		j = 0;
		while (j++ < box->n_sprites - i - 1)
			if (box->sprites[j].dist > box->sprites[j + 1].dist)
				swap(&box->sprites[j], &box->sprites[j + 1]);
	}
	i = -1;
	while (++i < box->n_sprites / 2)
		swap(&box->sprites[i], &box->sprites[box->n_sprites - i - 1]);
}
