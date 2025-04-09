/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:14:10 by emagnani          #+#    #+#             */
/*   Updated: 2025/04/09 17:52:18 by habouda          ###   ########.fr       */
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

// Window size 
# define WIDTH 1280
# define HEIGHT 720

// Game speeds
# define MOVE_SPEED 0.05
# define ROTATE_SPEED 0.025

// PI
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

// Helpers 
t_err_status	err_handler(char *err_message, t_err_status status);
bool			ft_isdigit_whitespaces(char *str);
void			get_player_pos(t_cub *cub);
int				rgb_to_int(t_rgb color);
int				is_close_to_wall(t_cub *cub, double x, double y);

// Init MLX
int				init_struct_cub(t_cub *cub, t_img *img);
void			init_mlx(t_map *map, t_cub *cub);

//display exec///
int 			mouvement(t_cub *cub);
void			calculate_ray(t_cub *cub);
void			find_ray_and_step_direction(t_cub *cub);
void			apply_dda(t_cub *cub);
void 			wall(t_cub *cub);
int				start_render(t_cub *cub);
int 			start_display(t_cub *cub);

// Hooks
void			init_keys(t_cub *cub);
int				handle_close(t_cub *cub);
int				release(int keysym, t_cub *cub);
int				press(int keysym, t_cub *cub);

///draw///
void			draw_floor_ceiling(t_cub *cub, int color);
void 			draw_wall(t_cub *cub, int x);
void	select_north_south_texture_dimensions(t_cub *cub, int *width, int *height,
	char **texture_data);
void	select_east_west_texture_dimensions(t_cub *cub, int *width, int *height,
		char **texture_data);

// rotate///
void			rotate_right(t_cub *cub, double rotation_speed);
void			rotate_left(t_cub *cub, double rotation_speed);
#endif