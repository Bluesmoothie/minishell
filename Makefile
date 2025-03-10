.PHONY			:	clean fclean re all norme FORCE check test valgrind valgrindext

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

SRC_FILES		=	minishell					\
					builtins					\
					env							\
					env2						\
					init						\
					launch						\
					miniparse					\
					nf 							\
					parse						\
					pid_connect					\
					pipe_connect				\
					quotes						\
					quotes_chevron				\
					signal						\
					text						\
					utils						\
					builtins/cd					\
					builtins/echo				\
					builtins/env				\
					builtins/exit				\
					builtins/export				\
					builtins/pwd				\
					builtins/unset				\
					garbage/core				\
					garbage/double_core			\
					garbage/double				\
					garbage/exit				\
					garbage/interface			\
					garbage/split_mod			\
					pipes/parse					\
					pipes/multiple_pipes		\
					pipes/pipes					\
					pipes/treat					\
					pipes/treat_env				\
					pipes/signal_heredoc		\
					pipes/split_quotes			\
					types/mlist					\
					types/mlist2				\
					types/minishell				\
					types/pipes					\
					types/pipes2				\

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
					others			\
					pipes			\
					quotes			\

TESTS_GARBAGE	=	error.log					\
					file\ with\ spaces.txt 		\
					file.txt					\
					file1.txt					\
					file2.txt					\
					file3.txt					\
					heredoc.txt					\
					ls_output.txt				\
					non_existent_file.txt		\
					output.txt					\
					quoted_heredoc.txt			\
					checker						\
					checker.d 					\
					out.txt						\
					ref.txt						\
					\"file with spaces.txt\"	\

#			VALGRIND

VFLAGS			=	--leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes
VFLAGS			+=	--suppressions=ignore_readline.supp -s
VFLAGS			+=	--log-socket=127.0.0.1:4242

#			RULES

all				:	$(NAME)

$(NAME)			:	$(BUILD_DIR) $(OBJ) $(LIBFT_A)
				$(CC) $(CFLAGS) $(OBJ) $(LIBSFLAGS) -o $(NAME)

$(BUILD_DIR)	:
				mkdir -p $(BUILD_DIR)
				mkdir -p $(BUILD_DIR)builtins
				mkdir -p $(BUILD_DIR)garbage
				mkdir -p $(BUILD_DIR)pipes
				mkdir -p $(BUILD_DIR)types

$(BUILD_DIR)%.o	: 	$(SRC_DIR)%.c
				$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

$(LIBFT_A)		:	FORCE
				$(MAKE) -C $(LIBFT)

FORCE			:

check			:	test
				./checker
				rm	-f $(TESTS_GARBAGE)

test			:
				$(CC) $(CFLAGS) tests/tests.c tests/tests2.c $(LIBSFLAGS) -o checker

valgrind		:
				@echo "\033[31m\033[1mNow launch make valgrindext in another console"
				@echo "Errors will appear here CTRL+C to stop\033[0m"
				valgrind-listener 4242

valgrindext		:
				valgrind $(VFLAGS) ./$(NAME)

norme			:
				norminette $(SRC_DIR) include

clean			:
				$(MAKE) clean -C $(LIBFT)
				rm -rf $(BUILD_DIR)
				rm	-f $(TESTS_GARBAGE)

fclean			:	clean
				$(MAKE) fclean -C $(LIBFT)
				rm -f $(NAME)

re				:	fclean all