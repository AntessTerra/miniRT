/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antess <antess@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/07/29 20:47:40 by antess           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Count_sprites

	Calculates how many sprites needs to be drawn each redraw
*/
int	count_sprites(t_box *box)
{
	int	i;

	i = 0;
	while (box->sprites[i].x != 0)
		i++;
	return (i);
}

/*	Check

	Basic function for checking inputs
*/
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
	box->n_sprites = count_sprites(box);
	close(fd);
}

/*	Timer

	Function for calculating FPS and redrawing screen every iteration
*/
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

	check(&box, argc, argv);
	box.mlx = mlx_init();
	box.win = mlx_new_window(box.mlx, SCREENWIDTH, SCREENHEIGHT, "cub3d");
	init_textures(&box);
	box.image.img = mlx_new_image(box.mlx, SCREENWIDTH, SCREENHEIGHT);
	box.image.addr = (unsigned char *)mlx_get_data_addr(box.image.img,
			&box.image.bits_pp, &box.image.line_len, &box.image.endian);
	redraw(&box);
	mlx_hook(box.win, 17, 0, exit_hook, &box);
	mlx_hook(box.win, 2, 1L << 0, key_press, &box);
	mlx_hook(box.win, 3, 1L << 1, key_release, &box);
	mlx_loop_hook(box.mlx, timer, &box);
	mlx_loop(box.mlx);
	return (0);
}
