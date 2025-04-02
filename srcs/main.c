/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:13:33 by emagnani          #+#    #+#             */
/*   Updated: 2025/04/02 22:16:38 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_close(void *param)
{
	(void)param;
	exit(EXIT_SUCCESS);
	return (0);
}

void	calculate_ray(t_cub *cub)
{
	///le rayon commence a la position du joueur mais cast en int////
	cub->ray->map_x = (int)cub->player->pos_x;
	cub->ray->map_y = (int)cub->player->pos_y;
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
	while (1)
	{
		apply_dda(cub);
		if (cub->map->map[cub->ray->map_y][cub->ray->map_x] == 1)
			break;
	}
	//// distance du mur///
	if (cub->ray->side == 0) // Vertical wall hit side value is changed in apply dda//
		cub->ray->wall_dist = (cub->ray->map_x - cub->player->pos_x + (1 - cub->ray->step_x) / 2) / cub->ray->dir_x;
	else // Horizontal wall hit side value is changed in apply dda
		cub->ray->wall_dist = (cub->ray->map_y - cub->player->pos_y + (1 - cub->ray->step_y) / 2) / cub->ray->dir_y;
}

void	find_ray_and_step_direction(t_cub *cub)
{
	if (cub->player->dir_x > 0)
	{
		cub->ray->sidedist_x = (cub->ray->map_x + 1.0 - cub->player->pos_x) * cub->ray->deltadist_x;
		cub->ray->step_x = 1;
	}
	else if (cub->player->dir_x < 0)
	{
		cub->ray->sidedist_x = (cub->player->pos_x - cub->ray->map_x) * cub->ray->deltadist_x;
		cub->ray->step_x = -1;
	}
	if (cub->player->dir_y > 0)
	{
		cub->ray->sidedist_y = (cub->ray->map_y + 1.0 - cub->player->pos_y) * cub->ray->deltadist_y;
		cub->ray->step_y = 1;
	}
	else if (cub->player->dir_y < 0)
	{
		cub->ray->sidedist_y = (cub->player->pos_y - cub->ray->map_y) * cub->ray->deltadist_y;
		cub->ray->step_y = -1;
	}
}


void	apply_dda(t_cub *cub)
{
	//On avance dans la diredtion x ou la direction y en fonction de leur taille
	if (cub->ray->sidedist_x < cub->ray->sidedist_y)
	{
		// On avance de maniere verticale//
		cub->ray->sidedist_x += cub->ray->deltadist_x;
		cub->ray->map_x += cub->ray->step_x;
		cub->ray->side = 0;
	}
	else
	{
		// On avance de maniere horizontale
		cub->ray->sidedist_y += cub->ray->deltadist_y;
		cub->ray->map_y += cub->ray->step_y;
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

}

int	start_render(t_cub *cub)
{
	int 	x;

	double cam_x;
	cub->player->plane_x = cub->player->dir_x;
	cub->player->plane_y = cub->player->dir_y;
	x = -1;
	while (++x < WIDHT)
	{
		cam_x = 2 * x / (double)WIDHT -1;
		cub->ray->dir_x = cub->player->dir_x + cub->player->plane_x * cam_x; //vecteur directions//
		cub->ray->dir_y = cub->player->dir_y + cub->player->plane_y * cam_x; //vecteur directions//
		calculate_ray(cub);
		wall(cub);
	}
	return (0);
}

int start_display(t_cub *cub)
{
	if (!cub)
		return (EXIT_FAILURE);
	mlx_loop_hook(cub->mlx, start_render, cub);
	mlx_hook(cub->mlx_win, 17, 0, handle_close, NULL);
	mlx_loop(cub->mlx);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_img 	img;
	t_cub	cub;

	if (start_parsing(argc, argv, &map) != SUCCESS)
		return (EXIT_FAILURE);
	cub.map = &map;
	get_player_pos(&cub);
	init_struct(&cub, &img);
	cub.mlx = mlx_init();
	cub.mlx_win = mlx_new_window(cub.mlx, 1280, 720, "cub3d");
	init_mlx(&map, &cub);
	cub.img->img = mlx_new_image(cub.mlx, WIDHT, HEIGHT); /// A PROTEGER ////
	cub.img->adrr = mlx_get_data_addr(cub.img->img, &cub.img->bpp, &cub.img->line_length, &cub.img->endian ); /// PAS ENCORE PROTGERER POUR CLARTE ET COMPREHENSION ///
	start_display(&cub);
	return (EXIT_SUCCESS);
}
