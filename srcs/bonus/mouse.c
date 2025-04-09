/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:26:28 by habouda           #+#    #+#             */
/*   Updated: 2025/04/09 19:34:20 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


//franchement jai pas tout compris hein///
int	mouse_function(int x, int y, void *arg)
{
	static int	s_x = 0;
	t_cub		*cub;

	cub = (t_cub *)arg;
	(void)y;
	if (!s_x)
		s_x = x;
	if (x < s_x)
		rotate_left(cub, MOUSE_SPEED);
	if (x > s_x)
		rotate_right(cub, MOUSE_SPEED);
	s_x = x;
	return (0);
}
