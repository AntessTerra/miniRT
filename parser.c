/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:29:34 by jbartosi          #+#    #+#             */
/*   Updated: 2023/07/13 14:37:10 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parser(t_box *box, int fd)
{
	char	*line;
	int		i;

	box->map = malloc(100 * sizeof(char *));
	i = 0;
	while (i < 100)
		box->map[i++] = malloc(100);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		ft_strlcpy(box->map[i++], line, ft_strlen(line) + 1);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}
