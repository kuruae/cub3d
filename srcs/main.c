/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:13:33 by emagnani          #+#    #+#             */
/*   Updated: 2025/04/03 01:21:48 by habouda          ###   ########.fr       */
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
	printf("Player Position: pos_x = %f, pos_y = %f\n", cub->player->pos_x, cub->player->pos_y);
	printf("Ray Map Position: map_x = %d, map_y = %d\n", cub->ray->map_x, cub->ray->map_y);
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
	else
	{
		cub->ray->sidedist_x = INT_MAX;
		cub->ray->step_x = 0;
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

		cub->ray->sidedist_x += cub->ray->deltadist_x;
		cub->ray->map_x += cub->ray->step_x;
		cub->ray->side = 0;
	}
	else
	{	// On avance de maniere horizontale
		printf("step_y %d\n", cub->ray->step_y);
		cub->ray->sidedist_y += cub->ray->deltadist_y;
		printf("map_y before increment: %d\n", cub->ray->map_y);
		cub->ray->map_y += cub->ray->step_y;
		printf("map_y after increment: %d\n", cub->ray->map_y);
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
	if (cub->ray->side == 1) 
		cub->ray->wall_x = cub->player->pos_x + cub->ray->wall_dist * cub->ray->dir_x;
		
}

void draw_wall(t_cub *cub, int x)
{
    int y_axis;
    int texture_x;
    int texture_y;
    int color;
    int texture_width = 64;  // Using 64x64 textures
    int texture_height = 64;
    int bytes_per_pixel = cub->img->bpp / 8;
    
    // Calculate texture_x with bounds checking
    texture_x = (int)(cub->ray->wall_x * texture_width) % texture_width;
    if (texture_x < 0) texture_x += texture_width;
    
    y_axis = cub->ray->draw_start;
    while (y_axis < cub->ray->draw_end)
    {
        // Calculate texture_y with bounds checking
        texture_y = (int)((y_axis - cub->ray->draw_start) * texture_height / cub->ray->line_height);
        if (texture_y < 0) texture_y = 0;
        if (texture_y >= texture_height) texture_y = texture_height - 1;
        
        // Calculate texture offset using texture width, not line_length
        int offset = (texture_y * texture_width + texture_x) * bytes_per_pixel;
        
        // Add safety check
        int max_offset = texture_width * texture_height * bytes_per_pixel - bytes_per_pixel;
        if (offset < 0 || offset > max_offset)
        {
            // Use solid colors as fallback if offset out of bounds
            if (cub->ray->side == 0)
                color = (cub->ray->step_x > 0) ? 0xFF0000 : 0x00FF00; // Red or Green
            else  
                color = (cub->ray->step_y > 0) ? 0x0000FF : 0xFFFF00; // Blue or Yellow
        }
        else
        {
            // Access texture data with proper offset
            if (cub->ray->side == 0)
            {
                if (cub->ray->step_x > 0)
                    color = *(unsigned int *)(cub->img->north + offset);
                else
                    color = *(unsigned int *)(cub->img->south + offset);
            }
            else
            {
                if (cub->ray->step_y > 0)
                    color = *(unsigned int *)(cub->img->east + offset);
                else
                    color = *(unsigned int *)(cub->img->west + offset);
            }
        }
        
        // Draw to screen with bounds checking
        if (y_axis >= 0 && y_axis < HEIGHT && x >= 0 && x < WIDHT)
            *(unsigned int *)(cub->img->adrr + (y_axis * cub->img->line_length + x * bytes_per_pixel)) = color;
        
        y_axis++;
    }
}



int	start_render(t_cub *cub)
{
	int 	x;

	double cam_x;
	cub->player->plane_x = -cub->player->dir_x * 0.6;
	cub->player->plane_y = cub->player->dir_y * 0.6;
	x = -1;
	while (++x < WIDHT)
	{
		cam_x = 2 * x / (double)WIDHT -1;
		cub->ray->dir_x = cub->player->dir_x + cub->player->plane_x * cam_x; //vecteur directions//
		cub->ray->dir_y = cub->player->dir_y + cub->player->plane_y * cam_x; //vecteur directions//
		calculate_ray(cub);
		wall(cub);
		draw_wall(cub, x);
	}
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img->img, 0, 0);
	return (0);
}

int start_display(t_cub *cub)
{
    if (mlx_loop_hook(cub->mlx, start_render, cub) == -1)
    {
        printf("mlx_loop_hook failed\n");
        return (EXIT_FAILURE);
    }
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
	if (cub.mlx_win == NULL)
	{
		printf("Error: mlx_new_window failed\n");
		return (EXIT_FAILURE);
	}
	init_mlx(&map, &cub);
	cub.img->img = mlx_new_image(cub.mlx, WIDHT, HEIGHT);
	if (!cub.img->img)
	{	
    	printf("Error: mlx_new_image failed\n");
	    return (EXIT_FAILURE);
	}
	cub.img->adrr = mlx_get_data_addr(cub.img->img, &cub.img->bpp, &cub.img->line_length, &cub.img->endian ); /// PAS ENCORE PROTGERER POUR CLARTE ET COMPREHENSION ///
	start_display(&cub);
	return (EXIT_SUCCESS);
}
