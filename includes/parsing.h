/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:24:02 by emagnani          #+#    #+#             */
/*   Updated: 2025/03/24 20:54:16 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

// Error handling
# define MSG_INVALID_ARGS "Invalid number of arguments\n"
# define MSG_INVALID_EXT "Invalid file extension\n"
# define MSG_INVALID_MAP_PATH "Invalid map path\n"
# define MSG_INVALID_TEXTURE_PATH "Invalid texture path\n"
# define MSG_INVALID_COLOR "Invalid color\n"
# define MSG_INVALID_MAP "Invalid Map\n"

# define NORTH 2
# define WEST 3
# define EAST 4
# define SOUTH 5
# define TABS 6

// Debug functions
void			debug_print_file(char *file);
void			debug_print_struct_map(t_map *map);

// Helpers
t_err_status	validate_file_path(const char *file, char *msg);

// Parsing main
t_err_status	validate_file_extension(char *file);
t_err_status	start_parsing(int argc, char **argv);

// Parsing textures
t_err_status	parse_textures(char *line, t_map *map);

// Parsing colors
t_err_status	parse_colors(char *line, t_map *map);

// Parsing map
t_err_status	start_parsing_cub_file(char *file);
t_err_status	cub_file_readloop(char *file, t_map *map);
t_err_status	process_line(char *line, t_map *map, int fd);


//map translator && debuyg

int		*map_translator(char *line);


// Structs


#endif