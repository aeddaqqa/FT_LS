# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aeddaqqa <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/01 13:04:21 by aeddaqqa          #+#    #+#              #
#    Updated: 2019/11/29 01:17:27 by aeddaqqa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC = main.c aff_fs.c aff_l.c directory.c free.c ft_ls1.c gest_param.c\
	sort1.c sort2.c sort3.c stock.c tools1.c tools2.c tools3.c
OBJ = $(SRC:.c=.o)

CC = gcc

INC = ft_ls.h

CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ) $(INC) 
	@make -C libft
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME) -I $(INC) libft/libft.a

clean :
	@make clean -C libft
	@rm -rf $(OBJ)
fclean : clean
	@make fclean -C libft
	@rm -rf $(NAME)
re : fclean all
