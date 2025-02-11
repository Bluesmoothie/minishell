.PHONY		: 	all clean fclean re norme

NAME		=	libft.a

#			GCC

CC			=	cc
CFLAGS		= 	-Wall -Wextra -Werror -MMD -MP -I $(INCLUDE)

#			COMMON

BUILD_DIR	=	.build/
SRC_DIR		=	src/
INCLUDE		=	include/

#			SRC

SRC_FILES	=	char/ft_isalnum 		\
 				char/ft_isalpha 		\
				char/ft_isascii 		\
				char/ft_isdigit 		\
				char/ft_isprint 		\
				char/ft_tolower 		\
				char/ft_toupper 		\
				list/ft_lstadd_back 	\
				list/ft_lstadd_front	\
				list/ft_lstclear		\
				list/ft_lstdelone		\
				list/ft_lstiter			\
				list/ft_lstlast			\
				list/ft_lstmap			\
				list/ft_lstnew			\
				list/ft_lstsize			\
				memory/ft_bzero 		\
				memory/ft_calloc 		\
				memory/ft_memchr		\
				memory/ft_memcmp 		\
				memory/ft_memcpy 		\
				memory/ft_memmove 		\
				memory/ft_memset 		\
				string/ft_atoi 			\
				string/ft_free_split	\
				string/ft_itoa 			\
				string/ft_split 		\
				string/ft_strcat		\
				string/ft_strchr 		\
				string/ft_strcmp		\
				string/ft_strdup 		\
				string/ft_strfcat		\
				string/ft_striteri 		\
				string/ft_strjoin 		\
				string/ft_strlcat 		\
				string/ft_strlcpy 		\
				string/ft_strlen 		\
				string/ft_strmapi 		\
				string/ft_strncmp 		\
				string/ft_strnstr 		\
				string/ft_strrchr 		\
				string/ft_strtrim 		\
				string/ft_substr 		\
				string/ft_uitoa			\
				write/ft_pustr_fd 		\
				write/ft_putchar_fd 	\
				write/ft_putendl_fd 	\
				write/ft_putnbr_fd 		\

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(BUILD_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 		= 	$(addprefix $(BUILD_DIR), $(addsuffix .d, $(SRC_FILES)))

#			RULES

all				: $(NAME)

$(NAME)			: $(BUILD_DIR) $(OBJ)
				ar -rcs $(NAME) $(OBJ)

$(BUILD_DIR)	:
				mkdir -p $(BUILD_DIR)/char
				mkdir -p $(BUILD_DIR)/list
				mkdir -p $(BUILD_DIR)/memory
				mkdir -p $(BUILD_DIR)/string
				mkdir -p $(BUILD_DIR)/write

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