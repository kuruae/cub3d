/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:15:09 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/29 18:49:50 by emagnani         ###   ########.fr       */
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
	ERR_POSITION,
	ERR_COLOR
}	t_err_status;

// RGB color
typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}		t_rgb;

typedef struct s_submap
{
	int				*line;
	int				**player_pos;
	int				id;
	struct s_submap	*next;
	struct s_submap	*prev;
}	t_submap;

// Map data
typedef struct s_map
{
	char		**map;
	bool	has_pos;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	t_rgb	floor_color;
	t_rgb	ceiling_color;
}	t_map;

#endif