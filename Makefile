NAME        = miniRT
BONUS_NAME  = miniRT_bonus

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

LIBFT_DIR   = libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a

MLX_DIR     = minilibx-linux
MLX_LIB     = $(MLX_DIR)/libmlx.a

INC_DIR     = includes
INCLUDES    = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

LIBS        = -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lm


SRC_DIR     = src
#add here
SRC         = 

BONUS_DIR   = src_bonus
#add bonus here
BONUS_SRC   = 


OBJ         = $(SRC:.c=.o)
BONUS_OBJ   = $(BONUS_SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBS) -o $(BONUS_NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	rm -f $(OBJ) $(BONUS_OBJ)
	@make -C $(LIBFT_DIR) clean
	@if [ -d "$(MLX_DIR)" ]; then make -C $(MLX_DIR) clean; fi

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
