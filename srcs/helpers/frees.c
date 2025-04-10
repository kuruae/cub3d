/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:50:16 by habouda           #+#    #+#             */
/*   Updated: 2025/04/10 19:41:30 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	close_mlx(t_cub *cub)
{
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
}

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
	mlx_destroy_image(cub->mlx, cub->mini->img);
	mlx_destroy_image(cub->mlx, cub->no_xpm);
	mlx_destroy_image(cub->mlx, cub->so_xpm);
	mlx_destroy_image(cub->mlx, cub->we_xpm);
	mlx_destroy_image(cub->mlx, cub->ea_xpm);
	ft_free_str_array(&cub->map->map);
	free(cub->mini);
	close_mlx(cub);
	exit(EXIT_SUCCESS);
	return (0);
}
