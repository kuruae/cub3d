/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_double_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 18:35:24 by habouda           #+#    #+#             */
/*   Updated: 2025/04/07 20:29:04 by emagnani         ###   ########.fr       */
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



char	**rotate_array(char **arr, int width, int height)
{
	int i;
	int j;
	int	iterated;
	int	new_i;
	int	new_j;
	char	**rotated;
	
	rotated = malloc(sizeof(char *) * (width + 1));
	if (!rotated)
		return (NULL);
	iterated = 0;
	new_i = 0;
	j = 0;
	while (iterated < width)
	{
		new_j = 0;
		i = 0;
		rotated[new_i] = malloc(sizeof(char) * (height + 1));
		if (!rotated[new_i])
			return (NULL); // Proper error handling needed
		while (i < height)
		{
			// Ensure j is within the original row's bounds; use default if necessary
			if ((size_t)j < (size_t)ft_strlen(arr[i]))
				rotated[new_i][new_j] = arr[i][j];
			else
				rotated[new_i][new_j] = ' '; // Example padding
			i++;
			new_j++;
		}
		rotated[new_i][new_j] = '\0';
		j++;
		new_i++;
		iterated++;
	}
	rotated[new_i] = NULL;
	return (rotated);
}

// char	**rotate_array(char **arr, int width, int height)
// {
// 	int	i;
// 	int	j;
// 	int counter;
// 	char	**rotated;

// 	rotated = malloc(sizeof(char * ) *  width + 1);
// 	i = 0;
// 	j = 0;
// 	counter = 0;
// 	while (arr[i])
// 	{
// 		i = 0;
// 		while (arr[i][j])
// 			i++;
// 		rotated[counter] = malloc(sizeof(char) * i + 1);
// 		counter++;
// 		j++;
// 	}
// 	rotated[counter + 1] = NULL;
// 	i = 0;
// 	j = 0;
// 	counter = 0;
// 	while (arr[i])
// 	{
// 		i = 0;
// 		while (arr[i][j])
// 		{
// 			rotated[j]
// 			i++;
// 		}
// 		j++;
// 	}
// }
