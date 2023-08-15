/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:15:23 by jbartosi          #+#    #+#             */
/*   Updated: 2023/08/15 17:25:48 by jbartosi         ###   ########.fr       */
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
	box->textures[2].img = mlx_xpm_file_to_image(box->mlx, "textures/red_terracotta_floor.xpm", &k, &j);
	box->textures[2].addr = (unsigned char *)mlx_get_data_addr(box->textures[2].img,
			&box->textures[2].bits_pp, &box->textures[2].line_len, &box->textures[2].endian);
	box->textures[3].img = mlx_xpm_file_to_image(box->mlx, "textures/brick.xpm", &k, &j);
	box->textures[3].addr = (unsigned char *)mlx_get_data_addr(box->textures[3].img,
			&box->textures[3].bits_pp, &box->textures[3].line_len, &box->textures[3].endian);
	box->textures[4].img = mlx_xpm_file_to_image(box->mlx, "textures/white_concrete.xpm", &k, &j);
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
	box->textures[8].img = mlx_xpm_file_to_image(box->mlx, "textures/brick.xpm", &k, &j);
	box->textures[8].addr = (unsigned char *)mlx_get_data_addr(box->textures[8].img,
			&box->textures[8].bits_pp, &box->textures[8].line_len, &box->textures[8].endian);
	box->textures[9].img = mlx_xpm_file_to_image(box->mlx, "textures/brick.xpm", &k, &j);
	box->textures[9].addr = (unsigned char *)mlx_get_data_addr(box->textures[9].img,
			&box->textures[9].bits_pp, &box->textures[9].line_len, &box->textures[9].endian);
	box->textures[10].img = mlx_xpm_file_to_image(box->mlx, "textures/brick.xpm", &k, &j);
	box->textures[10].addr = (unsigned char *)mlx_get_data_addr(box->textures[10].img,
			&box->textures[10].bits_pp, &box->textures[10].line_len, &box->textures[10].endian);

	box->sheva = malloc(8 * sizeof(t_image));
	box->sheva[0].img = mlx_xpm_file_to_image(box->mlx, "textures/sheva/0000.xpm", &k, &j);
	box->sheva[0].addr = (unsigned char *)mlx_get_data_addr(box->sheva[0].img,
			&box->sheva[0].bits_pp, &box->sheva[0].line_len, &box->sheva[0].endian);
	box->sheva[1].img = mlx_xpm_file_to_image(box->mlx, "textures/sheva/0001.xpm", &k, &j);
	box->sheva[1].addr = (unsigned char *)mlx_get_data_addr(box->sheva[1].img,
			&box->sheva[1].bits_pp, &box->sheva[1].line_len, &box->sheva[1].endian);
	box->sheva[2].img = mlx_xpm_file_to_image(box->mlx, "textures/sheva/0002.xpm", &k, &j);
	box->sheva[2].addr = (unsigned char *)mlx_get_data_addr(box->sheva[2].img,
			&box->sheva[2].bits_pp, &box->sheva[2].line_len, &box->sheva[2].endian);
	box->sheva[3].img = mlx_xpm_file_to_image(box->mlx, "textures/sheva/0003.xpm", &k, &j);
	box->sheva[3].addr = (unsigned char *)mlx_get_data_addr(box->sheva[3].img,
			&box->sheva[3].bits_pp, &box->sheva[3].line_len, &box->sheva[3].endian);
	box->sheva[4].img = mlx_xpm_file_to_image(box->mlx, "textures/sheva/0004.xpm", &k, &j);
	box->sheva[4].addr = (unsigned char *)mlx_get_data_addr(box->sheva[4].img,
			&box->sheva[4].bits_pp, &box->sheva[4].line_len, &box->sheva[4].endian);
	box->sheva[5].img = mlx_xpm_file_to_image(box->mlx, "textures/sheva/0005.xpm", &k, &j);
	box->sheva[5].addr = (unsigned char *)mlx_get_data_addr(box->sheva[5].img,
			&box->sheva[5].bits_pp, &box->sheva[5].line_len, &box->sheva[5].endian);
	box->sheva[6].img = mlx_xpm_file_to_image(box->mlx, "textures/sheva/0006.xpm", &k, &j);
	box->sheva[6].addr = (unsigned char *)mlx_get_data_addr(box->sheva[6].img,
			&box->sheva[6].bits_pp, &box->sheva[6].line_len, &box->sheva[6].endian);
	box->sheva[7].img = mlx_xpm_file_to_image(box->mlx, "textures/sheva/0007.xpm", &k, &j);
	box->sheva[7].addr = (unsigned char *)mlx_get_data_addr(box->sheva[7].img,
			&box->sheva[7].bits_pp, &box->sheva[7].line_len, &box->sheva[7].endian);

	box->meat = malloc(8 * sizeof(t_image));
	box->meat[0].img = mlx_xpm_file_to_image(box->mlx, "textures/meat/0000.xpm", &k, &j);
	box->meat[0].addr = (unsigned char *)mlx_get_data_addr(box->meat[0].img,
			&box->meat[0].bits_pp, &box->meat[0].line_len, &box->meat[0].endian);
	box->meat[1].img = mlx_xpm_file_to_image(box->mlx, "textures/meat/0001.xpm", &k, &j);
	box->meat[1].addr = (unsigned char *)mlx_get_data_addr(box->meat[1].img,
			&box->meat[1].bits_pp, &box->meat[1].line_len, &box->meat[1].endian);
	box->meat[2].img = mlx_xpm_file_to_image(box->mlx, "textures/meat/0002.xpm", &k, &j);
	box->meat[2].addr = (unsigned char *)mlx_get_data_addr(box->meat[2].img,
			&box->meat[2].bits_pp, &box->meat[2].line_len, &box->meat[2].endian);
	box->meat[3].img = mlx_xpm_file_to_image(box->mlx, "textures/meat/0003.xpm", &k, &j);
	box->meat[3].addr = (unsigned char *)mlx_get_data_addr(box->meat[3].img,
			&box->meat[3].bits_pp, &box->meat[3].line_len, &box->meat[3].endian);
	box->meat[4].img = mlx_xpm_file_to_image(box->mlx, "textures/meat/0004.xpm", &k, &j);
	box->meat[4].addr = (unsigned char *)mlx_get_data_addr(box->meat[4].img,
			&box->meat[4].bits_pp, &box->meat[4].line_len, &box->meat[4].endian);
	box->meat[5].img = mlx_xpm_file_to_image(box->mlx, "textures/meat/0005.xpm", &k, &j);
	box->meat[5].addr = (unsigned char *)mlx_get_data_addr(box->meat[5].img,
			&box->meat[5].bits_pp, &box->meat[5].line_len, &box->meat[5].endian);
	box->meat[6].img = mlx_xpm_file_to_image(box->mlx, "textures/meat/0006.xpm", &k, &j);
	box->meat[6].addr = (unsigned char *)mlx_get_data_addr(box->meat[6].img,
			&box->meat[6].bits_pp, &box->meat[6].line_len, &box->meat[6].endian);
	box->meat[7].img = mlx_xpm_file_to_image(box->mlx, "textures/meat/0007.xpm", &k, &j);
	box->meat[7].addr = (unsigned char *)mlx_get_data_addr(box->meat[7].img,
			&box->meat[7].bits_pp, &box->meat[7].line_len, &box->meat[7].endian);

	box->coin = malloc(8 * sizeof(t_image));
	box->coin[0].img = mlx_xpm_file_to_image(box->mlx, "textures/coin/0000.xpm", &k, &j);
	box->coin[0].addr = (unsigned char *)mlx_get_data_addr(box->coin[0].img,
			&box->coin[0].bits_pp, &box->coin[0].line_len, &box->coin[0].endian);
	box->coin[1].img = mlx_xpm_file_to_image(box->mlx, "textures/coin/0001.xpm", &k, &j);
	box->coin[1].addr = (unsigned char *)mlx_get_data_addr(box->coin[1].img,
			&box->coin[1].bits_pp, &box->coin[1].line_len, &box->coin[1].endian);
	box->coin[2].img = mlx_xpm_file_to_image(box->mlx, "textures/coin/0002.xpm", &k, &j);
	box->coin[2].addr = (unsigned char *)mlx_get_data_addr(box->coin[2].img,
			&box->coin[2].bits_pp, &box->coin[2].line_len, &box->coin[2].endian);
	box->coin[3].img = mlx_xpm_file_to_image(box->mlx, "textures/coin/0003.xpm", &k, &j);
	box->coin[3].addr = (unsigned char *)mlx_get_data_addr(box->coin[3].img,
			&box->coin[3].bits_pp, &box->coin[3].line_len, &box->coin[3].endian);
	box->coin[4].img = mlx_xpm_file_to_image(box->mlx, "textures/coin/0004.xpm", &k, &j);
	box->coin[4].addr = (unsigned char *)mlx_get_data_addr(box->coin[4].img,
			&box->coin[4].bits_pp, &box->coin[4].line_len, &box->coin[4].endian);
	box->coin[5].img = mlx_xpm_file_to_image(box->mlx, "textures/coin/0005.xpm", &k, &j);
	box->coin[5].addr = (unsigned char *)mlx_get_data_addr(box->coin[5].img,
			&box->coin[5].bits_pp, &box->coin[5].line_len, &box->coin[5].endian);
	box->coin[6].img = mlx_xpm_file_to_image(box->mlx, "textures/coin/0006.xpm", &k, &j);
	box->coin[6].addr = (unsigned char *)mlx_get_data_addr(box->coin[6].img,
			&box->coin[6].bits_pp, &box->coin[6].line_len, &box->coin[6].endian);
	box->coin[7].img = mlx_xpm_file_to_image(box->mlx, "textures/coin/0007.xpm", &k, &j);
	box->coin[7].addr = (unsigned char *)mlx_get_data_addr(box->coin[7].img,
			&box->coin[7].bits_pp, &box->coin[7].line_len, &box->coin[7].endian);

	box->handgun = malloc(8 * sizeof(t_image));
	box->handgun[0].img = mlx_xpm_file_to_image(box->mlx, "textures/handgun/0000.xpm", &k, &j);
	box->handgun[0].addr = (unsigned char *)mlx_get_data_addr(box->handgun[0].img,
			&box->handgun[0].bits_pp, &box->handgun[0].line_len, &box->handgun[0].endian);
	box->handgun[1].img = mlx_xpm_file_to_image(box->mlx, "textures/handgun/0001.xpm", &k, &j);
	box->handgun[1].addr = (unsigned char *)mlx_get_data_addr(box->handgun[1].img,
			&box->handgun[1].bits_pp, &box->handgun[1].line_len, &box->handgun[1].endian);
	box->handgun[2].img = mlx_xpm_file_to_image(box->mlx, "textures/handgun/0002.xpm", &k, &j);
	box->handgun[2].addr = (unsigned char *)mlx_get_data_addr(box->handgun[2].img,
			&box->handgun[2].bits_pp, &box->handgun[2].line_len, &box->handgun[2].endian);
	box->handgun[3].img = mlx_xpm_file_to_image(box->mlx, "textures/handgun/0003.xpm", &k, &j);
	box->handgun[3].addr = (unsigned char *)mlx_get_data_addr(box->handgun[3].img,
			&box->handgun[3].bits_pp, &box->handgun[3].line_len, &box->handgun[3].endian);
	box->handgun[4].img = mlx_xpm_file_to_image(box->mlx, "textures/handgun/0004.xpm", &k, &j);
	box->handgun[4].addr = (unsigned char *)mlx_get_data_addr(box->handgun[4].img,
			&box->handgun[4].bits_pp, &box->handgun[4].line_len, &box->handgun[4].endian);
	box->handgun[5].img = mlx_xpm_file_to_image(box->mlx, "textures/handgun/0005.xpm", &k, &j);
	box->handgun[5].addr = (unsigned char *)mlx_get_data_addr(box->handgun[5].img,
			&box->handgun[5].bits_pp, &box->handgun[5].line_len, &box->handgun[5].endian);
	box->handgun[6].img = mlx_xpm_file_to_image(box->mlx, "textures/handgun/0006.xpm", &k, &j);
	box->handgun[6].addr = (unsigned char *)mlx_get_data_addr(box->handgun[6].img,
			&box->handgun[6].bits_pp, &box->handgun[6].line_len, &box->handgun[6].endian);
	box->handgun[7].img = mlx_xpm_file_to_image(box->mlx, "textures/handgun/0007.xpm", &k, &j);
	box->handgun[7].addr = (unsigned char *)mlx_get_data_addr(box->handgun[7].img,
			&box->handgun[7].bits_pp, &box->handgun[7].line_len, &box->handgun[7].endian);

	box->player.h_bar.img = mlx_xpm_file_to_image(box->mlx, "textures/health_bar.xpm", &k, &j);
	box->player.h_bar.addr = (unsigned char *)mlx_get_data_addr(box->player.h_bar.img,
			&box->player.h_bar.bits_pp, &box->player.h_bar.line_len, &box->player.h_bar.endian);

	box->player.gun_overlay.img = mlx_xpm_file_to_image(box->mlx, "textures/gun_overlay.xpm", &k, &j);
	box->player.gun_overlay.addr = (unsigned char *)mlx_get_data_addr(box->player.gun_overlay.img,
			&box->player.gun_overlay.bits_pp, &box->player.gun_overlay.line_len, &box->player.gun_overlay.endian);
	box->player.gun_hotbar.img = mlx_xpm_file_to_image(box->mlx, "textures/gun_hotbar.xpm", &k, &j);
	box->player.gun_hotbar.addr = (unsigned char *)mlx_get_data_addr(box->player.gun_hotbar.img,
			&box->player.gun_hotbar.bits_pp, &box->player.gun_hotbar.line_len, &box->player.gun_hotbar.endian);
}

/*	Init_vals

	Sets most of the values to 0
*/
void	init_vals(t_box *box)
{
	box->info.pos_x = 4;
	box->info.pos_y = 5;
	box->info.dir_x = -1.0;
	box->info.dir_y = 0;
	box->info.plane_x = 0;
	box->info.plane_y = 0.66;
	gettimeofday(&box->time, NULL);
	gettimeofday(&box->old_time, NULL);
	box->info.camera_x = 0;
	box->info.ray_dir_x = 0;
	box->info.ray_dir_y = 0;
	box->info.rotate = 0;
	box->info.move_x = 0;
	box->info.move_y = 0;
	box->info.hit = 0;
	box->info.sprint = 0;
	box->timer = 0;
	box->info.old_dir_x = 0;
	box->info.old_plane_x = 0;
	box->info.zbuffer = malloc(SCREENWIDTH * sizeof(double));
	box->player.h_state = 0;
	box->player.has_gun = 0;
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

	i = -1;
	while (++i < box->n_sprites)
		box->sprites[i].dist = ((box->info.pos_x - box->sprites[i].x)
				* (box->info.pos_x - box->sprites[i].x)
				+ (box->info.pos_y - box->sprites[i].y)
				* (box->info.pos_y - box->sprites[i].y));
	i = -1;
	while (++i < box->n_sprites - 1)
	{
		j = -1;
		while (++j < box->n_sprites - i - 1)
			if (box->sprites[j].dist > box->sprites[j + 1].dist)
				swap(&box->sprites[j], &box->sprites[j + 1]);
	}
	i = -1;
	while (++i < box->n_sprites / 2)
		swap(&box->sprites[i], &box->sprites[box->n_sprites - i - 1]);
}
