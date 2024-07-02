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
	box->multiplayer.host_ip = inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr);
	return (0);
}

int init_server(t_box *box, int port)
{
	box->multiplayer.server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (box->multiplayer.server_sock < 0)
		return (1);
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	bind(box->multiplayer.server_sock, (struct sockaddr*)&serverAddress,
		 sizeof(serverAddress));

	listen(box->multiplayer.server_sock, SOMAXCONN);

	struct epoll_event ev;
	box->multiplayer.epoll_sock = epoll_create1(0);

	if (box->multiplayer.epoll_sock < 0)
		return (1);

	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = box->multiplayer.server_sock;

	if(epoll_ctl(box->multiplayer.epoll_sock, EPOLL_CTL_ADD, box->multiplayer.server_sock, &ev))
	{
		close(box->multiplayer.epoll_sock);
		return (1);
	}
	return (0);
}

int connect_to_server(t_box *box, int port)
{
	box->multiplayer.connection_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (box->multiplayer.connection_sock < 0)
		return (1);
	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = inet_addr(box->multiplayer.input_ip);

	printf("Connecting to %s:%d\n", box->multiplayer.input_ip, port);
	if (connect(box->multiplayer.connection_sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
		return (1);
	return (0);
}

int receive_message(t_box *box, int fd)
{
	(void)box;
	char buffer[1024];
	int n = read(fd, buffer, 1024);
	if (n < 0)
		return (1);
	buffer[n] = '\0';
	printf("Received: %s\n", buffer);
	return (0);
}

int send_message(t_box *box, int fd, char *message)
{
	(void)box;
	int n = write(fd, message, strlen(message));
	if (n < 0)
		return (1);
	return (0);
}
