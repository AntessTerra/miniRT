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
	box->server.server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (box->server.server_sock < 0)
		return (1);
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	bind(box->server.server_sock, (struct sockaddr*)&serverAddress,
		 sizeof(serverAddress));

	listen(box->server.server_sock, SOMAXCONN);

	struct epoll_event ev;
	box->server.epoll_sock = epoll_create1(0);

	if (box->server.epoll_sock < 0)
		return (1);

	ev.events = EPOLLIN | EPOLLOUT;
	ev.data.fd = box->server.server_sock;

	if(epoll_ctl(box->server.epoll_sock, EPOLL_CTL_ADD, box->server.server_sock, &ev))
	{
		close(box->server.epoll_sock);
		return (1);
	}
	return (0);
}

int init_client(t_box *box, int port)
{
	box->client.client_listening_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (box->client.client_listening_sock < 0)
		return (1);
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	bind(box->client.client_listening_sock, (struct sockaddr*)&serverAddress,
		 sizeof(serverAddress));

	listen(box->client.client_listening_sock, SOMAXCONN);

	struct epoll_event ev;
	box->client.epoll_sock = epoll_create1(0);

	if (box->client.epoll_sock < 0)
		return (1);

	ev.events = EPOLLIN | EPOLLOUT;
	ev.data.fd = box->client.client_listening_sock;

	if(epoll_ctl(box->client.epoll_sock, EPOLL_CTL_ADD, box->client.client_listening_sock, &ev))
	{
		close(box->client.epoll_sock);
		return (1);
	}
	return (0);
}

int connect_to_server(t_box *box, int port)
{
	box->client.connection_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (box->client.connection_sock < 0)
		return (1);
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = inet_addr(box->client.input_ip);

	printf("Connecting to %s:%d\n", box->client.input_ip, port);
	if (connect(box->client.connection_sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
		return (1);
	return (0);
}

int connect_to_client(t_box *box, int port)
{
	box->server.connection_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (box->server.connection_sock < 0)
		return (1);
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = inet_addr(box->server.input_ip);

	printf("Connecting to %s:%d\n", box->server.input_ip, port);
	if (connect(box->server.connection_sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
		return (1);
	return (0);
}

int receive_message(t_box *box, int fd)
{
	(void)box;
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	printf("Started receiving from: %i\n", fd);

	int n = recv(fd, buffer, sizeof(buffer), 0);

	if (n < 0)
		return (1);
	buffer[n] = '\0';
	if (!n)
		printf("Disconnected from: %i\n", fd);
	else
		printf("Received: %s\n", buffer);
	return (0);
}

int send_message(t_box *box, int fd, char *message)
{
	(void)box;
	printf("Started sending: %s to fd %i\n", message, fd);
	int n = send(fd, message, ft_strlen(message), 0);
	if (n < 0)
		return (1);
	printf("Send: %s to fd %i\n", message, fd);
	return (0);
}
