/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuru <kuru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 17:41:36 by habouda           #+#    #+#             */
/*   Updated: 2025/04/08 22:29:25 by kuru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_struct_cub(t_cub *cub, t_img *img)
{
	if (read_all_texture_sizes(cub) != 0)
	{
		ft_putstr_fd("Error: Texture size reading error\n", 2);
		return (1);
	}
	cub->ray = malloc(sizeof(t_ray) * 1);
	cub->img = img;
	cub->map = NULL;
	cub->mlx = NULL;
	cub->mlx_win = NULL;
	cub->no_xpm = NULL;
	cub->we_xpm = NULL;
	cub->so_xpm = NULL;
	cub->ea_xpm = NULL;
	return (0);
}

void	init_mlx(t_map *map, t_cub *cub)
{
	int	width;
	int	height;

	cub->map = map;
	cub->no_xpm = mlx_xpm_file_to_image(cub->mlx, map->no_texture, &width,
			&height);
	cub->so_xpm = mlx_xpm_file_to_image(cub->mlx, map->so_texture, &width,
			&height);
	cub->ea_xpm = mlx_xpm_file_to_image(cub->mlx, map->ea_texture, &width,
			&height);
	cub->we_xpm = mlx_xpm_file_to_image(cub->mlx, map->we_texture, &width,
			&height);
	if (!cub->no_xpm || !cub->so_xpm || !cub->we_xpm || !cub->ea_xpm)
	{
		ft_putstr_fd("Texture loading failed WHY\n", 2);
		return ;
	}
	cub->img->north = mlx_get_data_addr(cub->no_xpm, &cub->img->bpp,
			&cub->img->line_length, &cub->img->endian);
	cub->img->south = mlx_get_data_addr(cub->so_xpm, &cub->img->bpp,
			&cub->img->line_length, &cub->img->endian);
	cub->img->west = mlx_get_data_addr(cub->we_xpm, &cub->img->bpp,
			&cub->img->line_length, &cub->img->endian);
	cub->img->east = mlx_get_data_addr(cub->ea_xpm, &cub->img->bpp,
			&cub->img->line_length, &cub->img->endian);
	if (!cub->img->north || !cub->img->west || !cub->img->south
		|| !cub->img->east)
	{
		ft_putstr_fd("Image loading failed WHY\n", 2);
		return ;
	}
}
