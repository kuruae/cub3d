/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_double_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:35:24 by habouda           #+#    #+#             */
/*   Updated: 2025/04/07 20:40:47 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_dimensions(char **arr, int *rows, int *max_cols)
{
	int	i;
	int	len;

	*rows = 0;
	*max_cols = 0;
	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		len = 0;
		while (arr[i][len])
			len++;
		if (len > *max_cols)
			*max_cols = len;
		i++;
	}
	*rows = i;
}

char	**allocate_rotated(int rows, int cols)
{
	char	**rotated;
	int		i;

	rotated = (char **)malloc((cols + 1) * sizeof(char *));
	if (!rotated)
		return (NULL);
	i = 0;
	while (i < cols)
	{
		rotated[i] = (char *)malloc((rows + 1) * sizeof(char));
		if (!rotated[i])
		{
			while (--i >= 0)
				free(rotated[i]);
			free(rotated);
			return (NULL);
		}
		i++;
	}
	rotated[cols] = NULL;
	return (rotated);
}

char	**rotate_array(char **arr)
{
	int		rows;
	int		cols;
	int		i;
	int		j;
	char	**rotated;

	get_dimensions(arr, &rows, &cols);
	if (rows == 0 || cols == 0)
		return (NULL);
	rotated = allocate_rotated(rows, cols);
	i = -1;
	while (++i < cols)
	{
		j = -1;
		while (++j < rows)
		{
			if (j < rows && i < (int)ft_strlen(arr[j]))
				rotated[i][j] = arr[j][i];
			else
				rotated[i][j] = ' ';
		}
		rotated[i][rows] = '\0';
	}
	return (rotated);
}