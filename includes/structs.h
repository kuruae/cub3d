/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:15:09 by emagnani          #+#    #+#             */
/*   Updated: 2025/04/02 17:06:11 by habouda          ###   ########.fr       */
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
	ERR_COLOR,
	ERR_VALUES
}	t_err_status;

// RGB color
typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}		t_rgb;


// Map data
typedef struct s_map
{
	char	**map;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	t_rgb	floor_color;
	t_rgb	ceiling_color;
}	t_map;


typedef struct	s_img
{
	void	*img;
	void	*north;
	void	*south;
	void	*east;
	void	*west;
	int		*adrr;
	int		endian;
	int		bpp;
	int		line_length;
}	t_img;
typedef struct s_cub
{
	void		*mlx_win;
	void		*mlx;
	void		*no_xpm;
	void		*we_xpm;
	void		*so_xpm;
	void		*ea_xpm;
	t_map		*map;
	t_img		*img;
}	t_cub;

#endif