######### COLORS ########

GREEN := $(shell printf "\033[32m")
RED := $(shell printf "\033[31m")
BLUE := $(shell printf "\033[34m")
YELLOW := $(shell printf "\033[33m")
RESET := $(shell printf "\033[0m")
BOLD := $(shell printf "\033[1m")

######### FLAGS ########

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -O0
LIBFT_PATH = libft
MLX_PATH = mlx

######### DIRECTORIES ########

SRC_DIR = srcs
OBJ_DIR = objs
INCLUDE_DIR = includes
INCLUDE_DIRS = -I$(INCLUDE_DIR) -I$(LIBFT_PATH)/includes -I$(MLX_PATH)

######### FILES ########

rwildcard = $(foreach d, $(wildcard $1*), $(call rwildcard,$d/,$2) $(filter $(subst *,%,$2), $d))

# Find all .c files in src directory and its subdirectories
SRC_FILES = $(call rwildcard, $(SRC_DIR)/, *.c)

# Create object files with directory structure preserved
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