/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:04:13 by habouda           #+#    #+#             */
/*   Updated: 2025/03/28 20:09:34 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_add_in_list_cub(t_submap **head, int id, int *line)
{
	ft_lstadd_end_cub(head, id, line);
}

void	ft_lstadd_end_cub(t_submap **head, int id, int *line)
{
	t_submap	*new_node;
	t_submap	*temp;

	if (!head || !line)
		return ;
	new_node = create_node_cub(id, line);
	if (!new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
	new_node->prev = temp;
}

void	*create_node_cub(int id, int *line)
{
	t_submap	*new_node;

	new_node = (t_submap *)malloc(sizeof(t_submap));
	if (!new_node)
		return (NULL);
	new_node->id = id;
	new_node->line = line;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
