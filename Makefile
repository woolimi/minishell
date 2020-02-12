SRCS_minishell = srcs/main.c

SRCS_libft =

SRCS = ${SRCS_minishell} ${SRCS_libft}

INCL = -Iincludes/

OBJS = ${SRCS:.c=.o}

NAME = minishell

FLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : ${OBJS}
		gcc ${FLAGS} -o $(NAME) ${OBJS} 

.c.o : ${SRCS}
		gcc ${FLAGS} -c ${INCL} $< -o ${<:.c=.o}
clean :
		rm -f ${OBJS}

fclean : clean
		rm -f $(NAME)

re : fclean
		make all

.PHONY: all clean fclean re
