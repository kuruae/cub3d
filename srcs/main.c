/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:13:33 by emagnani          #+#    #+#             */
/*   Updated: 2025/04/01 19:53:13 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_close(void *param)
{
	(void)param;
	exit(EXIT_SUCCESS);
	return (0);
}
void	init_struct(t_cub *cub)
{
	cub->img = NULL;
	cub->map = NULL;
	cub->mlx = NULL;
	cub->mlx_win = NULL;
	cub->no_xpm = NULL;
	cub->we_xpm = NULL;
	cub->so_xpm = NULL;
	cub->ea_xpm = NULL;
}

void	init_mlx(t_map *map, t_cub *cub)
{
	int	width;
	int	height;

	cub->map = map;
	cub->no_xpm = mlx_xpm_file_to_image(cub->mlx, map->no_texture, &width, &height);
	cub->so_xpm = mlx_xpm_file_to_image(cub->mlx, map->so_texture, &width, &height);
	cub->ea_xpm = mlx_xpm_file_to_image(cub->mlx, map->ea_texture, &width, &height);
	cub->we_xpm = mlx_xpm_file_to_image(cub->mlx, map->we_texture, &width, &height);
	if (!cub->no_xpm || !cub->so_xpm || !cub->we_xpm || !cub->ea_xpm)
	{
		ft_putstr_fd("Texture loading failed\n", 2);
		return ;
	}
	cub->img->north = (int *)mlx_get_data_addr(cub->no_xpm, &cub->img->bpp,
		&cub->img->line_length, &cub->img->endian);
	cub->img->south = (int *)mlx_get_data_addr(cub->so_xpm, &cub->img->bpp,
		&cub->img->line_length, &cub->img->endian);
	cub->img->west = (int *)mlx_get_data_addr(cub->we_xpm, &cub->img->bpp,
		&cub->img->line_length, &cub->img->endian);
	cub->img->east = (int *)mlx_get_data_addr(cub->ea_xpm, &cub->img->bpp,
		&cub->img->line_length, &cub->img->endian);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_cub	cub;

	if (start_parsing(argc, argv, &map) != SUCCESS)
		return (EXIT_FAILURE);
	init_struct(&cub);
	cub.mlx = mlx_init();
	init_mlx(&map, &cub);
	cub.mlx_win = mlx_new_window(cub.mlx, 1280, 720, "cub3d");
	mlx_hook(cub.mlx_win, 17, 0, handle_close, NULL);
	mlx_loop(cub.mlx);
	return (EXIT_SUCCESS);
}
