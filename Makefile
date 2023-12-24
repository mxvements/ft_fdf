CC=			cc

CFLAGS=		-Wall -Wextra -Werror -g3

MLX_MAC=	-Lmlx -lmlx -framework OpenGL -framework AppKit

MLX_LINUX=	-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

NAME=		fdf

###############################################################################

#HRDS=

SRCS=		main.c

SRCS_DIR=	./srcs/

###############################################################################

LIBFT_DIR=	libft

LIBFT=		./libft/libft.a

###############################################################################

GNL_DIR=	./gnl/

GNL_SRCS=	get_next_line.c \
			get_next_line_utils.c

###############################################################################

MY_OBJECTS=$(addprefix $(SRCS_DIR), ${SRCS:%.c=%.o})

MY_OBJECTS+=$(addprefix $(GNL_DIR), ${GNL_SRCS:%.c=%.o})

###############################################################################

all: $(NAME)

$(NAME): $(MY_OBJECTS)
	make extra -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(MY_OBJECTS) $(LIBFT) $(MLX_LINUX) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(MY_OBJECTS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

norminette:
	norminette $(MY_SOURCES)

re: fclean all