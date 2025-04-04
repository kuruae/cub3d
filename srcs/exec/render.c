/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:45:38 by habouda           #+#    #+#             */
/*   Updated: 2025/04/04 20:34:00 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_ray(t_cub *cub)
{
	///le rayon commence a la position du joueur mais cast en int////
	cub->ray->map_x = (int)cub->player->pos_x;
	cub->ray->map_y = (int)cub->player->pos_y;
	// printf("Player Position: pos_x = %f, pos_y = %f\n", cub->player->pos_x, cub->player->pos_y);
	// printf("Ray Map Position: map_x = %d, map_y = %d\n", cub->ray->map_x, cub->ray->map_y);
	////DELTADIST Necessaire au calcul pour lancer les rayons je suis pas sur de ce que c par contre//
	if (cub->ray->dir_x != 0)
		cub->ray->deltadist_x = fabs(1 / cub->ray->dir_x);
	else
		cub->ray->deltadist_x = 0;
	if (cub->ray->dir_y != 0)
		cub->ray->deltadist_y = fabs(1 / cub->ray->dir_y);
	else
		cub->ray->deltadist_y = 0;
	/// On se base sur cub->player->dir pour savoir dans quel direction lancer les rayons
	find_ray_and_step_direction(cub);
	while (cub->map->map[cub->ray->map_y][cub->ray->map_x] != 49)
		apply_dda(cub);
	if (cub->ray->side == 0) // Vertical wall hit side value is changed in apply dda//
		cub->ray->wall_dist = (cub->ray->map_x - cub->player->pos_x + (1 - cub->ray->step_x) / 2) / cub->ray->dir_x;
	else // Horizontal wall hit side value is changed in apply dda
		cub->ray->wall_dist = (cub->ray->map_y - cub->player->pos_y + (1 - cub->ray->step_y) / 2) / cub->ray->dir_y;
}

void find_ray_and_step_direction(t_cub *cub)
{
	if (cub->ray->dir_x > 0)
	{
		cub->ray->sidedist_x = (cub->ray->map_x + 1.0 - cub->player->pos_x) * cub->ray->deltadist_x;
		cub->ray->step_x = 1;
	}
	else if (cub->ray->dir_x < 0)
	{
		cub->ray->sidedist_x = (cub->player->pos_x - cub->ray->map_x) * cub->ray->deltadist_x;
		cub->ray->step_x = -1;
	}
	else
	{
		cub->ray->sidedist_x = INT_MAX;
		cub->ray->step_x = 0;
	}
	if (cub->ray->dir_y > 0)
	{
		cub->ray->sidedist_y = (cub->ray->map_y + 1.0 - cub->player->pos_y) * cub->ray->deltadist_y;
		cub->ray->step_y = 1;
	}
	else if (cub->ray->dir_y < 0)
	{
		cub->ray->sidedist_y = (cub->player->pos_y - cub->ray->map_y) * cub->ray->deltadist_y;
		cub->ray->step_y = -1;
	}
	else
	{
		cub->ray->sidedist_y = INT_MAX;
		cub->ray->step_y = 0;
	}
}

void	apply_dda(t_cub *cub)
{
	//On avance dans la diredtion x ou la direction y en fonction de leur taille
	if (cub->ray->sidedist_x < cub->ray->sidedist_y)
	{
		// On avance de maniere verticale//
		// printf("step_x %d\n", cub->ray->step_x);
		cub->ray->sidedist_x += cub->ray->deltadist_x;
		// printf("map_x before increment: %d\n", cub->ray->map_x);
		cub->ray->map_x += cub->ray->step_x;
		// printf("map_x after increment: %d\n", cub->ray->map_x);
		cub->ray->side = 0;
	}
	else
	{	// On avance de maniere horizontale
		// printf("step_y %d\n", cub->ray->step_y);
		cub->ray->sidedist_y += cub->ray->deltadist_y;
		// printf("map_y before increment: %d\n", cub->ray->map_y);
		cub->ray->map_y += cub->ray->step_y;
		// printf("map_y after increment: %d\n", cub->ray->map_y);
		cub->ray->side = 1;
	}
}

void wall(t_cub *cub)
{
	////franchement pas compris je suis creve la a reregarder ////
	cub->ray->line_height = (int)(HEIGHT / cub->ray->wall_dist);
	cub->ray->draw_start = -cub->ray->line_height / 2 + HEIGHT / 2;
	if (cub->ray->draw_start < 0)
		cub->ray->draw_start = 0;
	cub->ray->draw_end = cub->ray->line_height / 2 + HEIGHT / 2;
	if (cub->ray->draw_end >= HEIGHT)
		cub->ray->draw_end = HEIGHT - 1;
	if (cub->ray->side == 0) 
		cub->ray->wall_x = cub->player->pos_y + cub->ray->wall_dist * cub->ray->dir_y;
	else 
		cub->ray->wall_x = cub->player->pos_x + cub->ray->wall_dist * cub->ray->dir_x;
	cub->ray->wall_x -= floor(cub->ray->wall_x);
}

int	start_render(t_cub *cub)
{
	int 	x;

	mlx_destroy_image(cub->mlx, cub->img->img);
	cub->img->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->img->adrr = mlx_get_data_addr(cub->img->img, &cub->img->bpp, &cub->img->line_length, &cub->img->endian);
	draw_floor_ceiling(cub);
	double cam_x;
	cub->player->plane_x = -cub->player->dir_y * 0.66;
	cub->player->plane_y = cub->player->dir_x * 0.66;
	// printf("Plane: plane_x = %f, plane_y = %f\n", cub->player->plane_x, cub->player->plane_y);
	x = -1;
	while (++x < WIDTH)
	{
		cam_x = 2 * x / (double)WIDTH -1;
		cub->ray->dir_x = cub->player->dir_x + cub->player->plane_x * cam_x; //vecteur directions//
		cub->ray->dir_y = cub->player->dir_y + cub->player->plane_y * cam_x; //vecteur directions//
		calculate_ray(cub);
		wall(cub);
		draw_wall(cub, x);
	}
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img->img, 0, 0);
	return (0);
}