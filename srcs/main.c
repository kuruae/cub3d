/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:13:33 by emagnani          #+#    #+#             */
/*   Updated: 2025/04/08 17:45:50 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_close(t_cub *cub)
{
	free(cub->ray);
	free(cub->player);
	free(cub->map->no_texture);
	free(cub->map->ea_texture);
	free(cub->map->so_texture);
	free(cub->map->we_texture);
	free(cub->no_size);
	free(cub->we_size);
	free(cub->so_size);
	free(cub->ea_size);
	free(cub->keys);
	mlx_destroy_image(cub->mlx, cub->no_xpm);
	mlx_destroy_image(cub->mlx, cub->so_xpm);
	mlx_destroy_image(cub->mlx, cub->we_xpm);
	mlx_destroy_image(cub->mlx, cub->ea_xpm);
	ft_free_str_array(&cub->map->map);
	if (cub->img->img)
	{
		mlx_destroy_image(cub->mlx, cub->img->img);
		cub->img->img = NULL;
	}
	if (cub->mlx_win)
	{
		mlx_destroy_window(cub->mlx, cub->mlx_win);
		cub->mlx_win = NULL;
	}
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
		cub->mlx = NULL;
	}
	exit(EXIT_SUCCESS);
	return (0);
}

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
	mlx_hook(cub->mlx_win, 17, 0, handle_close, cub);
	mlx_loop(cub->mlx);
	return (EXIT_SUCCESS);
}

static void	test_free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->map)
	{
		printf("Freeing map...\n");
		while (map->map[i])
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
	}
	if (map->no_texture)
		free(map->no_texture);
	if (map->so_texture)
		free(map->so_texture);
	if (map->we_texture)
		free(map->we_texture);
	if (map->ea_texture)
		free(map->ea_texture);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_img	img;
	t_cub	cub;

	if (start_parsing(argc, argv, &map) != SUCCESS)
	{
		test_free_map(&map);
		return (EXIT_FAILURE);
	}
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
	cub.img->img = mlx_new_image(cub.mlx, WIDTH, HEIGHT);
	if (!cub.img->img)
	{
		printf("Error: mlx_new_image failed\n");
		return (EXIT_FAILURE);
	}
	cub.img->adrr = mlx_get_data_addr(cub.img->img, &cub.img->bpp,
			&cub.img->line_length, &cub.img->endian);
		/// PAS ENCORE PROTGERER POUR CLARTE ET COMPREHENSION ///
	start_display(&cub);
	return (EXIT_SUCCESS);
}
