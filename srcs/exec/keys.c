/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuru <kuru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:11:39 by kuru              #+#    #+#             */
/*   Updated: 2025/04/05 20:52:35 by kuru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_keys(t_cub *cub)
{
	cub->keys = malloc(sizeof(t_keys));
	if (!cub->keys)
	{
		printf("Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	cub->keys->w = 0;
	cub->keys->a = 0;
	cub->keys->s = 0;
	cub->keys->d = 0;
	cub->keys->left = 0;
	cub->keys->right = 0;
}

int	press(int keysym, t_cub *cub)
{
	if (keysym == XK_Escape)
		handle_close(cub);
	if (keysym == XK_w)
		cub->keys->w = 1;
	if (keysym == XK_s)
		cub->keys->s = 1;
	if (keysym == XK_a)
		cub->keys->a = 1;
	if (keysym == XK_d)
		cub->keys->d = 1;
	if (keysym == XK_Left)
		cub->keys->left = 1;
	if (keysym == XK_Right)
		cub->keys->right = 1;
	return (0);
}

int	release(int keysym, t_cub *cub)
{
	if (keysym == XK_Escape)
		handle_close(cub);
	if (keysym == XK_w)
		cub->keys->w = 0;
	if (keysym == XK_s)
		cub->keys->s = 0;
	if (keysym == XK_a)
		cub->keys->a = 0;
	if (keysym == XK_d)
		cub->keys->d = 0;
	if (keysym == XK_Left)
		cub->keys->left = 0;
	if (keysym == XK_Right)
		cub->keys->right = 0;
	return (0);
}
