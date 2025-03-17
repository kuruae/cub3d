/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:44:05 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/17 18:01:02 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_args(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(&file[len - 4], ".cub", 4))
		return (err_handler(ERR_INVALID_EXT, true));
	return (EXIT_SUCCESS);
}

int	start_parse(int argc, char **argv)
{
	if (argc != 2)
		return (err_handler(ERR_INVALID_ARGS, true));
	validate_args(argv[1]);
	// parse_file(argv[1]);
	return (EXIT_SUCCESS);
}
