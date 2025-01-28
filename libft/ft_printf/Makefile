.PHONY		:	all clean fclean re norme

NAME		=	libftprintf.a

#			GCC

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -MMD -MP -I $(INCLUDE)

#			COMMON

BUILD_DIR	=	.build/
SRC_DIR		=	src/
INCLUDE		=	include/

#			SRC

SRC_FILES	=	libftprintf	\
				printer_1	\
				printer_2	\
				hex			\
				ft_uitoa	\

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(BUILD_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 		= 	$(addprefix $(BUILD_DIR), $(addsuffix .d, $(SRC_FILES)))

#			RULES

all				:	$(NAME)

$(NAME)			:	$(BUILD_DIR) $(OBJ)
				ar -rcs $(NAME) $(OBJ)

$(BUILD_DIR)	:
				mkdir -p $(BUILD_DIR)

$(BUILD_DIR)%.o	: $(SRC_DIR)%.c
				$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

norme			:
				norminette $(SRC) $(INCLUDE)

clean			:
				rm -rf $(BUILD_DIR)

fclean			:	clean
				rm -f $(NAME)

re				:	fclean all
