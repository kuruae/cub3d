/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:24:02 by emagnani          #+#    #+#             */
/*   Updated: 2025/04/09 18:42:45 by habouda          ###   ########.fr       */
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

// File extension
# define EXT ".cub"
# define EXT_LEN 4

// temp file path
# define TEMP_FILE "/tmp/tmp.cub"

// Map values
# define NORTH '2'
# define WEST '3'
# define EAST '4'
# define SOUTH '5'
# define VOID '6'

// Debug functions
void			debug_print_file(char *file);
void			debug_print_struct_map(t_map *map);
void			debug_print_translated_line(int *translated_line);
void			debug_print_full_map(int **full_map);

// Helpers
int				ft_tablen(int *tab);
void			trim_newline(char *str);
t_err_status	validate_file_path(const char *file, char *msg);
int				read_all_texture_sizes(t_cub *cub);
int				get_map_height(char **map);
int				get_map_width(char **map, int height);
int				is_map_closed(t_map *map, int height, int width);
void			get_dimensions(char **arr, int *rows, int *max_cols);
int				check_for_x(char **map);

// Parsing main
t_err_status	validate_file_extension(char *file);
t_err_status	start_parsing(int argc, char **argv, t_map *map);

// Parsing cubfile
t_err_status	start_parsing_cub_file(char *file, t_map *map);
t_err_status	cub_file_readloop(char *file, t_map *map);
t_err_status	process_line(char *line, t_map *map, int fd);
t_err_status	verify_values(t_map *map);
t_err_status	verify_data(t_map *map);

// Parsing textures
t_err_status	parse_textures(char *line, t_map *map);

// Parsing colors
t_err_status	parse_colors(char *line, t_map *map);

// Parsing map
t_err_status	map_reader(char *line, t_map *map, int fd);
char			*is_map_closed_upper(char **map, size_t width);
char			*is_map_closed_bottom(char **map, int height, size_t width);

// map translator
char			*map_translator(char *line);

#endif