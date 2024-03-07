CC = cc
CFLAGS = -Wall -Werror -Wextra
INCLUDES = -I/opt/X11/include -Imlx
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

NAME = cub3d

SRCS = 	main.c							\
		input.c							\
		parse/parse.c					\
		parse/read_file.c				\
		parse/check_data.c				\
		parse/check_map.c				\
		parse/check_map_aux.c			\
		parse/gnl/get_next_line.c 		\
		parse/gnl/get_next_line_utils.c	\
		render/render.c					\
		render/raycast.c				\

		
#\\\\\\\\\\\\\\\\\\\\


OBJS = $(SRCS:.c=.o)

all: $(NAME) 

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(OBJS) $(MLX_FLAGS) -o $(NAME) -Llibft/ -lft

libft/libft.a:
	make -C libft/

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

clean:
	rm -rf $(OBJS)
	make -C libft/ clean

fclean: clean
	rm -rf $(NAME)
	make -C libft/ fclean

re: fclean $(NAME)
	make -C libft/ re

bonus: $(NAME)

.PHONY: clean fclean re