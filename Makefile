# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 16:28:46 by tiboitel          #+#    #+#              #
#    Updated: 2018/08/25 18:26:22 by tiboitel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_ping
HDS			=	./includes
SRCS		=	main.c
CC 			=	gcc
CCFLAGS		=	-Wall -Werror -Wextra
OBJS		=	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME): 	$(OBJS)
	$(CC)  -o $(NAME) $(OBJS) $(LFLAGS) 

%.o:%.c
	$(CC) $(CCFLAGS) -c $< -o $@ -I $(HDS)

clean:
	rm -f $(OBJ)

fclean: 	clean
	rm -f $(NAME)

re: 		fclean all

.PHONY: all clean fclean re
