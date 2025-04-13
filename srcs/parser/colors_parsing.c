/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:21:28 by emagnani          #+#    #+#             */
/*   Updated: 2025/04/13 16:54:38 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_arrays(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	check_rgb_values(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit_whitespaces(str[i]) == false)
			return (EXIT_FAILURE);
		if (ft_atoi(str[i]) > 255 || ft_atoi(str[i]) < 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static t_err_status	process_colors(const char *line, t_rgb *colors)
{
	char	**splitted_rgb;

	while (ft_isspace(*line))
		line++;
	splitted_rgb = ft_split(line, ',');
	if (!splitted_rgb)
		return (MALLOC_FAILURE);
	if (check_rgb_values(splitted_rgb) == EXIT_FAILURE
		|| count_arrays(splitted_rgb) != 3)
	{
		ft_free_str_array(&splitted_rgb);
		return (ERR_COLOR);
	}
	colors->r = ft_atoi(splitted_rgb[0]);
	colors->g = ft_atoi(splitted_rgb[1]);
	colors->b = ft_atoi(splitted_rgb[2]);
	ft_free_str_array(&splitted_rgb);
	return (SUCCESS);
}

t_err_status	parse_colors(char *line, t_map *map)
{
	t_err_status	status;

	status = SUCCESS;
	if (line[0] == 'C')
		status = process_colors(&line[1], &map->ceiling_color);
	if (line[0] == 'F')
		status = process_colors(&line[1], &map->floor_color);
	return (status);
}
