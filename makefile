CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -O3
SRC = src/data_parsing.c src/exiter.c src/ft_atoi.c src/ft_math.c src/ft_memmove.c src/ft_putstr_fd.c src/ft_split.c src/ft_str_tolower.c src/ft_strdup.c src/ft_strjoin.c src/ft_strlen.c src/ft_strncmp.c src/rotate_shape.c
CFILES = events_handling.c file_parsing.c init.c main.c projection.c renderer.c
CFILES_BONUS = $(addprefix _bonus/,$(CFILES:.c=_bonus.c))
OFILES = $(CFILES:.c=.o) $(SRC:.c=.o)
OFILES_BONUS = $(CFILES_BONUS:.c=.o) $(SRC:.c=.o)
NAME = fdf
NAME_BONUS = fdf_bonus
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit  -lm
INCLUDES = -I./ -I_bonus

all : $(NAME)

bonus : $(NAME_BONUS)

$(NAME) : $(OFILES)
	$(CC)  $(OFILES) $(CFLAGS) $(INCLUDES) $(MLX_FLAGS)  -o $(NAME)

$(NAME_BONUS) : $(OFILES_BONUS)
	$(CC)  $(OFILES_BONUS) $(CFLAGS) $(INCLUDES)  $(MLX_FLAGS) -o $(NAME_BONUS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES)  -c $< -o $@

clean :
	$(RM) $(OFILES) $(OFILES_BONUS) $(SRC:.c=.o)

fclean : clean
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

re: fclean all