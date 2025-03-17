/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:14:10 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/17 17:55:52 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <math.h>

// Error handling
# define ERR_INVALID_ARGS "Invalid number of arguments\n"
# define ERR_INVALID_EXT "Invalid file extension\n"

// Helpers 
int	err_handler(char *err_message, bool exit_program);

// Parsing
int	validate_args(char *file);
int	start_parse(int argc, char **argv);

#endif