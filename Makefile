# Minimal Makefile for cub3d (Linux / minilibx)
NAME		:= cub3d
CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -Iinc
MLX_DIR		:= minilibx-linux
MLX_LIBS	:= -L$(MLX_DIR) -lmlx -lX11 -lXext -lm
LIBFT_DIR	:= libft

SRCS		:= src/main.c $(shell find src -mindepth 2 -name '*.c')
OBJS		:= $(SRCS:.c=.o)

.PHONY: all clean fclean re mlx libft

all: mlx libft $(NAME)

mlx:
	@$(MAKE) -C $(MLX_DIR)

libft:
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)/libft.a $(MLX_LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean || true

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean || true

re: fclean all
