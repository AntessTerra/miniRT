/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:29:34 by jbartosi          #+#    #+#             */
/*   Updated: 2023/07/27 16:19:31 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parser(t_box *box, int fd)
{
	char	*line;
	int		i;
	int		s;

	box->map = malloc(100 * sizeof(char *));
	i = 0;
	while (i < 100)
		box->map[i++] = malloc(100);
	box->sprites = malloc(100 * sizeof(t_sprite));
	i = 0;
	while (i < 100)
	{
		box->sprites[i].x = 0;
		box->sprites[i].y = 0;
		box->sprites[i++].texture = 0;
	}
	line = get_next_line(fd);
	i = 0;
	while (line[0] != '\n')
	{
		ft_strlcpy(box->map[i++], line, ft_strlen(line) + 1);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		s = 0;
		box->sprites[i].x = atof(line);
		while (line[s] != ',' && line[s] != '\n')
			s++;
		s++;
		box->sprites[i].y = atof(line + s);
		while (line[s] != ',' && line[s] != '\n')
			s++;
		s++;
		box->sprites[i].texture = atof(line + s);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
}
