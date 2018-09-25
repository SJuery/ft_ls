# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjuery <sjuery@student.42.us.org>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/31 11:28:46 by sjuery            #+#    #+#              #
#    Updated: 2018/09/24 17:47:11 by sjuery           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= ft_ls

SRC		= 	srcs/ft_ls.c \
			srcs/others.c \

OBJ 	= $(SRC:.c=.o)
CFLAGS	= -Wall -Wextra -Werror \
			#-fsanitize=address -fsanitize=undefined
			-O3 -march=native -flto=thin

.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
	printf '\033[31m[...] %s\n\033[0m' "Creating LS Command"
	make -C srcs/libft/
	gcc $(CFLAGS) srcs/libft/libft.a $^ -o $(NAME)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Created LS Command"

clean:
	printf '\033[31m[...] %s\n\033[0m' "Cleaning LS Command"
	make fclean -C srcs/libft/
	/bin/rm -f srcs/*.o
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Cleaned LS Command"

fclean: clean
	make fclean -C srcs/libft/
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all test
