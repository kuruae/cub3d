/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit_whitespaces.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:48:06 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/29 17:46:30 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * same as my ft_is_str_digit but also 
 * allows/trims whitespaces
 */
bool	ft_isdigit_whitespaces(char *str)
{
	if (!str || *str == '\0')
		return (false);
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str) && !ft_isspace(*str))
			return (false);
		str++;
	}
	return (true);
}
int		ft_tablen(int *tab)
{
	int	i;

	i = 0;
	while(tab[i] != -1)
		i++;
	return (i);
}