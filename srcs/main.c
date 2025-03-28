/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:13:33 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/28 20:09:23 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_close(void *param)
{
	(void)param;
	exit(EXIT_SUCCESS);
	return (0);
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;

	if (start_parsing(argc, argv) != SUCCESS)
		return (EXIT_FAILURE);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1280, 720, "cub3d");
	mlx_hook(mlx_win, 17, 0, handle_close, NULL);
	mlx_loop(mlx);
	(void)mlx_win;
	return (EXIT_SUCCESS);
}
