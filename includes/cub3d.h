/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuru <kuru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:14:10 by emagnani          #+#    #+#             */
/*   Updated: 2025/04/11 22:52:36 by kuru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include <sys/time.h>

# include "mlx.h"
# include "libft.h"
# include "structs.h"
# include "parsing.h"

// Window size 
# define WIDTH 1280
# define HEIGHT 720

// Game speeds
# define MOVE_SPEED 5
# define ROTATE_SPEED 5
# define MOUSE_SPEED 3.5

# define MIN_DELTA_TIME 0.001
# define MAX_DELTA_TIME 0.016

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
void			compute_t_time_values(t_cub *cub);

// Init MLX
int				init_struct_cub(t_cub *cub, t_img *img);
void			init_mlx(t_map *map, t_cub *cub);

//display exec///
double			calculate_move_speed(t_cub *cub);
int				mouvement(t_cub *cub);
void			calculate_ray(t_cub *cub);
void			apply_dda(t_cub *cub);
void			wall(t_cub *cub);
int				start_render(t_cub *cub);
int				start_display(t_cub *cub);
void			update_fps_counter(t_cub *cub);

// Hooks
void			init_keys(t_cub *cub);
int				handle_close(t_cub *cub);
int				release(int keysym, t_cub *cub);
int				press(int keysym, t_cub *cub);

///draw///

void			draw_floor_ceiling(t_cub *cub, int color);
void			draw_wall(t_cub *cub, int x);
void			select_north_south_texture_dimensions(t_cub *cub, int *width,
					int *height, char **texture_data);
void			select_east_west_texture_dimensions(t_cub *cub, int *width,
					int *height, char **texture_data);

// rotate///
void			rotate_right(t_cub *cub, double rotation_speed);
void			rotate_left(t_cub *cub, double rotation_speed);
int				mouse_function(int x, int y, void *arg);

///minimap de miniville
void			mini_map_pixel_put(t_minimap *mini, int x, int y, int color);
void			draw_square(t_minimap *mini);
void			put_the_walls(t_minimap *mini, int draw_x, int draw_y);
#endif