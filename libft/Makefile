# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/03 16:28:46 by tiboitel          #+#    #+#              #
#    Updated: 2017/06/19 19:22:02 by tiboitel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
HDS			=	./includes
SRC			=	ft_strdelc.c \
				ft_arrlen.c \
				ft_creplace.c \
				ft_bzero.c \
				ft_memset.c \
				ft_strsplit.c \
				ft_memcpy.c \
				ft_memccpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memdel.c \
				ft_memalloc.c \
				ft_memmove.c \
				ft_strnew.c \
				ft_strdel.c \
				ft_strclr.c \
				ft_strlen.c \
				ft_intlen.c \
				ft_striter.c \
				ft_striteri.c \
				ft_strmap.c \
				ft_strmapi.c \
				ft_strequ.c \
				ft_strnequ.c \
				ft_strsub.c \
				ft_strjoin.c \
				ft_strfjoin.c \
				ft_strtrim.c \
				ft_strcpy.c \
				ft_strncpy.c \
				ft_strdup.c \
				ft_strndup.c \
				ft_strcmp.c \
				ft_strncmp.c \
				ft_strstr.c \
				ft_strnstr.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strcat.c \
				ft_strncat.c \
				ft_strlcat.c \
				ft_atoi.c \
				ft_itoa.c \
				ft_isdigit.c \
				ft_isalpha.c \
				ft_isalnum.c \
				ft_isprint.c \
				ft_isascii.c \
				ft_isprime.c \
				ft_iswhitespace.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_putchar.c \
				ft_putnchar.c \
				ft_putstr.c \
				ft_putendl_fd.c \
				ft_putnbr.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putnbr_fd.c \
				ft_putendl.c \
				ft_lstnew.c \
				ft_lstdelone.c \
				ft_lstdel.c \
				ft_lstadd.c \
				ft_lstpushback.c \
				ft_lstiter.c \
				ft_lstmap.c \
				ft_lstlen.c \
				ft_lstsort.c \
				ft_stcknew.c \
				ft_stckpop.c \
				ft_stckpush.c \
				ft_isstckempty.c \
				ft_isstckfull.c \
				ft_sqrt.c \
				ft_strrev.c \
				ft_getenv.c
CC 			=	gcc
CCFLAGS		=	-Wall -Werror -Wextra
OBJ			=	$(SRC:.c=.o)

all:		$(NAME)

$(NAME): 	$(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o:%.c
	$(CC) $(CCFLAGS) -c $< -o $@ -I $(HDS)

clean:
	rm -f $(OBJ)

fclean: 	clean
	rm -f $(NAME)

re: 		fclean all		
