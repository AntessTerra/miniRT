/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:52:55 by jbartosi          #+#    #+#             */
/*   Updated: 2023/07/27 14:50:11 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_box *box)
{
	if (key == 113) //q
		box->info.rotate = -1;
	if (key == 101) //e
		box->info.rotate = 1;
	if (key == 119 || key == 65362) //w or up
		box->info.move_x = 1;
	if (key == 115 || key == 65364) //s or down
		box->info.move_x = -1;
	if (key == 97 || key == 65361) //a or left
		box->info.move_y = -1;
	if (key == 100 || key == 65363) //d or right
		box->info.move_y = 1;
	//printf("MAPX: %d | MAPY: %d | POSX: %f | POSY: %f | TIME: %zu | DIRX: %f | DIRY: %f\n", box->info.mapX, box->info.mapY, box->info.posX, box->info.posY, box->timer, box->info.dirX, box->info.dirY);
	//redraw(box);
	//printf("key pressed: %i \n", key);
	return (0);
}

int	key_release(int key, t_box *box)
{
	if (key == 65307)
	{
		mlx_destroy_window(box->mlx, box->win);
		exit(0);
	}
	if (key == 113) //q
		box->info.rotate = 0;
	if (key == 101) //e
		box->info.rotate = 0;
	if (key == 119 || key == 65362) //w or up
		box->info.move_x = 0;
	if (key == 115 || key == 65364) //s or down
		box->info.move_x = 0;
	if (key == 97 || key == 65361) //a or left
		box->info.move_y = 0;
	if (key == 100 || key == 65363) //d or right
		box->info.move_y = 0;
	//printf("MAPX: %d | MAPY: %d | POSX: %f | POSY: %f | TIME: %zu | DIRX: %f | DIRY: %f\n", box->info.mapX, box->info.mapY, box->info.posX, box->info.posY, box->timer, box->info.dirX, box->info.dirY);
	//redraw(box);
	//printf("key released: %i \n", key);
	return (0);
}

int	exit_hook(t_box *box)
{
	mlx_destroy_window(box->mlx, box->win);
	exit(0);
}
