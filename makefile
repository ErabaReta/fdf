CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
CFILES = main.c ft_split.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c ft_strlen.c ft_memmove.c ft_atoi.c
OFILES = $(CFILES:.c=.o)
NAME = fdf

all : $(NAME)

$(NAME) : $(OFILES)
	$(CC)  $(OFILES) $(CFLAGS)  -lmlx -framework OpenGL -framework AppKit -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OFILES) $(BONUS_OFILES) $(BONUS_OFILES)

fclean : clean
	$(RM) $(NAME) $(BONUS_NAME)

re: fclean all