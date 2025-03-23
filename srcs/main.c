/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:13:33 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/23 17:57:23 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;

	if (start_parsing(argc, argv) != SUCCESS)
		return (EXIT_FAILURE);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1280, 720, "cub3d");
	mlx_loop(mlx);
	(void)mlx_win;
	return (EXIT_SUCCESS);
}
