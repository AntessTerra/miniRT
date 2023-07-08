/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/07/08 18:17:27 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_box *box)
{
	int	n;
	int	x;
	int	y;

	n = 0;
	box->info.texture = malloc(8 * sizeof(int *));
	while (n < 8)
	{
		box->info.texture[n] = malloc(TEXTUREHEIGHT * sizeof(int *));
		x = 0;
		while (x < TEXTUREHEIGHT)
		{
			box->info.texture[n][x] = malloc(TEXTUREWIDTH * sizeof(int *));
			y = 0;
			while (y < TEXTUREWIDTH)
			{
				box->info.texture[n][x][y++] = 0;
			}
			x++;
		}
		n++;
	}
	x = 0;
	while (x < TEXTUREHEIGHT)
	{
		y = 0;
		while (y < TEXTUREWIDTH)
		{
			int xorcolor = (x * 256 / TEXTUREWIDTH) ^ (y * 256 / TEXTUREHEIGHT);
			//int xcolor = x * 256 / texWidth;
			int ycolor = y * 256 / TEXTUREHEIGHT;
			int xycolor = y * 128 / TEXTUREHEIGHT + x * 128 / TEXTUREWIDTH;
			box->info.texture[0][x][y] = 65536 * 254 * (x != y && x != TEXTUREWIDTH - y); //flat red with black cross
			box->info.texture[1][x][y] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			box->info.texture[2][x][y] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			box->info.texture[3][x][y] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			box->info.texture[4][x][y] = 256 * xorcolor; //xor green
			box->info.texture[5][x][y] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			box->info.texture[6][x][y] = 65536 * ycolor; //red gradient
			box->info.texture[7][x][y++] = 128 + 256 * 128 + 65536 * 128; //flat grey
		}
		x++;
	}
}

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
	init_textures(box);
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
	i = 0;
	while (i < 100)
	{
		printf("%s", box.map[i++]);
	}
	box.mlx = mlx_init();
	box.win = mlx_new_window(box.mlx, SCREENWIDTH, SCREENHEIGHT, "cub3d");
	box.eagle.img = mlx_xpm_file_to_image(box.mlx, "textures/eagle.xpm", &k, &j);
	box.eagle.addr = mlx_get_data_addr(box.eagle.img, &box.eagle.bits_pp,
			&box.eagle.line_len, &box.eagle.endian);
	box.image.img = mlx_new_image(box.mlx, SCREENWIDTH, SCREENHEIGHT);
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
