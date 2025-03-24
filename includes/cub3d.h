/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:14:10 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/24 18:51:13 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>

# include "mlx.h"
# include "libft.h"
# include "structs.h"
# include "parsing.h"

# define EXT ".cub"
# define EXT_LEN 4

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

// Helpers 
t_err_status	err_handler(char *err_message, t_err_status status);
bool			ft_isdigit_whitespaces(char *str);


#endif