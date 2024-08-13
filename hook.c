/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:52:55 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:04:56 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int x, int y, t_box *box)
{
	if (box->game_state == IN_PAUSE_MENU)
	{
		if (x > 540 && x < 740 && y > 380 && y < 420)
			box->pause_menu_choice = 1;
		else if (x > 520 && x < 760 && y > 440 && y < 470)
			box->pause_menu_choice = 2;
		else if (x > 540 && x < 740 && y > 480 && y < 520)
			box->pause_menu_choice = 3;
		else
			box->pause_menu_choice = 0;
	}
	else if (box->game_state == IN_START_MENU)
	{
		if (x > 490 && x < 790 && y > 150 && y < 200)
			box->start_menu_choice = 1;
		else if (x > 500 && x < 790 && y > 240 && y < 290)
			box->start_menu_choice = 2;
		else if (x > 510 && x < 820 && y > 330 && y < 380)
			box->start_menu_choice = 3;
		else if (x > 530 && x < 860 && y > 420 && y < 470)
			box->start_menu_choice = 4;
		else if (x > 540 && x < 800 && y > 500 && y < 560)
			box->start_menu_choice = 5;
		else
			box->start_menu_choice = 0;
	}
	else if (box->game_state == IN_PAUSE_OPTIONS || box->game_state == IN_START_OPTIONS)
	{
		if (x > 490 && x < 790 && y > 200 && y < 240)
			box->options_menu_choice = 1;
		else if (x > 490 && x < 790 && y > 250 && y < 290)
			box->options_menu_choice = 2;
		else
			box->options_menu_choice = 0;
	}
	// else if (box->game_state == RUNNING_LAN)
	// 	send_update(box);
	return (0);
}

int	mouse_press(int keycode, int x, int y, t_box *box)
{
	if (box->game_state == RUNNING || box->game_state == RUNNING_LAN)
	{
		if (keycode == 1)
			box->player.cry = 1;
		if (keycode == 3)
			action_door(box);
	}
	else if (box->game_state == IN_PAUSE_MENU)
	{
		if (box->pause_menu_choice == 1 && keycode == 1)
			box->game_state = IN_PAUSE_OPTIONS;
		else if (box->pause_menu_choice == 2 && keycode == 1)
		{
			if (box->conn_state == CLIENT_READY || box->conn_state == SERVER_READY)
				box->game_state = RUNNING_LAN;
			else
				box->game_state = RUNNING;
			gettimeofday(&box->time, NULL);
		}
		else if (box->pause_menu_choice == 3 && keycode == 1)
		{
			if (box->conn_state == SERVER_READY || box->conn_state == CLIENT_READY)
			{
				close(box->server_sock);
				close(box->epoll_sock);
				if (box->sprites != NULL)
				{
					free_sprites(box);
					free_map(box);
					init_vals(box);
				}
			}
			box->game_state = IN_START_MENU;
		}
	}
	else if (box->game_state == IN_START_MENU)
	{
		if (box->start_menu_choice == 1 && keycode == 1)
		{
			if (box->sprites != NULL)
			{
				free_sprites(box);
				free_map(box);
				init_vals(box);
			}
			int fd;
			fd = open("maps/arena.cub", O_RDONLY);
			parser(box, fd);
			close(fd);
			box->game_state = RUNNING;
			gettimeofday(&box->time, NULL);
		}
		else if (box->start_menu_choice == 2 && keycode == 1 && box->sprites)
		{
			box->game_state = RUNNING;
			gettimeofday(&box->time, NULL);
		}
		else if (box->start_menu_choice == 3 && keycode == 1)
		{
			if (box->sprites != NULL)
			{
				free_sprites(box);
				free_map(box);
				init_vals(box);
			}
			int fd;
			fd = open("maps/hell.cub", O_RDONLY);
			parser(box, fd);
			close(fd);
			gettimeofday(&box->time, NULL);
			sprite_append(box, 4, 3, ISAAC);
			if (get_ip(box) || init_server(box, 25565))
				return (1);
			box->conn_state = SERVER_LISTENING;
			box->game_state = HOSTING_GAME;
		}
		else if (box->start_menu_choice == 4 && keycode == 1)
		{
			if (box->sprites != NULL)
			{
				free_sprites(box);
				free_map(box);
				init_vals(box);
			}
			int fd;
			fd = open("maps/hell.cub", O_RDONLY);
			parser(box, fd);
			close(fd);
			gettimeofday(&box->time, NULL);
			sprite_append(box, 4, 3, ISAAC);
			box->conn_state = CLIENT_WAITING_FOR_INPUT;
			box->game_state = JOINING_GAME;
		}
		else if (box->start_menu_choice == 5 && keycode == 1)
			box->game_state = IN_START_OPTIONS;
	}
	else if (box->game_state == IN_PAUSE_OPTIONS || box->game_state == IN_START_OPTIONS)
	{
		if (y > 200 && y < 240 && keycode == 1)
		{
			if (x > 490 && x < 580)
			{
				if (box->sound.sfx_volume == 0)
					box->sound.sfx_volume = 1;
				else
					box->sound.sfx_volume = 0;
			}
			if (x > 650 && x < 770)
				box->sound.sfx_volume = (float)(x - 650) / (float)120;
			sound_play(box, &box->sound.sfx[OW]);
		}
		else if (y > 250 && y < 290 && keycode == 1)
		{
			if (x > 490 && x < 600)
			{
				if (box->sound.music_volume == 0)
					box->sound.music_volume = 1;
				else
					box->sound.music_volume = 0;
			}
			if (x > 650 && x < 770)
				box->sound.music_volume = (float)(x - 650) / (float)120;
			cs_set_volume(box->sound.playing[0].play, box->sound.music_volume, box->sound.music_volume);
		}
	}
	if (box->game_state == IN_TITLE_MENU && keycode == 1)
		box->game_state = IN_START_MENU;
	// printf("X %i Y %i\n", x, y);
	return (0);
}

int	mouse_release(int keycode, int x, int y, t_box *box)
{
	(void)x;
	(void)y;
	if (keycode == 1)
		box->player.cry = 0;
	return (0);
}

/*	Key_press

	Processes pressed down key
*/
int	key_press(int key, t_box *box)
{
	if (box->game_state == RUNNING || box->game_state == RUNNING_LAN)
	{
		if (key == 113)
			box->info.rotate = -1;
		if (key == 101)
			box->info.rotate = 1;
		if (box->partner.state != PARTNER_REVIVING)
		{
			if (key == 119 || key == 65362)
				box->info.move_x = 1;
			if (key == 115 || key == 65364)
				box->info.move_x = -1;
			if (key == 97 || key == 65361)
				box->info.move_y = -1;
			if (key == 100 || key == 65363)
				box->info.move_y = 1;
		}
		if (key == 65505)
			box->info.sprint = 1;
		if (key == 65365)
			box->info.up_down = 1;
		if (key == 65366)
			box->info.up_down = -1;
		if (key == 32)
			box->info.pos_z = 200;
		if (key == 65507)
			box->info.pos_z = -200;
		if (key == 65477)
		{
			if (box->hud)
				box->hud = 0;
			else
				box->hud = 1;
		}
		if (key == 65293 && box->partner.state == PARTNER_DOWNED && box->player.dist_from_partner < 3)
		{
			box->partner.state = PARTNER_REVIVING;
			gettimeofday(&box->partner.hit_time, NULL);
			send_update(box, "REVIVING");
		}
	}
	if ((key == 32 || key == 65293) && box->game_state == IN_TITLE_MENU)
		box->game_state = IN_START_MENU;
	// printf("Key pressed: %c, Current buffer: %s\n", (char)key, box->input_buffer);
	// printf("Key pressed: %i\n", key);
	// printf("CURRENT POSSITION: %f	%f\n", box->info.pos_x, box->info.pos_y);
	return (0);
}

// void print_binary(unsigned int number)
// {
// 	if (number >> 1) {
// 		print_binary(number >> 1);
// 	}
// 	putc((number & 1) ? '1' : '0', stdout);
// }

/*	Key_release

	Processes let up key
*/
int	key_release(int key, t_box *box)
{
	if (key == 65307)
	{
		if (box->game_state == RUNNING || box->game_state == RUNNING_LAN)
			box->game_state = IN_PAUSE_MENU;
		else if (box->game_state == IN_PAUSE_MENU)
		{
			if (box->conn_state == CLIENT_READY || box->conn_state == SERVER_READY)
				box->game_state = RUNNING_LAN;
			else
				box->game_state = RUNNING;
			gettimeofday(&box->time, NULL);
		}
		else if (box->game_state == IN_PAUSE_OPTIONS)
		{
			box->game_state = IN_PAUSE_MENU;
			gettimeofday(&box->time, NULL);
			box->mouse.x = SCREENWIDTH / 2;
			box->mouse.y = SCREENHEIGHT / 2;
			redraw(box);
		}
		else if (box->game_state == IN_START_OPTIONS)
			box->game_state = IN_START_MENU;
		else if (box->game_state == IN_START_MENU)
			box->game_state = IN_TITLE_MENU;
		else if (box->game_state == IN_TITLE_MENU)
			exit_hook(box);
		else if ((box->game_state == JOINING_GAME && (box->conn_state == CLIENT_SERVER_NOT_FOUND || box->conn_state == CLIENT_WAITING_FOR_INPUT))
					|| box->game_state == HOSTING_GAME || box->game_state == CONNECTION_LOST || box->game_state == DOWNED)
		{
			box->input_ip_index = 0;
			box->input_ip[0] = '\0';
			close(box->server_sock);
			close(box->epoll_sock);
			if (box->sprites != NULL)
			{
				free_sprites(box);
				free_map(box);
				init_vals(box);
			}
			box->game_state = IN_START_MENU;
		}
	}
	if (box->game_state == RUNNING || box->game_state == RUNNING_LAN)
	{
		if (key == 113)
			box->info.rotate = 0;
		if (key == 101)
			box->info.rotate = 0;
		if (key == 119 || key == 65362)
			box->info.move_x = 0;
		if (key == 115 || key == 65364)
			box->info.move_x = 0;
		if (key == 97 || key == 65361)
			box->info.move_y = 0;
		if (key == 100 || key == 65363)
			box->info.move_y = 0;
		if (key == 65505)
			box->info.sprint = 0;
		if (key == 65365 || key == 65366)
			box->info.up_down = 0;
		if (key == 65507)
			box->info.pos_z = 0;
	}
	if (box->game_state == JOINING_GAME && box->conn_state == CLIENT_WAITING_FOR_INPUT)
	{
		if ((key >= 48 && key <= 57 )|| key == 46)
		{
			box->input_ip[box->input_ip_index++] = (char)key;
			box->input_ip[box->input_ip_index] = '\0';
		}
		if (key == 65288)
			box->input_ip[--box->input_ip_index] = '\0';
		if (box->input_ip_index == sizeof(box->input_ip) || key == 65293)
		{
			if (init_client(box, 25565))
				return (printf("ERROR INITIALIZING CLIENT\n"), 1);
			gettimeofday(&box->conn_time, NULL);
			send_update(box, "Hello from client");
		}
	}
	if (box->game_state == HOSTING_GAME && box->conn_state == SERVER_READY && key == 65293)
	{
		send_update(box, "START GAME");
		box->game_state = RUNNING_LAN;
		gettimeofday(&box->time, NULL);
	}

	// printf("Key released: %i\n", key);
	return (0);
}

/*	Exit_hook

	Closes the window when the x in the corner is pressed
*/
int	exit_hook(t_box *box)
{
	free_stuff(box);
	exit(0);
}
