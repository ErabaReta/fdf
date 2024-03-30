#ifndef FDF_H
# define FDF_H

#include <mlx.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line/get_next_line.h"

//===========================
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;
//===========================
typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}	t_point;
//===========================
typedef struct	s_vars {
	void	*mlx;
	void	*win;
	t_data	*data;
}				t_vars;
//===========================
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*free_all(char **ptr, int i);
int	ft_atoi(const char *str);

#endif