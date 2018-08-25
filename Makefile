# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 16:28:46 by tiboitel          #+#    #+#              #
#    Updated: 2018/08/25 20:25:53 by tiboitel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_ping
HDS			=	./includes
SRCPATH		= 	./srcs/
SRCS		=	main.c \
				getopt.c
CC 			=	gcc
CCFLAGS		=	-Wall -Werror -Wextra
LFLAGS		= 	-L ./libft -lft
INCLUDES_O	= 	-I ./libft/includes
OBJS		=	$(addprefix $(SRCPATH), $(SRCS:.c=.o))

all:		$(NAME)

$(NAME): 	$(OBJS)
	$(CC)  -o $(NAME) $(OBJS) $(LFLAGS) 

%.o:%.c libft/libft.a
	$(CC) $(CCFLAGS) -c $< -o $@ -I $(HDS) $(INCLUDES_O)

libft/libft.a:
	make -C ./libft

clean:
	make -C ./libft clean
	rm -f $(OBJ)

fclean: 	clean
	make -C ./libft fclean
	rm -f $(NAME)

re: 		fclean all
	make -C ./libft re

.PHONY: all clean fclean re
