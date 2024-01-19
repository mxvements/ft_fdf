CC=			cc

CFLAGS=		-Wall -Wextra -Werror -g3

CFLAG_SAN=	-fsanitize=address

MLX_MAC=	-Lmlx -lmlx -framework OpenGL -framework AppKit 

MLX_LINUX=	-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

NAME=		fdf

###############################################################################

#HRDS=

SRCS=		main.c \
			automata.c \
			automata_aux.c \
			fdf_aux.c \
			fdf_keyhooks1.c \
			fdf_keyhooks2.c \
			fdf_mousehooks.c \
			fdf_putlines.c \
			fdf_putcolor.c \
			map_init1.c \
			map_init2.c \
			map_change.c \
			map_free.c \
			matrix_aux1.c \
			view_aux1.c \
			view_aux2.c \
			pt_aux.c \
			keys_aux.c

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

all: $(NAME) mac

$(NAME): $(MY_OBJECTS)
	make extra -C $(LIBFT_DIR)

mac:
	$(CC) $(CFLAGS) $(MY_OBJECTS) $(LIBFT) $(MLX_MAC) -o $(NAME)

linux:
	$(CC) $(CFLAGS) $(MY_OBJECTS) $(LIBFT) $(MLX_LINUX) -o $(NAME)

sanitize: fclean $(NAME)
	$(CC) $(CFLAGS) $(CFLAG_SAN) $(MY_OBJECTS) $(LIBFT) $(MLX_MAC) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(MY_OBJECTS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

norminette:
	norminette $(MY_SOURCES)

re: fclean all
