/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:46:55 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/18 17:56:01 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_err_status	validate_file_path(char *file, char *msg)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (err_handler(msg, PARSING_ERROR));
	}
	return (SUCCESS);
}

t_err_status	start_parsing_cub_file(char *file)
{
	// t_map	map;

	if (validate_file_path(file, MSG_INVALID_MAP_PATH) != SUCCESS)
		return (EXIT_FAILURE);

	debug_print_file(file);

	// parse_pre_map_data(file, &map);
	
	return (SUCCESS);
}