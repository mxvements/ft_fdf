CC=			cc

CFLAGS=		-Wall -Wextra -Werror -g3

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
	$(CC) $(CFLAGS) $(MY_OBJECTS) $(LIBFT) -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(MY_OBJECTS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -rf $(NAME)

norminette:
	norminette $(MY_SOURCES)

re: fclean all