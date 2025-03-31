/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:44:05 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/31 18:44:51 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_err_status	validate_file_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(&file[len - EXT_LEN], EXT, EXT_LEN))
		return (err_handler(MSG_INVALID_EXT, ERR_MAP_PATH));
	return (SUCCESS);
}

t_err_status	start_parsing(int argc, char **argv)
{
	if (argc != 2)
		return (err_handler(MSG_INVALID_ARGS, ERR_MAP_PATH));
	if (validate_file_extension(argv[1]) != SUCCESS)
		return (ERR_MAP_PATH);
	if (start_parsing_cub_file(argv[1]) != SUCCESS)
	{
		printf("error encoutered in parsing cub file\n");
		return (ERR_MAP_PATH);
	}
	return (SUCCESS);
}
