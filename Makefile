.PHONY			:	clean fclean re all norme FORCE check

NAME			=   minishell

#			GCC

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
CFLAGS			+=	-MMD -MP
CFLAGS			+=	$(INCLUDE)
CFLAGS			+=	-g3
LIBSFLAGS		=	-L$(LIBFT) -lft_ex -lreadline

#			COMMON

BUILD_DIR		=	.build/
SRC_DIR			=	src/
INCLUDE 		=	-Iinclude/ -I$(LIBFT)/include/

#			SRC

SRC_FILES		=	minishell		\
					env				\
					init			\
					launch			\
					miniparse		\
					parse			\
					pipes			\
					text			\
					builtins/cd		\
					builtins/echo	\
					builtins/env	\
					builtins/export	\
					builtins/pwd	\
					builtins/unset	\
					types/mlist		\
					types/mlist2	\
					types/minishell	\
					types/pipes		\
					types/pipes2	\

SRC 			= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 			= 	$(addprefix $(BUILD_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 			= 	$(addprefix $(BUILD_DIR), $(addsuffix .d, $(SRC_FILES)))

#			LIBFT

LIBFT			=	libft
LIBFT_A			=	$(LIBFT)/libft_ex.a

#			TESTS

TESTS_DIR		=	tests/
TESTS			=	$(addprefix $(TESTS_DIR), $(addsuffix .sh, $(TESTS_FILES)))
TESTS_FILES		=	chevron			\
					echo			\
					env				\
					launch_tests	\
					others			\
					pipes			\
					quotes			\

TESTS_GARBAGE	=	error.log				\
					file\ with\ spaces.txt 	\
					file.txt				\
					file1.txt				\
					file2.txt				\
					file3.txt				\
					heredoc.txt				\
					ls_output.txt			\
					non_existent_file.txt	\
					output.txt				\
					quoted_heredoc.txt		\
					minishellr				\
					bashr					\

#			RULES

all				:	$(NAME)

$(NAME)			:	$(BUILD_DIR) $(OBJ) $(LIBFT_A)
				$(CC) $(CFLAGS) $(OBJ) $(LIBSFLAGS) -o $(NAME)

$(BUILD_DIR)	:
				mkdir -p $(BUILD_DIR)
				mkdir -p $(BUILD_DIR)builtins
				mkdir -p $(BUILD_DIR)types

$(BUILD_DIR)%.o	: 	$(SRC_DIR)%.c
				$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

$(LIBFT_A)		:	FORCE
				$(MAKE) -C $(LIBFT)

FORCE			:

norme			:
				norminette $(SRC_DIR) include

check			:
				chmod +x $(TESTS)
				bash tests/launch_tests.sh
				rm	-f $(TESTS_GARBAGE)

clean			:
				$(MAKE) clean -C $(LIBFT)
				rm -rf $(BUILD_DIR)
				rm	-f $(TESTS_GARBAGE)

fclean			:	clean
				$(MAKE) fclean -C $(LIBFT)
				rm -f $(NAME)

re				:	fclean all