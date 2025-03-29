/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_translator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:26:44 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/29 18:17:18 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_line_length(char *line)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	len = ft_strlen(line);
	while (line[i])
	{
		if (line[i] == '\t')
			len = len + 3;
		i++;
	}
	return (len);
}

char	*map_translator(char *line)
{
	char	*new;
	int		i;
	int		x;

	i = 0;
	x = 0;
	new = malloc(sizeof(int) * (map_line_length(line) + 1));
	while (line[i])
	{
		if (line[i] == '\t')
		{
			new[x++] = VOID;
			new[x++] = VOID;
			new[x++] = VOID;
			new[x] = VOID;
		}
		else if (line[i] == '0')
			new[x] = '0';
		else if (line[i] == ' ')
			new[x] = VOID;
		else if (line[i] == '1')
			new[x] = '1';
		else if (line[i] == 'N')
			new[x] = NORTH;
		else if (line[i] == 'W')
			new[x] = WEST;
		else if (line[i] == 'E')
			new[x] = EAST;
		else if (line[i] == 'S')
			new[x] = SOUTH;
		else if (line[i] == '\n')
			break ;
		else
			new[x] = 'x';
		i++;
		x++;
	}
	new[x] = '\0';
	return (new);
}
