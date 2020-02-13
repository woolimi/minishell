NAME = minishell
FLAGS = -Wall -Wextra -Werror
SRC_NAME = main.c

SRC_PATH = ./srcs
SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ_PATH = ./obj
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

INC_LINK = -I./includes
LIBFT = -L./lib/libft -lft
all : $(NAME)

$(NAME) : $(OBJ) libft
	gcc $(FLAGS) $(OBJ) $(INC_LINK) $(LIBFT) -o $(NAME) 

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	gcc $(CFLAGS) $(INC_LINK) -o $@ -c $<
	
# libft compile
libft :
	@$(MAKE) -C ./lib/libft all

clean :
	@$(MAKE) -C ./lib/libft clean
	@rm -rf ./obj

fclean :
	@$(MAKE) -C ./lib/libft fclean
	@rm -rf ./obj $(NAME)

re : fclean all

.PHONY: all clean fclean re
