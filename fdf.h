#ifndef FDF_H
# define FDF_H

#include <mlx.h>
#include <stdlib.h>
#include <fcntl.h>
#include<math.h>
#include "get_next_line/get_next_line.h"

//===========================
typedef struct	s_img_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img_data;
//===========================
typedef struct s_3d_point
{
	float	x;
	float	y;
	float	z;
}				t_3d_point;
//===========================
typedef struct	s_2d_point
{
	int	x;
	int	y;
}				t_2d_point;
//===========================
typedef struct	s_matrix {
	float		**value;
	int		rows;
	int		cols;
}				t_matrix;
//===========================
typedef struct	s_vars {
	int			height;
	int			width;
	void		*mlx;
	void		*win;
	t_img_data	data;
	t_matrix	**shape;
}				t_vars;
//===========================
typedef struct s_camera	{
	t_3d_point pov;
	t_3d_point plane;
}				t_camera;
//===========================
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*free_all(char **ptr, int i);
int	ft_atoi(const char *str);

//=
int	ft_power(int nbr, int power);
int ft_abs(int nbr);
int calc_dist(int x, int y, t_2d_point point);
char	matrix_is_valid(t_matrix matrix);

#endif