/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_translator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuru <kuru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:26:44 by emagnani          #+#    #+#             */
/*   Updated: 2025/04/10 16:34:31 by kuru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_line_length(char *line)
{
	int	i;
	int	len;
	int	column;
	int	spaces_to_add;

	len = 0;
	i = 0;
	column = 0;
	while (line[i])
	{
		if (line[i] == '\t')
		{
			spaces_to_add = 4 - (column % 4);
			len += spaces_to_add;
			column += spaces_to_add;
		}
		else
		{
			len++;
			column++;
		}
		i++;
	}
	return (len);
}

static char	*handle_tab(char *new, t_translator_vars *var)
{
	int	spaces_to_add;
	int	i;

	i = 0;
	spaces_to_add = 4 - (var->x % 4);
	while (i < spaces_to_add)
	{
		new[var->x] = '1';
		var->x++;
		i++;
	}
	var->x--;
	return (new);
}

static char	*handle_direction(char *new, t_translator_vars *var, char c)
{
	if (c == 'N')
		new[var->x] = NORTH;
	else if (c == 'W')
		new[var->x] = WEST;
	else if (c == 'E')
		new[var->x] = EAST;
	else if (c == 'S')
		new[var->x] = SOUTH;
	return (new);
}

static char	*handle_map_char(char *new, t_translator_vars *var, char c)
{
	if (c == '\t')
		new = handle_tab(new, var);
	else if (c == '0')
		new[var->x] = '0';
	else if (c == ' ' || c == '1')
		new[var->x] = '1';
	else if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		new = handle_direction(new, var, c);
	else if (c == '\n')
		return (new);
	else
	{
		free(new);
		return (NULL);
	}
	var->i++;
	var->x++;
	return (new);
}

char	*map_translator(char *line)
{
	char				*new;
	t_translator_vars	var;

	var = (t_translator_vars){0, 0};
	new = malloc(sizeof(char) * (map_line_length(line) + 1));
	while (line[var.i])
	{
		new = handle_map_char(new, &var, line[var.i]);
		if (!new || line[var.i] == '\n')
			break ;
	}
	if (new)
		new[var.x] = '\0';
	return (new);
}
