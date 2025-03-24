/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:52:41 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/24 15:45:21 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_err_status	process_texture(const char *line, char **texture)
{
	while (ft_isspace(*line))
		line++;
	
	if (ft_strncmp(line, "./", 2) != 0)
		return (ERR_TEXTURE_PATH);
	line += 2;
	printf("line: %s\n", line);
	if (validate_file_path(line, MSG_INVALID_TEXTURE_PATH) != SUCCESS)
		return (ERR_TEXTURE_PATH);
	if (*texture)
		free(*texture);
	*texture = ft_strdup(line);
	if (!*texture)
		return (MALLOC_FAILURE);
	return (SUCCESS);
}

int	check_rgb_values(char **str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (ft_str_isdigit(str[i]) == false)
			return (EXIT_FAILURE);
		if (ft_atoi(str[i]) > 255 || ft_atoi(str[i]) < 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static t_err_status	process_colors(const char *line, t_rgb colors)
{
	char	**splitted_rgb;

	while (ft_isspace(*line))
		line++;
	
	splitted_rgb = ft_split(line, ',');
	if (!splitted_rgb)
		return (MALLOC_FAILURE);
	if (splitted_rgb[4] != NULL || !splitted_rgb[3])
		return (ERR_COLOR);
	if (check_rgb_values(splitted_rgb) == EXIT_FAILURE)
		return (ERR_COLOR);
	colors.r = ft_atoi(splitted_rgb[0]);
	colors.g = ft_atoi(splitted_rgb[1]);
	colors.b = ft_atoi(splitted_rgb[2]);

	return (SUCCESS);
}



t_err_status	parse_textures(char *line, t_map *map)
{
	t_err_status	status;

	status = SUCCESS;
	if (ft_strncmp(line, "NO", 2) == 0 && status == SUCCESS)
		status = process_texture(&line[2], &map->no_texture);
	else if (ft_strncmp(line, "SO", 2) == 0 && status == SUCCESS)
		status = process_texture(&line[2], &map->so_texture);
	else if (ft_strncmp(line, "WE", 2) == 0 && status == SUCCESS)
		status = process_texture(&line[2], &map->we_texture);
	else if (ft_strncmp(line, "EA", 2) == 0 && status == SUCCESS)
		status = process_texture(&line[2], &map->ea_texture);
	return (status);
}



t_err_status	parse_colors(char *line, t_map *map)
{
	t_err_status	status;

	status = SUCCESS;
	if (line[0] == 'C')
	status = process_color(&line[1], &map->ceiling_color);
	if (line[0] == 'F')
		status = process_color(&line[1], &map->floor_color);
	return (status);
}

static void trim_newline(char *str)
{
    size_t len = ft_strlen(str);
    if (len > 2 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

bool	are_we_in_map(char *line)
{
	bool	state;

	state = true;
	if (ft_strncmp(line, "NO", 2) == 0)
		state = false;
	if (ft_strncmp(line, "SO", 2) == 0)
		state = false;	
	if (ft_strncmp(line, "EA", 2) == 0)
		state = false;
	if (ft_strncmp(line, "WE", 2) == 0)
		state = false;
	if (line[0] == 'F')
		state = false;
	if (line[0] == 'C')
		state = false;
	return (state);
}

int		map_line_length(char *line)
{
	int i;
	int	len;

	len = 0;
	i = 0;
	len = ft_strlen(line);
	while(line[i])
	{
		if (line[i] == '\t')
			len = len + 3;
		i++;
	}
	return (len);
}

int		*map_translator(char *line)
{
	int	*new;
	int	i;
	int	j;

	i = 0;
	new = malloc(sizeof(int) * map_line_length(line) + 1); //ptet degager le + 1
	while(line[i])
	{
		if (line[i] == '\t')
		{
			j = 0;
			while(j != 4)
			{
				new[i] = 0;
				i++;
				j++;
			}
		}
		if (line[i] == ' ' || line[i] == '0')
			new[i] = 0;
		else if (line[i] == '1')
			new[i] = 1;
		else if (line[i] == 'N')
			new[i] = NORTH;
		else if (line[i] == 'W')
			new[i] = WEST;
		else if (line[i] == 'E')
			new[i] = EAST;
		else if (line[i] == 'S')
			new[i] = SOUTH;
		else
			new[i] = -1;
	}
	return (new);
}

void	map_reader(line, map, fd)
{
	int	i;

	i = 0;
	while(line)
	{
		

		
		line = get_next_line(fd);
	}
}

t_err_status	cub_file_readloop(char *file, t_map *map)
{
	int				fd;
	char			*line;
	t_err_status	status;

	status = SUCCESS;
	fd = open(file, O_RDONLY);
	
	while ((line = get_next_line(fd)))
	{
		trim_newline(line);
		if (are_we_in_map(line) == false)
		{
			status = parse_textures(line, map);
			status = parse_colors(line, map);
		}
		else
			map_reader(line, map, fd);
		free(line);

		if (status != SUCCESS)
			break ;
	}
	close(fd);
	return (SUCCESS);
}



void	ft_lstadd_end(t_submap **head, int value)
{
	t_submap	*new_node;
	t_submap	*temp;

	new_node = create_node(value);
	if (!head || !new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	else
	{
		temp = *head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new_node;
		new_node->prev = temp;
	}
}

void	ft_add_in_list(t_submap **head, char *argv)
{
	ft_lstadd_end(head, ft_atoi(argv));
}

void	*create_node(int value)
{
	t_submap	*new_node;

	new_node = (t_submap *)malloc(sizeof(t_submap));
	if (!new_node)
		return (NULL);
	return (new_node);
}