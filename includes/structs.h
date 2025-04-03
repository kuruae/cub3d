/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuru <kuru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:15:09 by emagnani          #+#    #+#             */
/*   Updated: 2025/04/03 09:34:54 by kuru             ###   ########.fr       */
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
	char	*adrr;
	int		endian;
	int		bpp;
	int		line_length;
}	t_img;

typedef struct s_ray
{
    double  camera_x;        // X position of the ray in the camera space
    double  dir_x;           // Direction of the ray in the X axis
    double  dir_y;           // Direction of the ray in the Y axis
    int     map_x;           // X grid coordinate where the ray is
    int     map_y;           // Y grid coordinate where the ray is
    int     step_x;          // =1 if we go in positive direction otherwise -1
    int     step_y;          // same as above
    double  sidedist_x;      // Distance to the next X grid line the ray will cross
    double  sidedist_y;      // Distance to the next Y grid line the ray will cross
    double  deltadist_x;     // How much the ray moves in the X direction per step
    double  deltadist_y;     // How much the ray moves in the Y direction per step
    double  wall_dist;       // The distance from the player to the wall the ray hit
    double  wall_x;          // OU EST CE QUE LE MUR A PRIS UN RAYON A CALCULER APRES AVOIR CHOPPER WALL
    int     side;            // Which side of the wall the ray hit (0 = horizontal, 1 = vertical)
    int     line_height;     // Height of the line to be drawn on the screen for this ray
    int     draw_start;      // Y-coordinate where the line starts being drawn on the screen
    int     draw_end;        // Y-coordinate where the line ends being drawn on the screen
}   t_ray;

typedef struct s_player
{
	double pos_x; ///POSITION DU JOUEUR///
	double pos_y;///POSITION DU JOUEUR///
	double dir_x; //VECTEUR DIRECTION X (EN GROS LA OU LE JOUEUR REGARDE)///
	double dir_y; //VECTEUR DIRECTION Y///
	double plane_x; // CAMERA //
	double plane_y; // CAMERA //
} 	t_player;

/*
** les struct pour la taille des textures
** doivent etre free a la fin du programme
*/
typedef struct s_xpm_size
{
	int		width;
	int		height;
}	t_xpm_size;

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
	t_player	*player;
	t_ray		*ray;
	t_xpm_size	*no_size;
	t_xpm_size	*we_size;
	t_xpm_size	*so_size;
	t_xpm_size	*ea_size;
}	t_cub;


#endif