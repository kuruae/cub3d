/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:46:55 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/29 19:01:50 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_reader(char *line, t_map *map, int fd)
{
	int			i;
	int 		fd2;
	char		**patricia;
	char		*translated_line;

	i = 0;
	fd2 = open("prout", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (line)
	{
		translated_line = map_translator(line);
		i++;
		ft_putstr_fd(translated_line, fd2);
		ft_putstr_fd("\n", fd2);
		line = get_next_line(fd);
	}
	patricia = malloc(sizeof(char*) * (i + 1));
	i = 0;
	close(fd2);
	fd2 = open("prout", O_RDONLY);
	line = get_next_line(fd2);
	while (line)
	{
		trim_newline(line);
		patricia[i] = ft_strdup(line);
		line = get_next_line(fd2);
		i++;
	}
	patricia[i] = NULL;
	i= 0;
	while(patricia[i]!=NULL)
	{
		printf("%s\n", patricia[i]);
		i++;
	}
	map->map = patricia;
	close(fd2);
}
