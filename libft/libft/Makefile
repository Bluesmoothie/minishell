.PHONY		: 	all clean fclean re norme

NAME		=	libft.a

#			GCC

CC			=	cc
CFLAGS		= 	-Wall -Wextra -Werror -MMD -MP -I $(INCLUDE)

#			COMMON

BUILD_DIR	=	.build/
SRC_DIR		=	src/
INCLUDE		=	include

#			SRC

SRC_FILES	= 	ft_isalpha 		\
				ft_isdigit 		\
				ft_isalnum 		\
				ft_isascii 		\
				ft_isprint 		\
				ft_strlen 		\
				ft_memset 		\
				ft_bzero 		\
				ft_memcpy 		\
				ft_memmove 		\
				ft_strlcpy 		\
				ft_strlcat 		\
				ft_toupper 		\
				ft_tolower 		\
				ft_strchr 		\
				ft_strrchr 		\
				ft_strncmp 		\
				ft_memchr		\
				ft_memcmp 		\
				ft_strnstr 		\
				ft_atoi 		\
				ft_calloc 		\
				ft_strdup 		\
				ft_substr 		\
				ft_strjoin 		\
				ft_strtrim 		\
				ft_split 		\
				ft_itoa 		\
				ft_strmapi 		\
				ft_striteri 	\
				ft_putchar_fd 	\
				ft_pustr_fd 	\
				ft_putendl_fd 	\
				ft_putnbr_fd 	\
				ft_lstnew 		\
				ft_lstadd_front \
				ft_lstsize 		\
				ft_lstlast 		\
				ft_lstadd_back 	\
				ft_lstdelone 	\
				ft_lstclear 	\
				ft_lstiter 		\
				ft_lstmap		\

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(BUILD_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 		= 	$(addprefix $(BUILD_DIR), $(addsuffix .d, $(SRC_FILES)))

#			RULES

all				: $(NAME)

$(NAME)			: $(BUILD_DIR) $(OBJ)
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

fclean			: clean
				rm -f $(NAME)

re				: fclean all