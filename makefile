CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME_SERVER = server
NAME_CLIENT = client

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): server.o
	$(CC) $(CFLAGS) server.o -o $(NAME_SERVER)

$(NAME_CLIENT): client.o
	$(CC) $(CFLAGS) client.o -o $(NAME_CLIENT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f server.o client.o 

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT) 

re: fclean all 

.PHONY: all clean fclean re