/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplayer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_ip(t_box *box)
{
	int fd;
	struct ifreq ifr;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0)
		return (1);
	ifr.ifr_addr.sa_family = AF_INET;
	ft_strlcpy(ifr.ifr_name, "enp0s31f6", IFNAMSIZ);
	ioctl(fd, SIOCGIFADDR, &ifr);
	close(fd);
	box->host_ip = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
	return (0);
}

int init_server(t_box *box, int port)
{
	box->server_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (box->server_sock < 0)
		return (printf("ERROR OPENING SOCKET\n"), 1);

	fcntl(box->server_sock, F_SETFL, O_NONBLOCK);

	box->server_addr.sin_family = AF_INET;
	box->server_addr.sin_port = htons(port);
	box->server_addr.sin_addr.s_addr = inet_addr(box->host_ip);

	box->addr_len = sizeof(box->server_addr);

	if (bind(box->server_sock, (struct sockaddr*)&box->server_addr, box->addr_len) < 0)
	{
		printf("ERROR BINDING %s\n", strerror(errno));
		box->frame = 0;
		close(box->server_sock);
		close(box->epoll_sock);
		if (box->sprites != NULL)
		{
			free_sprites(box);
			free_map(box);
			init_vals(box);
		}
		box->game_state = IN_START_MENU;
		return (1);
	}

	struct epoll_event ev;
	box->epoll_sock = epoll_create1(0);

	if (box->epoll_sock < 0)
		return (printf("ERROR CREATING EPOLL\n"), 1);

	ev.events = EPOLLIN;
	ev.data.fd = box->server_sock;

	if(epoll_ctl(box->epoll_sock, EPOLL_CTL_ADD, box->server_sock, &ev))
	{
		close(box->epoll_sock);
		return (printf("ERROR ADDING SOCKET TO EPOLL\n"), 1);
	}
	return (0);
}

int init_client(t_box *box, int port)
{
	box->server_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (box->server_sock < 0)
		return (printf("ERROR OPENING SOCKET\n"), 1);

	fcntl(box->server_sock, F_SETFL, O_NONBLOCK);

	box->server_addr.sin_family = AF_INET;
	box->server_addr.sin_port = htons(port);
	box->server_addr.sin_addr.s_addr = inet_addr(box->input_ip);

	box->addr_len = sizeof(box->server_addr);

	struct epoll_event ev;
	box->epoll_sock = epoll_create1(0);

	if (box->epoll_sock < 0)
		return (printf("ERROR CREATING EPOLL\n"), 1);

	ev.events = EPOLLIN;
	ev.data.fd = box->server_sock;

	if(epoll_ctl(box->epoll_sock, EPOLL_CTL_ADD, box->server_sock, &ev))
	{
		close(box->epoll_sock);
		return (printf("ERROR ADDING SOCKET TO EPOLL\n"), 1);
	}
	box->conn_state = CLIENT_LISTENING;
	return (0);
}

int receive_message(t_box *box, int fd, struct sockaddr_in *client_address, socklen_t *client_address_len)
{
	t_partner	partner;
	// printf("Started receiving from: %i\n", fd);

	int n;

	n = recvfrom(fd, &partner, sizeof(partner), 0, (struct sockaddr *)client_address, client_address_len);

	if (n < 0)
		return (1);

	if (box->game_state == HOSTING_GAME && box->conn_state == SERVER_LISTENING)
	{
		box->conn_state = SERVER_READY;
		// printf("SENDING HELLO TO CLIENT!\n");
		send_update(box, "Hello from server");
	}
	else if (box->game_state == JOINING_GAME && box->conn_state == CLIENT_LISTENING)
	{
		// printf("SERVER READY\n");
		box->conn_state = CLIENT_READY;
	}
	else if (box->game_state == JOINING_GAME && box->conn_state == CLIENT_READY)
	{
		if (!ft_strncmp(partner.message, "START GAME", 11))
		{
			box->game_state = RUNNING_LAN;
			gettimeofday(&box->time, NULL);
		}
	}
	if (!ft_strncmp(partner.message, "PING", 5))
		send_update(box, "PONG");
	box->partner.info.pos_x = partner.info.pos_x;
	box->partner.info.pos_y = partner.info.pos_y;
	box->partner.info.move_x = partner.info.move_x;
	box->partner.info.move_y = partner.info.move_y;
	box->partner.info.rotate = partner.info.rotate;
	box->partner.info.dir_x = partner.info.dir_x;
	box->partner.info.dir_y = partner.info.dir_y;
	box->partner.info.move_speed = partner.info.move_speed;
	if (partner.hp > 0)
	{
		box->partner.info.hit = partner.info.hit;
		box->partner.hit_time = partner.hit_time;
	}
	box->partner.cry = partner.cry;
	box->partner.fire_rate = partner.fire_rate;
	box->partner.max_hp = partner.max_hp;
	box->partner.hp = partner.hp;

	if (!ft_strncmp(partner.message, "DEAD", 5))
	{
		gettimeofday(&box->partner.death_time, NULL);
		box->partner.hp = 0;
		box->partner.state = PARTNER_DOWNED;
		sound_play(box, &box->sound.sfx[DEATH_GARRYS]);
	}
	if (!ft_strncmp(partner.message, "REVIVING", 9))
	{
		gettimeofday(&box->player.hit_time, NULL);
		box->game_state = REVIVING;
	}
	// printf("PARNTER CORDS: %f	%f	CRY:%i\n", box->partner.pos_x, box->partner.pos_y, box->partner.cry);
	gettimeofday(&box->last_message_time, NULL);
	return (0);
}

int send_message(int fd, void *message, int length, struct sockaddr_in *client_address, socklen_t *client_address_len)
{
	// printf("Started sending: %s to fd %i\n", message, fd);
	int n = sendto(fd, message, length, 0, (struct sockaddr *)client_address, *client_address_len);
	// printf("DATA SEND: %i\n", n);
	if (n < 0)
		return (printf("ERROR SENDING %s\n", strerror(errno)), 1);
	if (!ft_strncmp(((t_partner *)message)->message, "UPDATE", 7))
		return (0);
	printf("Send: %s to fd %i\n", ((t_partner *)message)->message, fd);
	return (0);
}

void	send_update(t_box *box, char *message)
{
	box->packet.info.pos_x = box->info.pos_x;
	box->packet.info.pos_y = box->info.pos_y;
	box->packet.info.move_x = box->info.move_x;
	box->packet.info.move_y = box->info.move_y;
	box->packet.info.rotate = box->info.rotate;
	box->packet.info.dir_x = box->info.dir_x;
	box->packet.info.dir_y = box->info.dir_y;
	box->packet.info.move_speed = box->info.move_speed;
	box->packet.info.hit = box->player.hit;
	box->packet.hit_time = box->player.hit_time;
	box->packet.cry = box->player.cry;
	box->packet.fire_rate = box->player.fire_rate;
	box->packet.max_hp = box->player.max_hp;
	box->packet.hp = box->player.hp;
	ft_strlcpy(box->packet.message, message, ft_strlen(message) + 1);
	send_message(box->server_sock, &box->packet, sizeof(struct s_partner), &box->server_addr, &box->addr_len);
}
