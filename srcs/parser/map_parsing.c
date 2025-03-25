/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:46:55 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/25 17:08:43 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_reader(char *line, t_map *map, int fd)
{
	int 		id;
	int			*translated_line;
	t_submap	*head;
	
	(void)map;
	head = NULL;
	id = 0;
	while(line) 
	{
		fprintf(stderr,"CURRENT LINE VALUE : %s \n", line);
		translated_line = map_translator(line);
		fprintf(stderr, "LINE VALUE AFTER TRANSLATOR\n");
		debug_print_translated_line(translated_line);
		ft_add_in_list_cub(&head, id, translated_line);
		id++;
		line = get_next_line(fd);
	}
}
