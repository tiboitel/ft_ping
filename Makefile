NAME				= ft_ping
SRCS				= main.c \
					  ping.c \
					  icmp.c \
					  socket.c \
					  utils.c
SRCSPATH			= ./srcs/
INCLUDES			= ./includes
CC					= clang
CFLAGS				= -Wall -Werror -Wextra -g
LFLAGS				= -lm
INCLUDES_O			= -I $(INCLUDES)
INCLUDES_C			= $(LFLAGS)
SRC					= $(addprefix $(SRCSPATH), $(SRCS))
OBJS				= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(INCLUDES_C) 

%.o: %.c
	$(CC) -o $@ $(INCLUDES_O) $(CFLAGS) $(SDL_HEADER) -c $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

