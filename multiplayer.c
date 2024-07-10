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
	box->server.host_ip = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
	return (0);
}

int init_server(t_box *box, int port)
{
	box->server.server_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (box->server.server_sock < 0)
		return (printf("ERROR OPENING SOCKET\n"), 1);

	fcntl(box->server.server_sock, F_SETFL, O_NONBLOCK);

	box->server.client_addr.sin_family = AF_INET;
	box->server.client_addr.sin_port = htons(port);
	box->server.client_addr.sin_addr.s_addr = inet_addr(box->server.host_ip);

	box->server.addr_len = sizeof(box->server.client_addr);

	if (bind(box->server.server_sock, (struct sockaddr*)&box->server.client_addr, box->server.addr_len) < 0)
		return (printf("ERROR BINDING %s\n", strerror(errno)), 1);

	struct epoll_event ev;
	box->server.epoll_sock = epoll_create1(0);

	if (box->server.epoll_sock < 0)
		return (printf("ERROR CREATING EPOLL\n"), 1);

	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = box->server.server_sock;

	if(epoll_ctl(box->server.epoll_sock, EPOLL_CTL_ADD, box->server.server_sock, &ev))
	{
		close(box->server.epoll_sock);
		return (printf("ERROR ADDING SOCKET TO EPOLL\n"), 1);
	}
	return (0);
}

int init_client(t_box *box, int port)
{
	box->client.server_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (box->client.server_sock < 0)
		return (printf("ERROR OPENING SOCKET\n"), 1);

	fcntl(box->client.server_sock, F_SETFL, O_NONBLOCK);

	box->client.server_addr.sin_family = AF_INET;
	box->client.server_addr.sin_port = htons(port);
	box->client.server_addr.sin_addr.s_addr = inet_addr(box->client.input_ip);

	box->client.addr_len = sizeof(box->client.server_addr);

	struct epoll_event ev;
	box->client.epoll_sock = epoll_create1(0);

	if (box->client.epoll_sock < 0)
		return (printf("ERROR CREATING EPOLL\n"), 1);

	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = box->client.server_sock;

	if(epoll_ctl(box->client.epoll_sock, EPOLL_CTL_ADD, box->client.server_sock, &ev))
	{
		close(box->client.epoll_sock);
		return (printf("ERROR ADDING SOCKET TO EPOLL\n"), 1);
	}
	box->conn_state = CLIENT_LISTENING;
	return (0);
}

// int connect_to_server(t_box *box, int port)
// {
// 	box->client.connection_sock = socket(AF_INET, SOCK_STREAM, 0);
// 	if (box->client.connection_sock < 0)
// 		return (1);
// 	struct sockaddr_in serverAddress;
// 	serverAddress.sin_family = AF_INET;
// 	serverAddress.sin_port = htons(port);
// 	serverAddress.sin_addr.s_addr = inet_addr(box->client.input_ip);

// 	printf("Connecting to %s:%d\n", box->client.input_ip, port);
// 	if (connect(box->client.connection_sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
// 		return (1);
// 	return (0);
// }

// int connect_to_client(t_box *box, int port)
// {
// 	box->server.connection_sock = socket(AF_INET, SOCK_STREAM, 0);
// 	if (box->server.connection_sock < 0)
// 		return (1);
// 	struct sockaddr_in serverAddress;
// 	serverAddress.sin_family = AF_INET;
// 	serverAddress.sin_port = htons(port);
// 	serverAddress.sin_addr.s_addr = inet_addr(box->server.input_ip);

// 	printf("Connecting to %s:%d\n", box->server.input_ip, port);
// 	if (connect(box->server.connection_sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
// 		return (1);
// 	return (0);
// }

int receive_message(t_box *box, int fd, struct sockaddr_in *client_address, socklen_t *client_address_len)
{
	(void)box;
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	printf("Started receiving from: %i\n", fd);

	int n = recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr *)client_address, client_address_len);

	if (n < 0)
		return (1);
	buffer[n] = '\0';
	if (!n)
		printf("Disconnected from: %i\n", fd);
	else
		printf("Received: %s\n", buffer);
	if (box->game_state == HOSTING_GAME && box->conn_state == SERVER_LISTENING)
	{
		box->conn_state = SERVER_READY;
		printf("SENDING HELLO TO CLIENT!\n");
		send_message(box, fd, "Hello from server", &box->server.client_addr, &box->server.addr_len);
	}
	else if (box->game_state == JOINING_GAME && box->conn_state == CLIENT_LISTENING)
	{
		printf("SERVER READY\n");
		box->conn_state = CLIENT_READY;
	}
	return (0);
}

int send_message(t_box *box, int fd, char *message, struct sockaddr_in *client_address, socklen_t *client_address_len)
{
	(void)box;
	printf("Started sending: %s to fd %i\n", message, fd);
	int n = sendto(fd, message, ft_strlen(message), 0, (struct sockaddr *)client_address, *client_address_len);
	if (n < 0)
		return (printf("ERROR SENDING %s\n", strerror(errno)), 1);
	printf("Send: %s to fd %i\n", message, fd);
	return (0);
}
