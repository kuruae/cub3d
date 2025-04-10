/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   speed_related_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kuru <kuru@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:35:33 by kuru              #+#    #+#             */
/*   Updated: 2025/04/10 22:33:46 by kuru             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calculate_move_speed(t_cub *cub)
{
	double	final_speed;

	final_speed = MOVE_SPEED * cub->time.delta_time;
	if (cub->keys->w && cub->keys->a)
		final_speed *= sqrt(2) / 2;
	else if (cub->keys->w && cub->keys->d)
		final_speed *= sqrt(2) / 2;
	else if (cub->keys->s && cub->keys->a)
		final_speed *= sqrt(2) / 2;
	else if (cub->keys->s && cub->keys->d)
		final_speed *= sqrt(2) / 2;
	return (final_speed);
}

static double	get_time_in_seconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

void	compute_t_time_values(t_cub *cub)
{
	cub->time.curr_time = get_time_in_seconds();
	cub->time.delta_time = cub->time.curr_time - cub->time.last_time;
	cub->time.last_time = cub->time.curr_time;
	if (cub->time.delta_time > 0.1)
		cub->time.delta_time = 0.1;
}

void	update_fps_counter(t_cub *cub)
{
	char			fps_text[30];
	char			*fps_nbr;
	char			*fps_joined;
	static t_fps	fps = {0, 0, 0};

	fps.frame_count++;
	fps.elapsed_time += cub->time.delta_time;
	if (fps.elapsed_time >= 1.0)
	{
		fps.fps = fps.frame_count / fps.elapsed_time;
		fps.frame_count = 0;
		fps.elapsed_time = 0;
	}
	ft_strlcpy(fps_text, "FPS: ", sizeof(fps_text));
	fps_nbr = ft_itoa((int)fps.fps);
	if (!fps_nbr)
		return ;
	fps_joined = ft_strjoin(fps_text, fps_nbr);
	if (!fps_joined)
		return (free(fps_nbr));
	mlx_string_put(cub->mlx, cub->mlx_win, 1200, 30,
		0xFFFFFF, fps_joined);
	free(fps_nbr);
	free(fps_joined);
}
