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
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	// printf("Started receiving from: %i\n", fd);

	int n;

	if ((box->conn_state == CLIENT_READY && box->game_state != JOINING_GAME) || box->conn_state == SERVER_READY)
	{
		t_partner	another_one;

		n = recvfrom(fd, &another_one, sizeof(another_one), 0, (struct sockaddr *)client_address, client_address_len);

		if (n < 0)
			return (1);
		box->partner.pos_x = another_one.pos_x;
		box->partner.pos_y = another_one.pos_y;
		box->partner.dir_x = another_one.dir_x;
		box->partner.dir_y = another_one.dir_y;
		box->partner.move_speed = another_one.move_speed;
		box->partner.cry = another_one.cry;
		box->partner.move_x = another_one.move_x;
		box->partner.move_y = another_one.move_y;
		box->partner.pos_z = another_one.pos_z;
		// printf("PARNTER CORDS: %f	%f	CRY:%i\n", box->partner.pos_x, box->partner.pos_y, box->partner.cry);
	}
	else
	{
		n = recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr *)client_address, client_address_len);

		if (n < 0)
			return (1);
		buffer[n] = '\0';
		// printf("BUFFER:	%s\n", buffer);
		if (box->game_state == HOSTING_GAME && box->conn_state == SERVER_LISTENING)
		{
			box->conn_state = SERVER_READY;
			// printf("SENDING HELLO TO CLIENT!\n");
			send_message(fd, "Hello from server", ft_strlen("Hello from server"), &box->server_addr, &box->addr_len);
		}
		else if (box->game_state == JOINING_GAME && box->conn_state == CLIENT_LISTENING)
		{
			printf("SERVER READY\n");
			box->conn_state = CLIENT_READY;
		}
		else if (box->game_state == JOINING_GAME && box->conn_state == CLIENT_READY)
		{
			if (!ft_strncmp(buffer, "START GAME", 11))
			{
				box->game_state = RUNNING_LAN;
				gettimeofday(&box->time, NULL);
			}
		}
	}
	return (0);
}

int send_message(int fd, void *message, int length, struct sockaddr_in *client_address, socklen_t *client_address_len)
{
	// printf("Started sending: %s to fd %i\n", message, fd);
	int n = sendto(fd, message, length, 0, (struct sockaddr *)client_address, *client_address_len);
	// printf("DATA SEND: %i\n", n);
	if (n < 0)
		return (printf("ERROR SENDING %s\n", strerror(errno)), 1);
	// printf("Send: %s to fd %i\n", message, fd);
	return (0);
}
