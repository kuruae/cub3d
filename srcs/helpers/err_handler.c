/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:48:35 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/17 18:01:44 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	err_handler(char *err_message, bool exit_program)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(err_message, STDERR_FILENO);
	if (exit_program)
		exit(EXIT_FAILURE);
	return (EXIT_FAILURE);
}
