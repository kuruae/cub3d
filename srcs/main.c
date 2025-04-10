/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuru <kuru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:13:33 by emagnani          #+#    #+#             */
/*   Updated: 2025/04/10 20:41:15 by kuru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	start_display(t_cub *cub)
{
	init_keys(cub);
	if (mlx_loop_hook(cub->mlx, &start_render, cub) == -1)
	{
		printf("mlx_loop_hook failed\n");
		return (EXIT_FAILURE);
	}
	mlx_hook(cub->mlx_win, KeyPress, KeyPressMask, &press, cub);
	mlx_hook(cub->mlx_win, KeyRelease, KeyRelease, &release, cub);
	mlx_hook(cub->mlx_win, MotionNotify,
		PointerMotionMask, &mouse_function, cub);
	mlx_hook(cub->mlx_win, 17, 0, handle_close, cub);
	mlx_loop(cub->mlx);
	return (EXIT_SUCCESS);
}

int	start_render(t_cub *cub)
{
	int		x;
	double	cam_x;
	int		color;

	compute_t_time_values(cub);
	color = rgb_to_int(cub->map->ceiling_color);
	mouvement(cub);
	draw_floor_ceiling(cub, color);
	cub->player->plane_x = -cub->player->dir_y * 0.66;
	cub->player->plane_y = cub->player->dir_x * 0.66;
	x = -1;
	while (++x < WIDTH)
	{
		cam_x = 2 * x / (double)WIDTH - 1;
		cub->ray->dir_x = cub->player->dir_x + cub->player->plane_x * cam_x;
		cub->ray->dir_y = cub->player->dir_y + cub->player->plane_y * cam_x;
		calculate_ray(cub);
		wall(cub);
		draw_wall(cub, x);
	}
	mlx_put_image_to_window(cub->mlx, cub->mlx_win, cub->img->img, 0, 0);
	draw_minimap(cub, cub->map);
	return (0);
}

void	init_mini_map(t_cub *cub, t_map *map)
{
	t_minimap	*mini;

	mini = malloc(sizeof(t_minimap) * 1);
	mini->map_height = get_map_height(map->map);
	mini->map_width = get_map_width(map->map, mini->map_height);
	mini->height = mini->map_height * 8;
	mini->width = mini->map_width * 8;
	mini->img = mlx_new_image(cub->mlx, mini->width, mini->height);
	if (!mini->img)
		return ;
	mini->addr = mlx_get_data_addr(mini->img, &mini->bits_per_pixel,
			&mini->line_length, &mini->endian);
	cub->mini = mini;
}

static int	main_mlx(t_map *map, t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->mlx_win = mlx_new_window(cub->mlx, 1280, 720, "cub3d");
	if (cub->mlx_win == NULL)
	{
		ft_putstr_fd("Error: mlx_new_window failed\n", 2);
		return (EXIT_FAILURE);
	}
	init_mlx(map, cub);
	cub->img->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img->img)
	{
		ft_putstr_fd("Error: mlx_new_image failed\n", 2);
		return (EXIT_FAILURE);
	}
	cub->img->adrr = mlx_get_data_addr(cub->img->img, &cub->img->bpp,
			&cub->img->line_length, &cub->img->endian);
	if (!cub->img->adrr)
	{
		ft_putstr_fd("Error: mlx_get_data_addr failed\n", 2);
		return (EXIT_FAILURE);
	}
	init_mini_map(cub, map);
	start_display(cub);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_img	img;
	t_cub	cub;

	if (start_parsing(argc, argv, &map) != SUCCESS)
	{
		free_map(&map);
		return (EXIT_FAILURE);
	}
	cub.map = &map;
	get_player_pos(&cub);
	if (init_struct_cub(&cub, &img) != SUCCESS)
	{
		free_map(&map);
		free(cub.player);
		return (EXIT_FAILURE);
	}
	return (main_mlx(&map, &cub));
}
