CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror 
CFILES = main.c ft_split.c ft_strlen.c ft_memmove.c ft_atoi.c ft_math.c ft_strdup.c ft_strjoin.c
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