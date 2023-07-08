/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:00:23 by jbartosi          #+#    #+#             */
/*   Updated: 2023/07/08 19:05:18 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	reset_vals(t_box *box)
{
	box->info.cameraX = 0;
	box->info.rayDirX = 0;
	box->info.rayDirY = 0;
	box->info.mapX = 0;
	box->info.mapY = 0;
	box->info.hit = 0;
	box->info.textNum = 0;
}

void	my_mlx_pyxel_put(t_image *image, int x, int y, int color)
{
	char	*pixel;

	pixel = image->addr + (y * image->line_len + x
			* (image->bits_pp / 8));
	*(unsigned int *)pixel = color;
}

int	extract_color(char *pixel)
{
	return (pixel[0] << 16 | pixel[1] << 8 | pixel[2]);
}

void	redraw(t_box *box)
{
	int	x;

	mlx_destroy_image(box->mlx, box->image.img);
	box->image.img = mlx_new_image(box->mlx, SCREENWIDTH, SCREENHEIGHT);
	box->image.addr = mlx_get_data_addr(box->image.img, &box->image.bits_pp,
			&box->image.line_len, &box->image.endian);
	x = -1;
	while (++x < SCREENWIDTH)
	{
		reset_vals(box);
		box->info.cameraX = 2 * x / (double)SCREENWIDTH - 1;
		box->info.rayDirX = box->info.dirX + box->info.planeX * box->info.cameraX;
		box->info.rayDirY = box->info.dirY + box->info.planeY * box->info.cameraX;
		box->info.mapX = (int)box->info.posX;
		box->info.mapY = (int)box->info.posY;
		box->info.deltaDistX = fabs(1 / box->info.rayDirX);
		box->info.deltaDistY = fabs(1 / box->info.rayDirY);
		if (box->info.rayDirX < 0)
		{
			box->info.stepX = -1;
			box->info.sideDistX = (box->info.posX - box->info.mapX) * box->info.deltaDistX;
		}
		else
		{
			box->info.stepX = 1;
			box->info.sideDistX = (box->info.mapX + 1.0 - box->info.posX) * box->info.deltaDistX;
		}
		if (box->info.rayDirY < 0)
		{
			box->info.stepY = -1;
			box->info.sideDistY = (box->info.posY - box->info.mapY) * box->info.deltaDistY;
		}
		else
		{
			box->info.stepY = 1;
			box->info.sideDistY = (box->info.mapY + 1.0 - box->info.posY) * box->info.deltaDistY;
		}
		while(!box->info.hit)
		{
			if (box->info.sideDistX < box->info.sideDistY)
			{
				box->info.sideDistX += box->info.deltaDistX;
				box->info.mapX += box->info.stepX;
				box->info.side = 0;
			}
			else
			{
				box->info.sideDistY += box->info.deltaDistY;
				box->info.mapY += box->info.stepY;
				box->info.side = 1;
			}
			if (box->map[box->info.mapX][box->info.mapY] > '0')
				box->info.hit = 1;
		}
		if (!box->info.side)
			box->info.prepWallDist = (box->info.sideDistX - box->info.deltaDistX);
		else
			box->info.prepWallDist = (box->info.sideDistY - box->info.deltaDistY);
		box->info.lineHeight = (int)(SCREENHEIGHT / box->info.prepWallDist);
		box->info.drawStart = -box->info.lineHeight / 2 + SCREENHEIGHT / 2;
		if (box->info.drawStart < 0)
			box->info.drawStart = 0;
		box->info.drawEnd = box->info.lineHeight / 2 + SCREENHEIGHT / 2;
		if (box->info.drawEnd >= SCREENHEIGHT)
			box->info.drawEnd = SCREENHEIGHT - 1;

		box->info.textNum = box->map[box->info.mapX][box->info.mapY] - 1 - '0';
		if (!box->info.side)
			box->info.wallX = box->info.posY + box->info.prepWallDist * box->info.rayDirY;
		else
			box->info.wallX = box->info.posX + box->info.prepWallDist * box->info.rayDirX;
		box->info.wallX -= floor((box->info.wallX));

		box->info.textX = (int)box->info.wallX * (double)TEXTUREWIDTH;
		if (!box->info.side && box->info.rayDirX > 0)
			box->info.textX = TEXTUREWIDTH - box->info.textX - 1;
		if (box->info.side && box->info.rayDirY < 0)
			box->info.textX = TEXTUREWIDTH - box->info.textX - 1;

		box->info.step = 1.0 * TEXTUREHEIGHT / box->info.lineHeight;
		box->info.texPos = (box->info.drawStart - SCREENHEIGHT / 2 + box->info.lineHeight / 2) * box->info.step;

		box->info.draw = box->info.drawStart;
		while (box->info.draw++ < box->info.drawEnd)
		{
			box->info.textY = (int)box->info.texPos & (TEXTUREHEIGHT - 1);
			box->info.texPos += box->info.step;
			//box->info.color = box->info.texture[box->info.textNum][0][50];
			//box->info.color = box->info.texture[box->info.textNum][box->info.textX][box->info.textY];
			//printf("X: %i TEXTX: %i | TEXTY: %i\n", x, box->info.textX, box->info.textY);
			box->info.color = extract_color(&box->eagle.addr[box->info.textX * 4 + box->eagle.line_len * box->info.textY]);
			if (box->info.side)
				box->info.color = (box->info.color >> 1) & 8355711;
			my_mlx_pyxel_put(&box->image, x, box->info.draw, box->info.color);
		}
		/*
		if (box->map[box->info.mapX][box->info.mapY] == '1')
			box->info.color = 0x00FF0000;
		else if (box->map[box->info.mapX][box->info.mapY] == '2')
			box->info.color = 0x0000FF00;
		else if (box->map[box->info.mapX][box->info.mapY] == '3')box->eagle.addr[box->info.textX * 4 + box->eagle.line_len * box->info.textY]
			box->info.color = 0x000000FF;
		else if (box->map[box->info.mapX][box->info.mapY] == '4')
			box->info.color = 0x00FFFFFF;
		else
			box->info.color = 0x00FFFF00;
		*/


	}
	box->info.oldTime = box->info.time;
	box->info.time = box->timer;
	box->info.frameTime = (box->info.time - box->info.oldTime) / 1000.0;
	box->info.moveSpeed = box->info.frameTime * 100.0;
	box->info.rotSpeed = box->info.frameTime * 30.0;
	mlx_put_image_to_window(box->mlx, box->win, box->image.img, 0, 0);
}
