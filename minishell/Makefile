SRCS		=		src/minishell.c src/lst_func.c src/parser.c src/utils.c  src/cmd_built.c src/ft_echo.c src/ft_exit.c \
					src/ft_export.c src/execve.c src/ft_cd.c src/utils2.c src/pipe.c src/handle_file.c src/ft_unset.c \
					src/parser2.c src/add_func.c src/add_version.c src/exec_add.c src/mini_utils.c src/mini_utils2.c \
					src/mini_utils3.c src/file_add.c src/free_file.c

LIBFT		=		libft/libft.a

OBJS		=		$(SRCS:.c=.o)

NAME		=		minishell

CC			=		gcc

CFLAGS		=		-Wall -Wextra -Werror

RM			=		rm -rf

all:	$(NAME)
	

$(LIBFT):
			make bonus -C ./libft

$(NAME):	$(OBJS) $(LIBFT)
				$(CC) $(CFLAGS) -lreadline $(OBJS) libft/libft.a  -o $(NAME)
				@echo "<---------------OK--------------->"

clean:
				$(RM) $(OBJS)
				@echo "<-------------CLEAN------------->"

fclean:		clean
				$(RM) $(NAME)
			make fclean -C libft
			@echo "<-----------FULL_CLEAN----------->"

re:			fclean all

.PHONY:		all clean fclean re