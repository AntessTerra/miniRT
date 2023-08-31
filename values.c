/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:15:23 by jbartosi          #+#    #+#             */
/*   Updated: 2023/08/31 14:11:33 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*	Init_textures

	Loads textures into memory
*/
void	init_textures(t_box *box)
{
	int		k;
	int		j;
	int		i;
	char	*path;
	char	*angle[8];

	angle[0] = ANGLE0;
	angle[1] = ANGLE1;
	angle[2] = ANGLE2;
	angle[3] = ANGLE3;
	angle[4] = ANGLE4;
	angle[5] = ANGLE5;
	angle[6] = ANGLE6;
	angle[7] = ANGLE7;

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

	box->sheva = malloc(8 * sizeof(t_image));
	i = -1;
	while (++i < 8)
	{
		path = ft_strjoin("textures/sheva/", angle[i]);
		box->sheva[i].img = mlx_xpm_file_to_image(box->mlx, path, &k, &j);
		if (!box->sheva[i].img)
			box->sheva[i].img = mlx_xpm_file_to_image(box->mlx, "textures/missing.xpm", &k, &j);
		box->sheva[i].addr = (unsigned char *)mlx_get_data_addr(box->sheva[i].img,
				&box->sheva[i].bits_pp, &box->sheva[i].line_len, &box->sheva[i].endian);
		free(path);
	}


	box->meat = malloc(8 * sizeof(t_image));
	i = -1;
	while (++i < 8)
	{
		path = ft_strjoin("textures/meat/", angle[i]);
		box->meat[i].img = mlx_xpm_file_to_image(box->mlx, path, &k, &j);
		if (!box->meat[i].img)
			box->meat[i].img = mlx_xpm_file_to_image(box->mlx, "textures/missing.xpm", &k, &j);
		box->meat[i].addr = (unsigned char *)mlx_get_data_addr(box->meat[i].img,
				&box->meat[i].bits_pp, &box->meat[i].line_len, &box->meat[i].endian);
		free(path);
	}

	box->coin = malloc(8 * sizeof(t_image));
	i = -1;
	while (++i < 8)
	{
		path = ft_strjoin("textures/coin/", angle[i]);
		box->coin[i].img = mlx_xpm_file_to_image(box->mlx, path, &k, &j);
		if (!box->coin[i].img)
			box->coin[i].img = mlx_xpm_file_to_image(box->mlx, "textures/missing.xpm", &k, &j);
		box->coin[i].addr = (unsigned char *)mlx_get_data_addr(box->coin[i].img,
				&box->coin[i].bits_pp, &box->coin[i].line_len, &box->coin[i].endian);
		free(path);
	}

	box->handgun = malloc(8 * sizeof(t_image));
	i = -1;
	while (++i < 8)
	{
		path = ft_strjoin("textures/handgun/", angle[i]);
		box->handgun[i].img = mlx_xpm_file_to_image(box->mlx, path, &k, &j);
		if (!box->handgun[i].img)
			box->handgun[i].img = mlx_xpm_file_to_image(box->mlx, "textures/missing.xpm", &k, &j);
		box->handgun[i].addr = (unsigned char *)mlx_get_data_addr(box->handgun[i].img,
				&box->handgun[i].bits_pp, &box->handgun[i].line_len, &box->handgun[i].endian);
		free(path);
	}

	box->player.h_bar.img = mlx_xpm_file_to_image(box->mlx, "textures/health_bar.xpm", &k, &j);
	if (!box->player.h_bar.img)
		box->player.h_bar.img = mlx_xpm_file_to_image(box->mlx, "textures/missing.xpm", &k, &j);
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
