######### COLORS ########

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

######### FLAGS ########

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_PATH = libft
MLX_PATH = mlx

######### DIRECTORIES ########

SRC_DIR = srcs
OBJ_DIR = objs
INCLUDE_DIR = includes
INCLUDE_DIRS = -I$(INCLUDE_DIR) -I$(LIBFT_PATH)/includes -I$(MLX_PATH)

######### FILES ########

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
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
	@echo "$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c -o $@ $<
	@echo "$(NAME): $(GREEN)$@ was created$(RESET)"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)
	@echo "$(NAME): $(GREEN)$(LIBFT) was created$(RESET)"

$(MLX):
	@$(MAKE) -C $(MLX_PATH)
	@echo "$(NAME): $(GREEN)$(MLX) was created$(RESET)"

clean:
	@$(MAKE) -C $(LIBFT_PATH) clean
	@$(MAKE) -C $(MLX_PATH) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(NAME): $(RED)$(OBJ_DIR) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re