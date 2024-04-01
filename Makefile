# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/21 05:33:19 by jbettini          #+#    #+#              #
#    Updated: 2024/03/25 17:19:43 by jbettini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror -g
RM 			= 	rm -f
NAME		=	lem-in
SRC			=	$(wildcard srcs/*.c) 
LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a

TXT_RED = "\033[1;31m"
TXT_GREEN = "\033[1;32m"
TXT_YELLOW = "\033[1;33m"
TXT_BLUE = "\033[1;34m"
TXT_MAGENTA = "\033[1;35m"
TXT_CYAN = "\033[1;36m"
FANCY_RESET = "\033[0m"

OBJ		=	$(SRC:.c=.o)

%.o : %.c
	@printf  $(TXT_YELLOW)"Compilation du projet : "$(TXT_BLUE)"$<\n"$(FANCY_RESET)
	@$(CC) $(CFLAGS) -o $@ -c $< 

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) -lft 

	#-g -fsanitize=address
clean:
	make -C $(LIBFT_DIR) fclean
	@printf  $(TXT_RED)"Nettoyage du projet\n"$(FANCY_RESET)
	@$(RM) -rf $(OBJ) > /dev/null 2>&1

fclean: clean
	@printf  $(TXT_RED)"Suppression de l'executable\n"$(FANCY_RESET)
	@$(RM) -rf $(NAME) > /dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re
