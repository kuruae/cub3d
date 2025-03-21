/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:15:09 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/19 17:03:49 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"

// error table
typedef enum e_err_status
{
	MALLOC_FAILURE = -1,
	SUCCESS = 0,
	ERR_MAP_PATH,
	ERR_TEXTURE_PATH,
	ERR_COLOR
}	t_err_status;

// RGB color
typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

// Map data
typedef struct s_map
{
	char	*NO_texture;
	char	*SO_texture;
	char	*WE_texture;
	char	*EA_texture;
	t_rgb	floor_color;
	t_rgb	ceiling_color;
}	t_map;

#endif