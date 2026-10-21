NAME        = miniRT
BONUS_NAME  = miniRT_bonus

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

LIBFT_DIR   = 42_libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a

MLX_DIR     = minilibx-linux
MLX_LIB     = $(MLX_DIR)/libmlx.a


LIBS        = -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lm


SRC_DIR     = mandatory/
#add here
SRC         = $(SRC_DIR)main.c $(SRC_DIR)windows.c $(SRC_DIR)utils/cleanup.c $(SRC_DIR)parsing/file_validation.c \
			$(SRC_DIR)parsing/init_elem.c $(SRC_DIR)parsing/init_objs.c $(SRC_DIR)parsing/init_cylinder.c $(SRC_DIR)parsing/read_file.c $(SRC_DIR)utils/parse_utils.c \
			mathlib/dotprod.c mathlib/norm.c mathlib/normvec.c mathlib/vecadd.c mathlib/vecmag.c mathlib/vecsub.c mathlib/vecscale.c \
			 mathlib/veccross.c mathlib/is_zero_vec.c $(SRC_DIR)utils/render_utils.c $(SRC_DIR)render/camera.c $(SRC_DIR)render/render.c mathlib/vecsquared.c $(SRC_DIR)/render/intersect.c \
			 $(SRC_DIR)render/lighting.c mathlib/veclen.c $(SRC_DIR)utils/validation.c
			
			
BONUS_DIR   = bonus/
BONUS_SRC   = $(BONUS_DIR)main_bonus.c $(BONUS_DIR)windows_bonus.c \
			$(BONUS_DIR)utils/cleanup_bonus.c $(BONUS_DIR)utils/parse_utils_bonus.c \
			$(BONUS_DIR)utils/render_utils_bonus.c $(BONUS_DIR)utils/validation_bonus.c \
			$(BONUS_DIR)parsing/file_validation_bonus.c $(BONUS_DIR)parsing/init_elem_bonus.c \
			$(BONUS_DIR)parsing/init_objs_bonus.c $(BONUS_DIR)parsing/init_cylinder_bonus.c \
			$(BONUS_DIR)parsing/read_file_bonus.c $(BONUS_DIR)render/camera_bonus.c \
			$(BONUS_DIR)render/intersect_bonus.c $(BONUS_DIR)render/lighting_bonus.c \
			$(BONUS_DIR)render/render_bonus.c mathlib/dotprod.c mathlib/norm.c \
			mathlib/normvec.c mathlib/vecadd.c mathlib/vecmag.c mathlib/vecsub.c \
			mathlib/vecscale.c mathlib/veccross.c mathlib/is_zero_vec.c \
			mathlib/vecsquared.c mathlib/veclen.c


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
