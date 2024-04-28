CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror  -O3 #-fsanitize=address
CFILES = main.c ft_split.c ft_strlen.c ft_memmove.c ft_atoi.c ft_math.c ft_strdup.c ft_strjoin.c rotate_shape.c ft_putstr_fd.c ft_strncmp.c ft_str_tolower.c file_parsing.c exiter.c data_parsing.c init.c renderer.c projection.c
OFILES = $(CFILES:.c=.o)
NAME = fdf

all : $(NAME)

$(NAME) : $(OFILES)
	$(CC)  $(OFILES) $(CFLAGS)  -lmlx -framework OpenGL -framework AppKit  -lm -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OFILES) $(BONUS_OFILES) $(BONUS_OFILES)

fclean : clean
	$(RM) $(NAME) $(BONUS_NAME)

re: fclean all