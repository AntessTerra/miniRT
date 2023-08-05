/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antess <antess@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:15:23 by jbartosi          #+#    #+#             */
/*   Updated: 2023/07/29 18:54:11 by antess           ###   ########.fr       */
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
	box->textures[0].img = mlx_xpm_file_to_image(box->mlx, "textures/brick.xpm", &k, &j);
	box->textures[0].addr = (unsigned char *)mlx_get_data_addr(box->textures[0].img,
			&box->textures[0].bits_pp, &box->textures[0].line_len, &box->textures[0].endian);
	box->textures[1].img = mlx_xpm_file_to_image(box->mlx, "textures/wood_mixed.xpm", &k, &j);
	box->textures[1].addr = (unsigned char *)mlx_get_data_addr(box->textures[1].img,
			&box->textures[1].bits_pp, &box->textures[1].line_len, &box->textures[1].endian);
	box->textures[2].img = mlx_xpm_file_to_image(box->mlx, "textures/brick.xpm", &k, &j);
	box->textures[2].addr = (unsigned char *)mlx_get_data_addr(box->textures[2].img,
			&box->textures[2].bits_pp, &box->textures[2].line_len, &box->textures[2].endian);
	box->textures[3].img = mlx_xpm_file_to_image(box->mlx, "textures/brick.xpm", &k, &j);
	box->textures[3].addr = (unsigned char *)mlx_get_data_addr(box->textures[3].img,
			&box->textures[3].bits_pp, &box->textures[3].line_len, &box->textures[3].endian);
	box->textures[4].img = mlx_xpm_file_to_image(box->mlx, "textures/brick.xpm", &k, &j);
	box->textures[4].addr = (unsigned char *)mlx_get_data_addr(box->textures[4].img,
			&box->textures[4].bits_pp, &box->textures[4].line_len, &box->textures[4].endian);
	box->textures[5].img = mlx_xpm_file_to_image(box->mlx, "textures/brick.xpm", &k, &j);
	box->textures[5].addr = (unsigned char *)mlx_get_data_addr(box->textures[5].img,
			&box->textures[5].bits_pp, &box->textures[5].line_len, &box->textures[5].endian);
	box->textures[6].img = mlx_xpm_file_to_image(box->mlx, "textures/brick.xpm", &k, &j);
	box->textures[6].addr = (unsigned char *)mlx_get_data_addr(box->textures[6].img,
			&box->textures[6].bits_pp, &box->textures[6].line_len, &box->textures[6].endian);
	box->textures[7].img = mlx_xpm_file_to_image(box->mlx, "textures/brick.xpm", &k, &j);
	box->textures[7].addr = (unsigned char *)mlx_get_data_addr(box->textures[7].img,
			&box->textures[7].bits_pp, &box->textures[7].line_len, &box->textures[7].endian);
	box->textures[8].img = mlx_xpm_file_to_image(box->mlx, "textures/Sheva/0000.xpm", &k, &j);
	box->textures[8].addr = (unsigned char *)mlx_get_data_addr(box->textures[8].img,
			&box->textures[8].bits_pp, &box->textures[8].line_len, &box->textures[8].endian);
	box->textures[9].img = mlx_xpm_file_to_image(box->mlx, "textures/Sheva/0000.xpm", &k, &j);
	box->textures[9].addr = (unsigned char *)mlx_get_data_addr(box->textures[9].img,
			&box->textures[9].bits_pp, &box->textures[9].line_len, &box->textures[9].endian);
	box->textures[10].img = mlx_xpm_file_to_image(box->mlx, "textures/Sheva/0000.xpm", &k, &j);
	box->textures[10].addr = (unsigned char *)mlx_get_data_addr(box->textures[10].img,
			&box->textures[10].bits_pp, &box->textures[10].line_len, &box->textures[10].endian);

	box->sheva = malloc(8 * sizeof(t_image));
	box->sheva[0].img = mlx_xpm_file_to_image(box->mlx, "textures/Sheva/0000.xpm", &k, &j);
	box->sheva[0].addr = (unsigned char *)mlx_get_data_addr(box->sheva[0].img,
			&box->sheva[0].bits_pp, &box->sheva[0].line_len, &box->textures[10].endian);
	box->sheva[1].img = mlx_xpm_file_to_image(box->mlx, "textures/Sheva/0001.xpm", &k, &j);
	box->sheva[1].addr = (unsigned char *)mlx_get_data_addr(box->sheva[1].img,
			&box->sheva[1].bits_pp, &box->sheva[1].line_len, &box->sheva[1].endian);
	box->sheva[2].img = mlx_xpm_file_to_image(box->mlx, "textures/Sheva/0002.xpm", &k, &j);
	box->sheva[2].addr = (unsigned char *)mlx_get_data_addr(box->sheva[2].img,
			&box->sheva[2].bits_pp, &box->sheva[2].line_len, &box->sheva[2].endian);
	box->sheva[3].img = mlx_xpm_file_to_image(box->mlx, "textures/Sheva/0003.xpm", &k, &j);
	box->sheva[3].addr = (unsigned char *)mlx_get_data_addr(box->sheva[3].img,
			&box->sheva[3].bits_pp, &box->sheva[3].line_len, &box->sheva[3].endian);
	box->sheva[4].img = mlx_xpm_file_to_image(box->mlx, "textures/Sheva/0004.xpm", &k, &j);
	box->sheva[4].addr = (unsigned char *)mlx_get_data_addr(box->sheva[4].img,
			&box->sheva[4].bits_pp, &box->sheva[4].line_len, &box->sheva[4].endian);
	box->sheva[5].img = mlx_xpm_file_to_image(box->mlx, "textures/Sheva/0005.xpm", &k, &j);
	box->sheva[5].addr = (unsigned char *)mlx_get_data_addr(box->sheva[5].img,
			&box->sheva[5].bits_pp, &box->sheva[5].line_len, &box->sheva[5].endian);
	box->sheva[6].img = mlx_xpm_file_to_image(box->mlx, "textures/Sheva/0006.xpm", &k, &j);
	box->sheva[6].addr = (unsigned char *)mlx_get_data_addr(box->sheva[6].img,
			&box->sheva[6].bits_pp, &box->sheva[6].line_len, &box->sheva[6].endian);
	box->sheva[7].img = mlx_xpm_file_to_image(box->mlx, "textures/Sheva/0007.xpm", &k, &j);
	box->sheva[7].addr = (unsigned char *)mlx_get_data_addr(box->sheva[7].img,
			&box->sheva[7].bits_pp, &box->sheva[7].line_len, &box->sheva[7].endian);
}

/*	Init_vals

	Sets most of the values to 0
*/
void	init_vals(t_box *box)
{
	box->info.pos_x = 22;
	box->info.pos_y = 11.5;
	box->info.dir_x = -1.0;
	box->info.dir_y = 0;
	box->info.plane_x = 0;
	box->info.plane_y = 0.66;
	box->info.time = 0;
	box->info.old_time = 0;
	box->info.camera_x = 0;
	box->info.ray_dir_x = 0;
	box->info.ray_dir_y = 0;
	box->info.rotate = 0;
	box->info.move_x = 0;
	box->info.move_y = 0;
	box->info.hit = 0;
	box->timer = 0;
	box->info.old_dir_x = 0;
	box->info.old_plane_x = 0;
	box->info.zbuffer = malloc(SCREENWIDTH * sizeof(double));
}

void	reset_vals(t_box *box)
{
	box->info.camera_x = 0;
	box->info.ray_dir_x = 0;
	box->info.ray_dir_y = 0;
	box->info.map_x = 0;
	box->info.map_y = 0;
	box->info.hit = 0;
	box->info.text_num = 0;
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
		box->sprites[i].dist = ((box->info.pos_x - box->sprites[i].x)
				* (box->info.pos_x - box->sprites[i].x)
				+ (box->info.pos_y - box->sprites[i].y)
				* (box->info.pos_y - box->sprites[i].y));
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
