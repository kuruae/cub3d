/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:44:05 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/18 17:57:06 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_err_status	validate_file_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(&file[len - EXT_LEN], EXT, 4))
		return (err_handler(MSG_INVALID_EXT, PARSING_ERROR));
	return (SUCCESS);
}

t_err_status	start_parsing(int argc, char **argv)
{
	if (argc != 2)
		return (err_handler(MSG_INVALID_ARGS, PARSING_ERROR));
	if (validate_file_extension(argv[1]) != SUCCESS)
		return (PARSING_ERROR);
	if (start_parsing_cub_file(argv[1]) != SUCCESS)
		return (PARSING_ERROR);
	return (SUCCESS);
}
