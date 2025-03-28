/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:48:35 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/28 20:09:38 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_err_status	err_handler(char *err_message, t_err_status status)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(err_message, STDERR_FILENO);
	return (status);
}
