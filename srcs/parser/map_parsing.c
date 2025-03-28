/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:46:55 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/28 20:09:10 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	**list_to_int(t_submap *head, int size)
{
	t_submap	*temp;
	int			**full_map;
	int			i;

	temp = head;
	i = 0;
	full_map = malloc(sizeof(int *) * size + 1);
	if (!full_map)
		return (NULL);
	while (temp)
	{
		full_map[i] = temp->line;
		temp = temp->next;
		i++;
	}
	full_map[i] = NULL;
	return (full_map);
}

void	map_reader(char *line, t_map *map, int fd)
{
	int			i;
	int			*translated_line;
	t_submap	*head;

	(void)map;
	head = NULL;
	i = 0;
	while (line)
	{
		translated_line = map_translator(line);
		ft_add_in_list_cub(&head, i, translated_line);
		i++;
		line = get_next_line(fd);
	}
	map->map = list_to_int(head, i);
	debug_print_full_map(map->map);
}
