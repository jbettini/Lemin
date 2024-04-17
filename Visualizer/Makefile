# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbettini <jbettini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/31 01:47:44 by jbettini          #+#    #+#              #
#    Updated: 2024/04/17 04:23:43 by jbettini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -O -fPIE `sdl2-config --cflags` 
# -pie
LFLAGS = `sdl2-config --libs`

RM = rm -f
NAME = visu-hex
SRC_DIR := ../srcs

M_SRC := $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
B_SRC = $(wildcard srcs/*.c)

SRC = $(B_SRC) $(M_SRC)
OBJ = $(SRC:.c=.o)
LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

%.o : %.c
	@printf  "$(TXT_YELLOW)Compilation du projet : $(TXT_BLUE)$<\n$(FANCY_RESET)"
	@$(CC) $(CFLAGS) -o $@ -c $< 

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(LFLAGS) -L$(LIBFT_DIR) -lft 

clean:
	make -C $(LIBFT_DIR) fclean
	@printf  "$(TXT_RED)Nettoyage du projet\n$(FANCY_RESET)"
	@$(RM) $(OBJ)

fclean: clean
	@printf  "$(TXT_RED)Suppression de l'exécutable\n$(FANCY_RESET)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
