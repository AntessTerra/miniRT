/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/07/08 16:17:01 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_vals(t_box *box)
{
	box->info.posX = 22;
	box->info.posY = 12;
	box->info.dirX = -1.0;
	box->info.dirY = 0;
	box->info.planeX = 0;
	box->info.planeY = 0.66;
	box->info.time = 0;
	box->info.oldTime = 0;
	box->info.cameraX = 0;
	box->info.rayDirX = 0;
	box->info.rayDirY = 0;
	box->info.hit = 0;
	box->timer = 0;
	box->info.oldDirX = 0;
	box->info.oldPlaneX = 0;
}

void	check(t_box *box, int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		return (printf("Error\nNo argument supplied.\n"), exit(1));
	fd = open(argv[1], O_RDONLY);
	if (!fd)
		return (printf("Error\nCannot open file.\n"), exit(1));
	parser(box, fd);
	init_vals(box);
	close(fd);
}

int	timer(t_box *box)
{
	if (box->timer > 1000000000)
		box->timer = 0;
	box->timer++;
	redraw(box);
	return (0);
}

int	main(int argc, char **argv)
{
	t_box	box;
	int		i;

	check(&box, argc, argv);
	i = 0;
	while (i < 100)
	{
		printf("%s", box.map[i++]);
	}
	box.mlx = mlx_init();
	box.win = mlx_new_window(box.mlx, 1280, 720, "cub3d");
	box.image.img = mlx_new_image(box.mlx, 1280, 720);
	box.image.addr = mlx_get_data_addr(box.image.img, &box.image.bits_pp,
			&box.image.line_len, &box.image.endian);
	redraw(&box);
	mlx_hook(box.win, 17, 0, exit_hook, &box);
	mlx_hook(box.win, 2, 1L<<0, key_hook, &box);
	//mlx_key_hook(box.win, key_hook, &box);
	mlx_loop_hook(box.mlx, timer, &box);
	mlx_loop(box.mlx);

	i = 0;
	while (i < 100)
	{
		free(box.map[i++]);
	}
	free(box.map);
	return (0);
}
