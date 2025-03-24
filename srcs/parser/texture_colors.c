/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagnani <emagnani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:52:41 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/24 18:27:31 by emagnani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	map_reader(char *line, t_map *map, int fd)
{
	(void)fd;
	(void)map;
	(void)line;
	return ;
	// int	i;

	// i = 0;
	// while(line)
	// {
		

		
	// 	line = get_next_line(fd);
	// }
}

t_err_status	process_line(char *line, t_map *map, int fd)
{
	t_err_status	status;

	status = SUCCESS;
	trim_newline(line);
	if (are_we_in_map(line) == false)
	{
		status = parse_textures(line, map);
		if (status == SUCCESS)
			status = parse_colors(line, map);
	}
	else
		map_reader(line, map, fd);
	return (status);
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
		status = process_line(line, map, fd);
		free(line);
		if (status != SUCCESS)
			break ;
	}
	close(fd);
	return (SUCCESS);
}

// void	ft_lstadd_end(t_submap **head, int value)
// {
// 	t_submap	*new_node;
// 	t_submap	*temp;

// 	new_node = create_node(value);
// 	if (!head || !new_node)
// 		return ;
// 	if (*head == NULL)
// 	{
// 		*head = new_node;
// 		return ;
// 	}
// 	else
// 	{
// 		temp = *head;
// 		while (temp->next != NULL)
// 		{
// 			temp = temp->next;
// 		}
// 		temp->next = new_node;
// 		new_node->prev = temp;
// 	}
// }

// void	ft_add_in_list(t_submap **head, char *argv)
// {
// 	ft_lstadd_end(head, ft_atoi(argv));
// }

// void	*create_node(int value)
// {
// 	t_submap	*new_node;

// 	new_node = (t_submap *)malloc(sizeof(t_submap));
// 	if (!new_node)
// 		return (NULL);
// 	return (new_node);
// }