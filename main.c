/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/07/12 19:12:15 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	int		k;
	int		j;

	check(&box, argc, argv);
	box.mlx = mlx_init();
	box.win = mlx_new_window(box.mlx, SCREENWIDTH, SCREENHEIGHT, "cub3d");
	box.textures = malloc(8 * sizeof(t_image));
	box.textures[0].img = mlx_xpm_file_to_image(box.mlx, "textures/eagle.xpm", &k, &j);
	box.textures[0].addr = (unsigned char *)mlx_get_data_addr(box.textures[0].img, &box.textures[0].bits_pp,
			&box.textures[0].line_len, &box.textures[0].endian);
	box.textures[1].img = mlx_xpm_file_to_image(box.mlx, "textures/redbrick.xpm", &k, &j);
	box.textures[1].addr = (unsigned char *)mlx_get_data_addr(box.textures[1].img, &box.textures[1].bits_pp,
			&box.textures[1].line_len, &box.textures[1].endian);
	box.textures[2].img = mlx_xpm_file_to_image(box.mlx, "textures/purplestone.xpm", &k, &j);
	box.textures[2].addr = (unsigned char *)mlx_get_data_addr(box.textures[2].img, &box.textures[2].bits_pp,
			&box.textures[2].line_len, &box.textures[2].endian);
	box.textures[3].img = mlx_xpm_file_to_image(box.mlx, "textures/greystone.xpm", &k, &j);
	box.textures[3].addr = (unsigned char *)mlx_get_data_addr(box.textures[3].img, &box.textures[3].bits_pp,
			&box.textures[3].line_len, &box.textures[3].endian);
	box.textures[4].img = mlx_xpm_file_to_image(box.mlx, "textures/bluestone.xpm", &k, &j);
	box.textures[4].addr = (unsigned char *)mlx_get_data_addr(box.textures[4].img, &box.textures[4].bits_pp,
			&box.textures[4].line_len, &box.textures[4].endian);
	box.textures[5].img = mlx_xpm_file_to_image(box.mlx, "textures/mossy.xpm", &k, &j);
	box.textures[5].addr = (unsigned char *)mlx_get_data_addr(box.textures[5].img, &box.textures[5].bits_pp,
			&box.textures[5].line_len, &box.textures[5].endian);
	box.textures[6].img = mlx_xpm_file_to_image(box.mlx, "textures/wood.xpm", &k, &j);
	box.textures[6].addr = (unsigned char *)mlx_get_data_addr(box.textures[6].img, &box.textures[6].bits_pp,
			&box.textures[6].line_len, &box.textures[6].endian);
	box.textures[7].img = mlx_xpm_file_to_image(box.mlx, "textures/colorstone.xpm", &k, &j);
	box.textures[7].addr = (unsigned char *)mlx_get_data_addr(box.textures[7].img, &box.textures[7].bits_pp,
			&box.textures[7].line_len, &box.textures[7].endian);

	box.image.img = mlx_new_image(box.mlx, SCREENWIDTH, SCREENHEIGHT);
	box.image.addr = (unsigned char *)mlx_get_data_addr(box.image.img, &box.image.bits_pp,
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
