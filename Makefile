.PHONY			:	clean fclean re all norme FORCE

NAME			=   minishell

#			GCC

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -MMD -MP $(INCLUDE)

#			COMMON

BUILD_DIR		=	.build/
SRC_DIR			=	src/
INCLUDE 		=	-Iinclude/ -I$(LIBFT)/include/

#			SRC

SRC_FILES		=	minishell	\
					functions	\
					functions2	\
					parse		\
					text		\
					utils		\

SRC 			= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 			= 	$(addprefix $(BUILD_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 			= 	$(addprefix $(BUILD_DIR), $(addsuffix .d, $(SRC_FILES)))

#			LIBFT

LIBFT		=	libft
LIBFT_A		=	$(LIBFT)/libft_ex.a

#			RULES

all				:	$(NAME)

$(NAME)			:	$(BUILD_DIR) $(OBJ) $(LIBFT_A)
				$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT) -lft_ex -lreadline -o $(NAME)

$(BUILD_DIR)	:
				mkdir -p $(BUILD_DIR)

$(BUILD_DIR)%.o	: 	$(SRC_DIR)%.c
				$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

$(LIBFT_A)		:	FORCE
				$(MAKE) -C $(LIBFT)

FORCE			:

norme			:
				norminette $(SRC_DIR) include

clean			:
				$(MAKE) clean -C $(LIBFT)
				rm -rf $(BUILD_DIR)

fclean			:	clean
				$(MAKE) fclean -C $(LIBFT)
				rm -f $(NAME)

re				:	fclean all