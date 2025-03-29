/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:57:38 by habouda           #+#    #+#             */
/*   Updated: 2025/03/29 19:44:07 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_for_6(t_map *map, int i, int j, int width)
{
	if (j == 0)
	{
		if (map->map[i][j] == VOID && (map->map[i][j + 1] == '0'))
			return (1);
	}
	else if (j == width - 1)
	{
		if (map->map[i][j] == VOID && (map->map[i][j - 1] == '0'))
			return (1);
	}
	else
	{
		if (map->map[i][j] == VOID && (map->map[i][j - 1] == '0' || map->map[i][j + 1] == '0'))
			return (1);
	}
	return (0);
}

char	*is_map_closed_upper(t_map *map, size_t width)
{
	size_t	i;
	size_t	j;
	char	*up;

	up = malloc(sizeof(char) * (width + 1));
	if (!up)
		return (NULL);
	j = 0;
	while (j < width)
	{
		i = 0;
		while (map->map[i] && (j >= ft_strlen(map->map[i]) || map->map[i][j] == VOID))
		{
			if (check_for_6(map, i, j, width) == 1)
				return (NULL);
			i++;
		}
		if (map->map[i])
			up[j] = map->map[i][j];
		j++;
	}
	up[j] = '\0';
	return (up);
}

char	*is_map_closed_bottom(t_map *map, int height, size_t width)
{
	size_t	i;
	size_t	j;
	char	*bottom;

	bottom = malloc(sizeof(char) * (width + 1));
	if (!bottom)
		return (NULL);
	j = 0;
	while (j < width)
	{
		i = height - 1;
		while (map->map[i] && (j >= ft_strlen(map->map[i]) || map->map[i][j] == VOID))
		{
			if (check_for_6(map, i, j, width) == 1)
				return (NULL);
			i--;
		}
		if (i >= 0)
			bottom[j] = map->map[i][j];
		j++;
	}
	bottom[j] = '\0';
	return (bottom);
}

char *is_map_closed_left(t_map *map, int height)
{
	int	i;
	int	j;
	char	*left;

	left = malloc(sizeof(char) * (height + 1));
	if (!left)
		return (NULL);
	i = 0;
	while(i < height)
	{
		j = 0;
		while(map->map[i][j] && map->map[i][j] == VOID)
			j++;
		if (map->map[i][j])
			left[i] = map->map[i][j];
		i++;
	}
	left[i + 1] = '\0';
	return (left);
}


char	*is_map_closed_right(t_map *map, size_t height)
{
	size_t	i;
	size_t	j;
	char	*right;

	right = malloc(sizeof(char) * (height + 1));
	if (!right)
		return (NULL);
	i = 0;
	while(map->map[i] && i < height)
	{
		j = ft_strlen(map->map[i]) - 1;
		while(j >= 0 && map->map[i][j] == VOID)
			j--;
		if (j >= 0)
			right[i] = map->map[i][j];
		i++;
	}
	right[i] = '\0';
	return (right);
}

int	is_map_closed(t_map *map, int height, int width)
{
	char	*up;
	char	*bottom;
	char	*left;
	char	*right;
	int	i;

	i = 0;
	up = is_map_closed_upper(map, width);
	bottom = is_map_closed_bottom(map, height, width);
	right = is_map_closed_right(map, (size_t)(height));
	left = is_map_closed_left(map, height);
	if (!up || !bottom)
	{
		printf("hole in map");
		return 1;
	}
	printf("\nup %s\n", up);
	printf("down %s\n", bottom);
	printf("right %s\n", right);
	printf("left %s\n", left);
	while(up[i])
	{
		if (up[i] == '0')
		{
			printf("hole in topside \n");
			break;	
		}
		i++;
	}
	i = 0;
	while(bottom[i])
	{
		if (bottom[i] == '0')
		{
			printf("hole in bottomside \n");
			break;
		}
		i++;
	}
	i= 0;
	while(right[i])
	{
		if (right[i] == '0')
		{
			printf("hole in rightside \n");
			break;	
		}
		i++;
	}
	i = 0;
	while(left[i])
	{
		if (left[i] == '0')
		{
			printf("hole in leftside\n");
			break;
		}
		i++;
	}
	return (0);
}
