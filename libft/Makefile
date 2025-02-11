.PHONY		: 	all clean fclean re FORCE norme

NAME		=	libft_ex.a

#			COMMON

BUILD_DIR	=	.build/
FT_PRINTF 	=	ft_printf/
GNL 		=	get_next_line/
FT 			=	libft/

#			SRC

LIBFTPRINTF =	$(FT_PRINTF)libftprintf.a
LIBGNL		=	$(GNL)libgnl.a
LIBFT		=	$(FT)libft.a

#			RULES

all				: $(NAME)

$(NAME)			: $(LIBFTPRINTF) $(LIBGNL) $(LIBFT) $(BUILD_DIR)
				cp $(LIBFTPRINTF) $(BUILD_DIR)
				cp $(LIBGNL) $(BUILD_DIR)
				cp $(LIBFT) $(BUILD_DIR)
				ar -x $(BUILD_DIR)libftprintf.a --output=$(BUILD_DIR)
				ar -x $(BUILD_DIR)libgnl.a --output=$(BUILD_DIR)
				ar -x $(BUILD_DIR)libft.a --output=$(BUILD_DIR)
				ar -rcs $(NAME) $(BUILD_DIR)*.o

$(BUILD_DIR)	:
				mkdir -p $(BUILD_DIR)

$(LIBFTPRINTF)	:	FORCE
				$(MAKE) -C $(FT_PRINTF)

$(LIBGNL)		:	FORCE
				$(MAKE) -C $(GNL)

$(LIBFT)		:	FORCE
				$(MAKE) -C $(FT)

FORCE			:

norme			:
				norminette include
				$(MAKE) -C $(FT_PRINTF) norme
				$(MAKE) -C $(GNL) norme
				$(MAKE) -C $(FT) norme

clean			:
				$(MAKE) -C $(FT_PRINTF) clean
				$(MAKE) -C $(GNL) clean
				$(MAKE) -C $(FT) clean
				rm -rf $(BUILD_DIR)

fclean			: clean
				$(MAKE) -C $(FT_PRINTF) fclean
				$(MAKE) -C $(GNL) fclean
				$(MAKE) -C $(FT) fclean
				rm -f $(NAME)

re				: fclean all