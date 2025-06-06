/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuru <kuru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:15:09 by emagnani          #+#    #+#             */
/*   Updated: 2025/04/11 23:09:43 by kuru             ###   ########.fr       */
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
	ERR_INVALID_MAP,
	ERR_TEXTURE_PATH,
	ERR_POSITION,
	ERR_COLOR,
	ERR_VALUES
}				t_err_status;

// RGB color
typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

typedef struct s_draw_wall
{
	int			y_axis;
	int			texture_x;
	int			texture_y;
	int			color;
	int			texture_width;
	int			texture_height;
	char		*texture_data;
	double		wall_x;
	double		step;
	double		tex_pos;
	int			offset;
}				t_draw_wall;

typedef struct s_translator_vars
{
	int			i;
	int			x;
}				t_translator_vars;

typedef struct s_fps
{
	int			frame_count;
	double		elapsed_time;
	double		fps;
}	t_fps;

// Map data
typedef struct s_map
{
	char		**map;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	t_rgb		floor_color;
	t_rgb		ceiling_color;
}				t_map;

typedef struct s_minimap
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
	int			map_height;
	int			map_width;
}				t_minimap;
typedef struct s_img
{
	void		*img;
	void		*north;
	void		*south;
	void		*east;
	void		*west;
	char		*adrr;
	int			endian;
	int			bpp;
	int			line_length;
}				t_img;

typedef struct s_ray
{
	double		camera_x;
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	double		wall_dist;
	double		wall_x;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_ray;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

/*
** les struct pour la taille des textures
** doivent etre free a la fin du programme
*/
typedef struct s_xpm_size
{
	int			width;
	int			height;
}				t_xpm_size;

typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			m;
	int			left;
	int			right;
}				t_keys;

typedef struct s_time
{
	double		delta_time;
	double		last_time;
	double		curr_time;
}				t_time;

typedef struct s_cub
{
	void		*mlx_win;
	void		*mlx;
	void		*no_xpm;
	void		*we_xpm;
	void		*so_xpm;
	void		*ea_xpm;
	t_time		time;
	t_map		*map;
	t_img		*img;
	t_player	*player;
	t_ray		*ray;
	t_keys		*keys;
	t_xpm_size	*no_size;
	t_xpm_size	*we_size;
	t_xpm_size	*so_size;
	t_xpm_size	*ea_size;
	t_minimap	*mini;
}				t_cub;

#endif