/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:00:23 by jbartosi          #+#    #+#             */
/*   Updated: 2023/08/07 16:14:30 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pyxel_put(t_image *image, int x, int y, int color)
{
	unsigned char	*pixel;

	pixel = image->addr + (y * image->line_len + x
			* (image->bits_pp / 8));
	*(unsigned int *)pixel = color;
}

int	extract_color(unsigned char *pixel)
{
	return (pixel[2] << 16 | pixel[1] << 8 | pixel[0]);
}

void	redraw(t_box *box)
{
	int	x;
	int	y;
	int	i;

	mlx_destroy_image(box->mlx, box->image.img);
	box->image.img = mlx_new_image(box->mlx, SCREENWIDTH, SCREENHEIGHT);
	box->image.addr = (unsigned char *)mlx_get_data_addr(box->image.img, &box->image.bits_pp,
			&box->image.line_len, &box->image.endian);

	//FLOOR CASTING
	y = -1;
	while (++y < SCREENHEIGHT)
	{
		reset_vals(box);
		box->info.ray_dir_x0 = box->info.dir_x - box->info.plane_x;
		box->info.ray_dir_y0 = box->info.dir_y - box->info.plane_y;
		box->info.ray_dir_x1 = box->info.dir_x + box->info.plane_x;
		box->info.ray_dir_y1 = box->info.dir_y + box->info.plane_y;

		box->info.p = y - SCREENHEIGHT / 2;

		box->info.pos_z = 0.5 * SCREENHEIGHT;

		box->info.row_distance = box->info.pos_z / box->info.p;

		box->info.floor_step_x = box->info.row_distance * (box->info.ray_dir_x1 - box->info.ray_dir_x0) / SCREENWIDTH;
		box->info.floor_step_y = box->info.row_distance * (box->info.ray_dir_y1 - box->info.ray_dir_y0) / SCREENWIDTH;

		box->info.floor_x = box->info.pos_x + box->info.row_distance * box->info.ray_dir_x0;
		box->info.floor_y = box->info.pos_y + box->info.row_distance * box->info.ray_dir_y0;

		x = -1;
		while (++x < SCREENWIDTH)
		{
			box->info.cell_x = (int)(box->info.floor_x);
			box->info.cell_y = (int)(box->info.floor_y);

			box->info.tx = (int)(TEXTUREWIDTH * (box->info.floor_x - box->info.cell_x)) & (TEXTUREWIDTH - 1);
			box->info.ty = (int)(TEXTUREHEIGHT * (box->info.floor_y - box->info.cell_y)) & (TEXTUREHEIGHT - 1);

			box->info.floor_x += box->info.floor_step_x;
			box->info.floor_y += box->info.floor_step_y;

			box->info.floor_texture = 2;
			box->info.ceiling_texture = 4;

			box->info.color = extract_color(&box->textures[box->info.floor_texture].addr[box->info.tx * 4 + box->textures[box->info.floor_texture].line_len * box->info.ty]);
			box->info.color = (box->info.color >> 1) & 8355711;
			my_mlx_pyxel_put(&box->image, x, y, box->info.color);

			box->info.color = extract_color(&box->textures[box->info.ceiling_texture].addr[box->info.tx * 4 + box->textures[box->info.ceiling_texture].line_len * box->info.ty]);
			box->info.color = (box->info.color >> 1) & 8355711;
			my_mlx_pyxel_put(&box->image, x, SCREENHEIGHT - y - 1, box->info.color);
		}
	}

	//WALL CASTING
	x = -1;
	while (++x < SCREENWIDTH)
	{
		reset_vals(box);
		box->info.camera_x = 2 * x / (double)SCREENWIDTH - 1;
		box->info.ray_dir_x = box->info.dir_x + box->info.plane_x * box->info.camera_x;
		box->info.ray_dir_y = box->info.dir_y + box->info.plane_y * box->info.camera_x;
		box->info.map_x = (int)box->info.pos_x;
		box->info.map_y = (int)box->info.pos_y;
		box->info.delta_dist_x = fabs(1 / box->info.ray_dir_x);
		box->info.delta_dist_y = fabs(1 / box->info.ray_dir_y);
		if (box->info.ray_dir_x < 0)
		{
			box->info.step_x = -1;
			box->info.side_dist_x = (box->info.pos_x - box->info.map_x) * box->info.delta_dist_x;
		}
		else
		{
			box->info.step_x = 1;
			box->info.side_dist_x = (box->info.map_x + 1.0 - box->info.pos_x) * box->info.delta_dist_x;
		}
		if (box->info.ray_dir_y < 0)
		{
			box->info.step_y = -1;
			box->info.side_dist_y = (box->info.pos_y - box->info.map_y) * box->info.delta_dist_y;
		}
		else
		{
			box->info.step_y = 1;
			box->info.side_dist_y = (box->info.map_y + 1.0 - box->info.pos_y) * box->info.delta_dist_y;
		}
		while(!box->info.hit)
		{
			if (box->info.side_dist_x < box->info.side_dist_y)
			{
				box->info.side_dist_x += box->info.delta_dist_x;
				box->info.map_x += box->info.step_x;
				box->info.side = 0;
			}
			else
			{
				box->info.side_dist_y += box->info.delta_dist_y;
				box->info.map_y += box->info.step_y;
				box->info.side = 1;
			}
			if (box->map[box->info.map_x][box->info.map_y] > '0')
				box->info.hit = 1;
		}
		if (!box->info.side)
			box->info.prep_wall_dist = (box->info.side_dist_x - box->info.delta_dist_x);
		else
			box->info.prep_wall_dist = (box->info.side_dist_y - box->info.delta_dist_y);
		box->info.line_height = (int)(SCREENHEIGHT / box->info.prep_wall_dist);
		box->info.draw_start = -box->info.line_height / 2 + SCREENHEIGHT / 2;
		if (box->info.draw_start < 0)
			box->info.draw_start = 0;
		box->info.draw_end = box->info.line_height / 2 + SCREENHEIGHT / 2;
		if (box->info.draw_end >= SCREENHEIGHT)
			box->info.draw_end = SCREENHEIGHT - 1;

		box->info.text_num = box->map[box->info.map_x][box->info.map_y] - 1 - '0';
		if (!box->info.side)
			box->info.wall_x = box->info.pos_y + box->info.prep_wall_dist * box->info.ray_dir_y;
		else
			box->info.wall_x = box->info.pos_x + box->info.prep_wall_dist * box->info.ray_dir_x;
		box->info.wall_x -= floor((box->info.wall_x));

		box->info.text_x = (int)(box->info.wall_x * (double)TEXTUREWIDTH);
		if (!box->info.side && box->info.ray_dir_x > 0)
			box->info.text_x = TEXTUREWIDTH - box->info.text_x - 1;
		if (box->info.side && box->info.ray_dir_y < 0)
			box->info.text_x = TEXTUREWIDTH - box->info.text_x - 1;

		box->info.step = 1.0 * TEXTUREHEIGHT / box->info.line_height;
		box->info.tex_pos = (box->info.draw_start - SCREENHEIGHT / 2 + box->info.line_height / 2) * box->info.step;

		box->info.draw = box->info.draw_start;
		while (box->info.draw++ < box->info.draw_end)
		{
			box->info.text_y = (int)box->info.tex_pos & (TEXTUREHEIGHT - 1);
			box->info.tex_pos += box->info.step;
			box->info.color = extract_color(&box->textures[box->info.text_num].addr[box->info.text_x * 4 + box->textures[box->info.text_num].line_len * box->info.text_y]);
			if (box->info.side)
				box->info.color = (box->info.color >> 1) & 8355711;
			my_mlx_pyxel_put(&box->image, x, box->info.draw, box->info.color);
		}
		box->info.zbuffer[x] = box->info.prep_wall_dist;
		//printf("%i: %f\n", x, box->info.zbuffer[x]);
	}

	//SPRITE CASTING
	//printf("now %i\n", box->n_sprites);
	bubble_sort_sprites(box);
	i = -1;
	while (++i < box->n_sprites)
	{
		box->info.sprite_x = box->sprites[i].x - box->info.pos_x;
		box->info.sprite_y = box->sprites[i].y - box->info.pos_y;
		box->info.inv_det = 1.0 / (box->info.plane_x * box->info.dir_y - box->info.dir_x * box->info.plane_y);
		box->info.transform_x = box->info.inv_det * (box->info.dir_y * box->info.sprite_x - box->info.dir_x * box->info.sprite_y);
		box->info.transform_y = box->info.inv_det * (-box->info.plane_y * box->info.sprite_x + box->info.plane_x * box->info.sprite_y);
		box->info.sprite_screen_x = (int)((SCREENWIDTH / 2) * (1 + box->info.transform_x / box->info.transform_y));

		box->info.v_move_screen = (int)(VMOVE / box->info.transform_y);
		box->info.sprite_height = abs((int)(SCREENHEIGHT / (box->info.transform_y))) / VDIV;

		box->info.draw_start_y = (-box->info.sprite_height / 2 + SCREENHEIGHT / 2) + box->info.v_move_screen;
		if (box->info.draw_start_y < 0)
			box->info.draw_start_y = 0;

		box->info.draw_end_y = (box->info.sprite_height / 2 + SCREENHEIGHT / 2) + box->info.v_move_screen;
		if (box->info.draw_end_y >= SCREENHEIGHT)
			box->info.draw_end_y = SCREENHEIGHT - 1;

		box->info.sprite_width = abs((int)(SCREENHEIGHT / (box->info.transform_y))) / UDIV;

		box->info.draw_start_x = -box->info.sprite_width / 2 + box->info.sprite_screen_x;
		if (box->info.draw_start_x < 0)
			box->info.draw_start_x = 0;

		box->info.draw_end_x = box->info.sprite_width / 2 + box->info.sprite_screen_x;
		if (box->info.draw_end_x >= SCREENWIDTH)
			box->info.draw_end_x = SCREENWIDTH - 1;

		box->info.dx = box->sprites[i].x - box->info.pos_x;
		box->info.dy = box->sprites[i].y - box->info.pos_y;
		box->info.t_angle = atan2(box->info.dy, box->info.dx);
		//printf("Angle: %f | %f %f %f - %f %f - %f\n", angle, dx, dy, box->sprites[i].x, box->info.pos_x, box->sprites[i].y, box->info.pos_y);

		box->info.stripe = box->info.draw_start_x;

		while (box->info.stripe++ < box->info.draw_end_x)
		{
			box->info.tex_x = (int)(256 * (box->info.stripe - (-box->info.sprite_width / 2 + box->info.sprite_screen_x)) * TEXTUREWIDTH / box->info.sprite_width) / 256;

			if (box->info.transform_y > 0 && box->info.transform_y < box->info.zbuffer[box->info.stripe])
			{
				//printf("Sprite n: %i // %f > 0 | %d > 0 | %d < %d | %f < %f\n", i, box->info.transform_y, box->info.stripe, box->info.stripe, SCREENWIDTH, box->info.transform_y, box->info.zbuffer[box->info.stripe]);
				box->info.part = box->info.draw_start_y;
				while (box->info.part++ < box->info.draw_end_y)
				{
					box->info.d = (box->info.part) * 256 - SCREENHEIGHT * 128 + box->info.sprite_height * 128;
					box->info.tex_y = ((box->info.d * TEXTUREHEIGHT) / box->info.sprite_height) / 256;
					//printf("Color from: %i\n", box->sprites[i].texture);
					if ((box->info.t_angle > 2.7 && box->info.t_angle < 3.3) || (box->info.t_angle > -3.3 && box->info.t_angle < -2.7))
						box->info.text_n = 0;
					else if (box->info.t_angle > -2.7 && box->info.t_angle < -2.0)
						box->info.text_n = 1;
					else if (box->info.t_angle > -2.0 && box->info.t_angle < -1.2)
						box->info.text_n = 2;
					else if (box->info.t_angle > -1.2 && box->info.t_angle < -0.4)
						box->info.text_n = 3;
					else if (box->info.t_angle > -0.4 && box->info.t_angle < 0.4)
						box->info.text_n = 4;
					else if (box->info.t_angle > 0.4 && box->info.t_angle < 1.2)
						box->info.text_n = 5;
					else if (box->info.t_angle > 1.2 && box->info.t_angle < 2.0)
						box->info.text_n = 6;
					else if (box->info.t_angle > 2.0 && box->info.t_angle < 2.7)
						box->info.text_n = 7;
					else
						box->info.text_n = 0;
					if (box->sprites[i].texture == 100)
						box->info.color = extract_color(&box->sheva[box->info.text_n].addr[box->info.tex_x * 4 + box->sheva[box->info.text_n].line_len * box->info.tex_y]);
					else if (box->sprites[i].texture == 101)
						box->info.color = extract_color(&box->meat[box->info.text_n].addr[box->info.tex_x * 4 + box->meat[box->info.text_n].line_len * box->info.tex_y]);
					else if (box->sprites[i].texture == 102)
						box->info.color = extract_color(&box->coin[(box->timer % 16) / 2].addr[box->info.tex_x * 4 + box->coin[(box->timer % 16) / 2].line_len * box->info.tex_y]);
					else if (box->sprites[i].texture == 103)
						box->info.color = extract_color(&box->handgun[(box->timer % 32) / 4].addr[box->info.tex_x * 4 + box->handgun[(box->timer % 32) / 4].line_len * box->info.tex_y]);
					if ((box->info.color & 0x00FFFFFF) != 0)
						my_mlx_pyxel_put(&box->image, box->info.stripe, box->info.part, box->info.color);
				}
			}
		}


	}

	//Movement
	if (box->info.rotate == 1)
	{
		box->info.old_dir_x = box->info.dir_x;
		box->info.dir_x = box->info.dir_x * cos(-box->info.rot_speed) - box->info.dir_y * sin(-box->info.rot_speed);
		box->info.dir_y = box->info.old_dir_x * sin(-box->info.rot_speed) + box->info.dir_y * cos(-box->info.rot_speed);
		box->info.old_plane_x = box->info.plane_x;
		box->info.plane_x = box->info.plane_x * cos(-box->info.rot_speed) - box->info.plane_y * sin(-box->info.rot_speed);
		box->info.plane_y = box->info.old_plane_x * sin(-box->info.rot_speed) + box->info.plane_y * cos(-box->info.rot_speed);
	}
	else if (box->info.rotate == -1)
	{
		box->info.old_dir_x = box->info.dir_x;
		box->info.dir_x = box->info.dir_x * cos(box->info.rot_speed) - box->info.dir_y * sin(box->info.rot_speed);
		box->info.dir_y = box->info.old_dir_x * sin(box->info.rot_speed) + box->info.dir_y * cos(box->info.rot_speed);
		box->info.old_plane_x = box->info.plane_x;
		box->info.plane_x = box->info.plane_x * cos(box->info.rot_speed) - box->info.plane_y * sin(box->info.rot_speed);
		box->info.plane_y = box->info.old_plane_x * sin(box->info.rot_speed) + box->info.plane_y * cos(box->info.rot_speed);
	}
	if (box->info.move_x == 1)
	{
		if (box->map[(int)(box->info.pos_x + box->info.dir_x * box->info.move_speed)][(int)box->info.pos_y] == '0')
			box->info.pos_x += box->info.dir_x * box->info.move_speed;
		if (box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y + box->info.dir_y * box->info.move_speed)] == '0')
			box->info.pos_y += box->info.dir_y * box->info.move_speed;
	}
	else if (box->info.move_x == -1)
	{
		if (box->map[(int)(box->info.pos_x - box->info.dir_x * box->info.move_speed)][(int)box->info.pos_y] == '0')
			box->info.pos_x -= box->info.dir_x * box->info.move_speed;
		if (box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y - box->info.dir_y * box->info.move_speed)] == '0')
			box->info.pos_y -= box->info.dir_y * box->info.move_speed;
	}
	if (box->info.move_y == 1)
	{
		if (box->map[(int)(box->info.pos_x + box->info.dir_y * box->info.move_speed)][(int)(box->info.pos_y)] == '0')
			box->info.pos_x += box->info.dir_y * box->info.move_speed;
		if (box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y - box->info.dir_x * box->info.move_speed)] == '0')
			box->info.pos_y -= box->info.dir_x * box->info.move_speed;
	}
	else if (box->info.move_y == -1)
	{
		if (box->map[(int)(box->info.pos_x - box->info.dir_y * box->info.move_speed)][(int)(box->info.pos_y)] == '0')
			box->info.pos_x -= box->info.dir_y * box->info.move_speed;
		if (box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y + box->info.dir_x * box->info.move_speed)] == '0')
			box->info.pos_y += box->info.dir_x * box->info.move_speed;
	}

	box->info.old_time = box->info.time;
	box->info.time = box->timer;
	box->info.frame_time = (box->info.time - box->info.old_time) / 1000.0;
	box->info.move_speed = box->info.frame_time * 50.0;
	box->info.rot_speed = box->info.frame_time * 20.0;
	if (box->info.sprint)
	{
		box->info.move_speed *= 2;
		box->info.rot_speed *= 1.5;
	}
	mlx_put_image_to_window(box->mlx, box->win, box->image.img, 0, 0);
}
