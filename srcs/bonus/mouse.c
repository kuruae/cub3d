/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuru <kuru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:26:28 by habouda           #+#    #+#             */
/*   Updated: 2025/04/10 01:53:30 by kuru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_function(int x, int y, void *arg)
{
	static int	old_x = 0;
	t_cub		*cub;

	cub = (t_cub *)arg;
	(void)y;
	if (!old_x)
		old_x = x;
	if (x < old_x)
		rotate_left(cub, MOUSE_SPEED);
	if (x > old_x)
		rotate_right(cub, MOUSE_SPEED);
	old_x = x;
	return (0);
}
