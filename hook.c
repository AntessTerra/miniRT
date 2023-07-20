/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:52:55 by jbartosi          #+#    #+#             */
/*   Updated: 2023/07/20 17:10:10 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(int key, t_box *box)
{
	if (key == 65307)
	{
		mlx_destroy_window(box->mlx, box->win);
		exit(0);
	}
	if (key == 65361) //left
	{
		box->info.oldDirX = box->info.dirX;
		box->info.dirX = box->info.dirX * cos(box->info.rotSpeed) - box->info.dirY * sin(box->info.rotSpeed);
		box->info.dirY = box->info.oldDirX * sin(box->info.rotSpeed) + box->info.dirY * cos(box->info.rotSpeed);
		box->info.oldPlaneX = box->info.planeX;
		box->info.planeX = box->info.planeX * cos(box->info.rotSpeed) - box->info.planeY * sin(box->info.rotSpeed);
		box->info.planeY = box->info.oldPlaneX * sin(box->info.rotSpeed) + box->info.planeY * cos(box->info.rotSpeed);
	}
	if (key == 65363) //right
	{
		box->info.oldDirX = box->info.dirX;
		box->info.dirX = box->info.dirX * cos(-box->info.rotSpeed) - box->info.dirY * sin(-box->info.rotSpeed);
		box->info.dirY = box->info.oldDirX * sin(-box->info.rotSpeed) + box->info.dirY * cos(-box->info.rotSpeed);
		box->info.oldPlaneX = box->info.planeX;
		box->info.planeX = box->info.planeX * cos(-box->info.rotSpeed) - box->info.planeY * sin(-box->info.rotSpeed);
		box->info.planeY = box->info.oldPlaneX * sin(-box->info.rotSpeed) + box->info.planeY * cos(-box->info.rotSpeed);
	}
	if (key == 119) //w
	{
		if (box->map[(int)(box->info.posX + box->info.dirX * box->info.moveSpeed)][(int)box->info.posY] == '0')
			box->info.posX += box->info.dirX * box->info.moveSpeed;
		if (box->map[(int)(box->info.posX)][(int)(box->info.posY + box->info.dirY * box->info.moveSpeed)] == '0')
			box->info.posY += box->info.dirY * box->info.moveSpeed;
	}
	if (key == 97) //a
	{}
	if (key == 115) //s
	{
		if (box->map[(int)(box->info.posX - box->info.dirX * box->info.moveSpeed)][(int)box->info.posY] == '0')
			box->info.posX -= box->info.dirX * box->info.moveSpeed;
		if (box->map[(int)(box->info.posX)][(int)(box->info.posY - box->info.dirY * box->info.moveSpeed)] == '0')
			box->info.posY -= box->info.dirY * box->info.moveSpeed;
	}
	if (key == 100) //d
	{}
	//printf("MAPX: %d | MAPY: %d | POSX: %f | POSY: %f | TIME: %zu | DIRX: %f | DIRY: %f\n", box->info.mapX, box->info.mapY, box->info.posX, box->info.posY, box->timer, box->info.dirX, box->info.dirY);
	//redraw(box);
	//printf("key: %i \n", key);
	return (0);
}

int	exit_hook(t_box *box)
{
	mlx_destroy_window(box->mlx, box->win);
	exit(0);
}
