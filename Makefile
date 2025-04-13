######### COLORS ########

GREEN := $(shell printf "\033[32m")
RED := $(shell printf "\033[31m")
BLUE := $(shell printf "\033[34m")
YELLOW := $(shell printf "\033[33m")
RESET := $(shell printf "\033[0m")
BOLD := $(shell printf "\033[1m")

######### FLAGS ########

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -O0 -gdwarf-4
LIBFT_PATH = libft
MLX_PATH = mlx

######### DIRECTORIES ########

SRC_DIR = srcs
OBJ_DIR = objs
INCLUDE_DIR = includes
INCLUDE_DIRS = -I$(INCLUDE_DIR) -I$(LIBFT_PATH)/includes -I$(MLX_PATH)

######### FILES ########

# Explicitly list all source files
SRC_FILES = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/bonus/mini_helpers.c \
	$(SRC_DIR)/bonus/minimap.c \
	$(SRC_DIR)/bonus/mouse.c \
	$(SRC_DIR)/exec/draw.c \
	$(SRC_DIR)/exec/keys.c \
	$(SRC_DIR)/exec/mouvement.c \
	$(SRC_DIR)/exec/render.c \
	$(SRC_DIR)/exec/rotate.c \
	$(SRC_DIR)/helpers/draw_helper.c \
	$(SRC_DIR)/helpers/empty_gnl_buffer.c \
	$(SRC_DIR)/helpers/err_handler.c \
	$(SRC_DIR)/helpers/frees.c \
	$(SRC_DIR)/helpers/ft_isdigit_whitespaces.c \
	$(SRC_DIR)/helpers/get_player_pos.c \
	$(SRC_DIR)/helpers/init_mlx.c \
	$(SRC_DIR)/helpers/is_power_of_two.c \
	$(SRC_DIR)/helpers/rgb_to_int.c \
	$(SRC_DIR)/helpers/speed_related_helpers.c \
	$(SRC_DIR)/helpers/wall_too_close.c \
	$(SRC_DIR)/helpers/xpm.c \
	$(SRC_DIR)/parser/colors_parsing.c \
	$(SRC_DIR)/parser/cub_file_reader.c \
	$(SRC_DIR)/parser/cub_parsing.c \
	$(SRC_DIR)/parser/debug_parsing.c \
	$(SRC_DIR)/parser/is_map_closed.c \
	$(SRC_DIR)/parser/main_parsing.c \
	$(SRC_DIR)/parser/map_parsing.c \
	$(SRC_DIR)/parser/map_translator.c \
	$(SRC_DIR)/parser/textures_parsing.c \
	$(SRC_DIR)/parser/verify_map.c

# Create object files (can still use pattern for this)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

######### LIBRARIES ########

LIBFT = $(LIBFT_PATH)/libft.a
MLX = $(MLX_PATH)/libmlx.a

######### MLX FLAGS ########

MLX_ARGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm

######### NAME ########

NAME = cub3D

######### COMMANDS ########

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFT_PATH) -lft -L$(MLX_PATH) $(MLX_ARGS)
	@printf "$(GREEN)$(BOLD)$(NAME) successfully compiled!$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c -o $@ $<
	@printf "$(BLUE)Compiling$(RESET) $(BOLD)$<$(RESET)\n"

$(LIBFT):
	@printf "$(YELLOW)$(BOLD)Building libft...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_PATH) --no-print-directory > /dev/null 2>&1
	@printf "$(GREEN)$(BOLD)libft compiled!$(RESET)\n"

$(MLX):
	@printf "$(YELLOW)$(BOLD)Building minilibx...$(RESET)\n"
	@$(MAKE) -C $(MLX_PATH) --no-print-directory > /dev/null 2>&1
	@printf "$(GREEN)$(BOLD)minilibx compiled!$(RESET)\n"

clean:
	@printf "$(YELLOW)$(BOLD)Cleaning object files...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_PATH) clean --no-print-directory > /dev/null 2>&1
	@printf "$(RED)libft objects removed$(RESET)\n"
	@$(MAKE) -C $(MLX_PATH) clean --no-print-directory > /dev/null 2>&1
	@printf "$(RED)minilibx objects removed$(RESET)\n"
	@rm -rf $(OBJ_DIR)
	@printf "$(RED)$(NAME) objects removed$(RESET)\n"

fclean: clean
	@printf "$(YELLOW)$(BOLD)Removing executables and libraries...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_PATH) fclean --no-print-directory > /dev/null 2>&1
	@printf "$(RED)libft.a removed$(RESET)\n"
	@rm -f $(NAME)
	@printf "$(RED)$(NAME) executable removed$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re