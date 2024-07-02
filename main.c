/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

/* Count_sprites

	Calculates how many sprites needs to be drawn each redraw
*/
int	count_sprites(t_box *box)
{
	int			counter;
	t_sprite	*sprites;

	sprites = box->sprites;
	if (!sprites)
		return (0);
	counter = 1;
	while (sprites->next)
	{
		sprites = sprites->next;
		counter++;
	}
	return (counter);
}

/* Mouse_visibility

	Hides or shows mouse on screen
*/
void mouse_invisibility(t_box* box, bool hide)
{
	if (hide && !box->mouse_hidden)
	{
		mlx_mouse_hide(box->mlx, box->win);
		mlx_mouse_move(box->mlx, box->win, SCREENWIDTH / 2, SCREENHEIGHT / 2);
		box->mouse_hidden = 1;
	}
	else if (!hide && box->mouse_hidden)
	{
		mlx_mouse_show(box->mlx, box->win);
		box->mouse_hidden = 0;
	}
}

/*	Timer

	Function for calculating FPS and redrawing screen every iteration
*/
int	timer(t_box *box)
{
	gettimeofday(&box->time, NULL);
	mlx_mouse_get_pos(box->mlx, box->win, &box->mouse.x, &box->mouse.y);
	if (box->game_state == IN_TITLE_MENU)
	{
		mouse_invisibility(box, false);
		my_mlx_put_image_to_window(box, &box->textures[TITLE_MENU], 0, 0, -1);
		if (((int)((box->time.tv_usec / 100000.0) * 4) / 10) % 2 == 1)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[TITLE_MENU].img, 400, 215, 0, 1000, 450, 450); //press start
		else
			mlx_put_image_to_window(box->mlx, box->win, box->textures[TITLE_MENU].img, 400, 215, 432, 1000, 450, 450); //press start 2
		if (((int)((box->time.tv_usec / 100000.0) * 8) / 10) % 2 == 1)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[TITLE_MENU].img, 1000, 400, 950, 1030, 200, 200); //fly
		else
			mlx_put_image_to_window(box->mlx, box->win, box->textures[TITLE_MENU].img, 1000, 400, 950, 1250, 200, 200); //fly 2
		if (((int)((box->time.tv_usec / 100000.0) * 4) / 10) / 2 == 0)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[TITLE_MENU].img, 275, -10 + ((int)((box->time.tv_usec / 100000.0) * 20) / 10), 280, 740, 800, 300); //logo going down
		else
			mlx_put_image_to_window(box->mlx, box->win, box->textures[TITLE_MENU].img, 275, 10 - ((int)((box->time.tv_usec / 100000.0) * 20) / 10), 280, 740, 800, 300); //logo going up
	}
	else if (box->game_state == IN_START_OPTIONS)
	{
		my_mlx_put_image_to_window(box, &box->textures[MENU_BACK], 0, 0, -1);
		mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU].img, 400, 100, 0, 0, 460, 480);
		mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU].img, 500, 200, 0, 480, 100, 40); //SFX
		mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU].img, 500, 260, 0, 920, 100, 40); //MUSIC

		if (box->options_menu_choice == 1)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU].img, 450, 200, 460, 50, 100, 100); //SFX HIGHLIGTH
		else if (box->options_menu_choice == 2)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU].img, 450, 260, 460, 50, 100, 100); //MUSIC HIGHLIGTH

		mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU].img, 650, 200, 390, 480 + (32 * (int)(10 *  (1.0 - box->sound.sfx_volume))), 150, 32); //SFX VOLUME SLIDER

		mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU].img, 650, 260, 390, 480 + (32 * (int)(10 *  (1.0 - box->sound.music_volume))), 150, 32); //MUSIC VOLUME SLIDER
	}
	else if (box->game_state == IN_START_MENU)
	{
		mouse_invisibility(box, false);
		my_mlx_put_image_to_window(box, &box->textures[MENU_BACK], 0, 0, -1);
		my_mlx_put_image_to_window(box, &box->textures[START_MENU], 0, 0, -1);
		string_to_blacktext(box, 480, 160, "NEW RUN");
		if (box->sprites)
			string_to_blacktext(box, 490, 250, "CONTINUE");
		else
			string_to_graytext(box, 490, 250, "CONTINUE");
		string_to_blacktext(box, 510, 340, "HOST LAN");
		string_to_blacktext(box, 520, 430, "JOIN GAME");
		string_to_blacktext(box, 540, 520, "OPTIONS");
		if (box->start_menu_choice == 1)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 430, 120, 20, 800, 50, 100);
		else if (box->start_menu_choice == 2 && box->sprites)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 440, 210, 20, 800, 50, 100);
		else if (box->start_menu_choice == 3)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 455, 300, 20, 800, 50, 100);
		else if (box->start_menu_choice == 4)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 470, 390, 20, 800, 50, 100);
		else if (box->start_menu_choice == 5)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 480, 480, 20, 800, 50, 100);
	}
	else if (box->game_state == IN_PAUSE_OPTIONS)
	{
		mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU_DARK].img, 400, 100, 0, 0, 460, 480);
		mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU_DARK].img, 500, 200, 0, 480, 100, 40); //SFX
		mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU_DARK].img, 500, 260, 0, 920, 100, 40); //MUSIC

		if (box->options_menu_choice == 1)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU_DARK].img, 450, 200, 460, 50, 100, 100); //SFX HIGHLIGTH
		else if (box->options_menu_choice == 2)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU_DARK].img, 450, 260, 460, 50, 100, 100); //MUSIC HIGHLIGTH

		mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU_DARK].img, 650, 200, 390, 480 + (32 * (int)(10 *  (1.0 - box->sound.sfx_volume))), 150, 32); //SFX VOLUME SLIDER

		mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU_DARK].img, 650, 260, 390, 480 + (32 * (int)(10 *  (1.0 - box->sound.music_volume))), 150, 32); //MUSIC VOLUME SLIDER
	}
	else if (box->game_state == IN_PAUSE_MENU)
	{
		mouse_invisibility(box, false);
		mlx_put_image_to_window(box->mlx, box->win, box->textures[PAUSE_MENU].img, 400, 150, 0, 0, 480, 480);
		if (box->pause_menu_choice == 1)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[PAUSE_MENU].img, 500, 390, 475, 5, 30, 30);
		else if (box->pause_menu_choice == 2)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[PAUSE_MENU].img, 480, 440, 475, 5, 30, 30);
		else if (box->pause_menu_choice == 3)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[PAUSE_MENU].img, 505, 485, 475, 5, 30, 30);
	}
	else if (box->game_state == HOSTING_GAME)
	{
		mouse_invisibility(box, false);
		my_mlx_put_image_to_window(box, &box->textures[MENU_BACK], 0, 0, -1);
		string_to_blacktext(box, 300, 200, "OTHERS, JOIN THIS ADRESS:");
		string_to_blacktext(box, 300, 250, box->multiplayer.host_ip);

		struct epoll_event events[5];
		int nfds = epoll_wait(box->multiplayer.epoll_sock, events, 5, 20);
		int i;
		i = -1;
		while (++i < nfds)
		{
			if (events[i].data.fd == box->multiplayer.server_sock)
			{
				box->multiplayer.client_sock = accept(box->multiplayer.server_sock, NULL, NULL);
				box->multiplayer.n_clients++;
			}
			else if (receive_message(box, events[i].data.fd))
			{
				printf("ERROR RECEIVING MESSAGE\n");
				return (1);
			}
		}
		if (box->multiplayer.connected)
		{
			string_to_blacktext(box, 300, 400, "PRESS ENTER TO START");
			send_message(box, "START", box->multiplayer.client_sock);
		}
		else if (box->multiplayer.n_clients == 1 && !box->multiplayer.connected)
		{
			string_to_blacktext(box, 300, 350, "CONNECTION ESTABLISHED");
			box->multiplayer.input_ip[0] = '1';
			box->multiplayer.input_ip[1] = '0';
			box->multiplayer.input_ip[2] = '.';
			box->multiplayer.input_ip[3] = '1';
			box->multiplayer.input_ip[4] = '2';
			box->multiplayer.input_ip[5] = '.';
			box->multiplayer.input_ip[6] = '4';
			box->multiplayer.input_ip[7] = '.';
			box->multiplayer.input_ip[8] = '4';
			box->multiplayer.input_ip[9] = '\0';
			if (connect_to_server(box, 25568))
				return (1);
			box->multiplayer.connected = true;
		}
		else if (box->multiplayer.n_clients < 1)
		{

			string_to_blacktext(box, 300, 350, "WAITING FOR CONNECTION");
			int x;
			x = (int)((box->time.tv_usec / 100000.0) * 4) / 10;
			while (x-- > 0)
				string_to_blacktext(box, 300 + (x * 50), 400, ".");
		}
	}
	else if (box->game_state == JOINING_GAME)
	{
		mouse_invisibility(box, false);
		my_mlx_put_image_to_window(box, &box->textures[MENU_BACK], 0, 0, -1);
		box->multiplayer.frame = ((((box->time.tv_sec - box->multiplayer.conn_time.tv_sec) + ((box->time.tv_usec - box->multiplayer.conn_time.tv_usec) / 1000000.0)) * 10) * 16) / 10;
		string_to_blacktext(box, 300, 200, "ENTER HOST IP ADDRESS:");
		if (ft_strlen(box->multiplayer.input_ip) > 0)
			string_to_blacktext(box, 300, 250, box->multiplayer.input_ip);
		if (box->multiplayer.client_listening)
		{
			string_to_blacktext(box, 300, 350, "WAITING FOR HOST TO REPLY");
			struct epoll_event events[5];
			int nfds = epoll_wait(box->multiplayer.epoll_sock, events, 5, 20);
			int i;
			i = -1;
			while (++i < nfds)
			{
				if (events[i].data.fd == box->multiplayer.server_sock)
				{
					box->multiplayer.client_sock = accept(box->multiplayer.server_sock, NULL, NULL);
					box->multiplayer.n_clients++;
				}
				else if (receive_message(box, events[i].data.fd))
				{
					printf("ERROR RECEIVING MESSAGE\n");
					return (1);
				}
			}
		}
		else if (box->multiplayer.connected && !box->multiplayer.client_listening)
		{
			string_to_blacktext(box, 300, 300, "CONNECTION ESTABLISHED");
			if (init_server(box, 25568))
				return (1);
			box->multiplayer.client_listening = true;
		}
		else if (box->multiplayer.inputed_ip && box->multiplayer.frame < 85)
		{
			if (!connect_to_server(box, 25567))
				box->multiplayer.connected = true;
			string_to_blacktext(box, 300, 300, "CONNECTING");
			int x;
			x = (int)((box->time.tv_usec / 100000.0) * 4) / 10;
			while (x-- > 0)
				string_to_blacktext(box, 300 + (x * 50), 350, ".");
		}
		else if (box->multiplayer.inputed_ip && box->multiplayer.frame > 85)
		{
			string_to_blacktext(box, 300, 300, "CONNECTION FAILED");
			string_to_blacktext(box, 300, 350, "PRESS ESC TO RETURN");
		}
	}
	else if (box->game_state == RUNNING)
	{
		mouse_invisibility(box, true);
		mlx_mouse_move(box->mlx, box->win, SCREENWIDTH / 2, SCREENHEIGHT / 2);
		redraw(box);
	}
	else if (box->game_state == LOSE)
	{
		box->player.frame = ((((box->time.tv_sec - box->fin_time.tv_sec) + ((box->time.tv_usec - box->fin_time.tv_usec) / 1000000.0)) * 10) * 16) / 10;
		mlx_put_image_to_window(box->mlx, box->win, box->textures[GRIM].img, 400, 100, 400, 0, 512, 512); //DEATH NOTE
		mlx_put_image_to_window(box->mlx, box->win, box->textures[GRIM].img, 650, 300, 64, 64, 64, 64); //POOP
		if (box->player.frame > 85)
			exit_hook(box);
	}
	else if (box->game_state == WIN)
	{
		box->player.frame = ((((box->time.tv_sec - box->fin_time.tv_sec) + ((box->time.tv_usec - box->fin_time.tv_usec) / 1000000.0)) * 10) * 16) / 10;
		my_mlx_put_image_to_window(box, &box->textures[YAY], 400, 100, -1);
		if (box->player.frame > 115)
			exit_hook(box);
	}
	return (0);
}

int	main(void)
{
	t_box	box;

	init_vals(&box);
	box.mlx = mlx_init();
	box.win = mlx_new_window(box.mlx, SCREENWIDTH, SCREENHEIGHT, "cub3d");
	init_textures(&box);
	new_image(box.mlx, &box.image, SCREENWIDTH, SCREENHEIGHT);
	new_image(box.mlx, &box.shaders, SCREENWIDTH, SCREENHEIGHT);
	init_sounds(&box);
	mlx_hook(box.win, 17, 0, exit_hook, &box);
	mlx_hook(box.win, 2, 1L << 0, key_press, &box);
	mlx_hook(box.win, 3, 1L << 1, key_release, &box);
	mlx_hook(box.win, 4, 1L << 2, mouse_press, &box);
	mlx_hook(box.win, 5, 1L << 3, mouse_release, &box);
	mlx_hook(box.win, 6, 1L << 6, mouse_move, &box);
	mlx_loop_hook(box.mlx, timer, &box);
	mlx_loop(box.mlx);
	return (0);
}
