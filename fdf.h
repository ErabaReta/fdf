#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
//==
# define WINDOW_HEIGHT 500
# define WINDOW_WIDTH 500
//==
# define ROTATION_ANGLE 2
# define TRANSLATION_DISTENCE 3 
//=== buttons ====
# define ESC 53
# define Q 12
# define W 13
# define A 0
# define S 1
# define Z 6
# define X 7
# define E 14
# define R 15
# define D 2
# define F 3
# define C 8
# define V 9
# define UP_ARROW 126
# define DOWN_ARROW 125
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
	int	visibility;
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
	t_matrix	**shape_3d;
	t_matrix	**shape_2d;
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
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);

//=
int	ft_power(int nbr, int power);
int ft_abs(int nbr);
int calc_dist(int x, int y, t_2d_point point);
char	matrix_is_valid(t_matrix matrix);
//=
float	**new_value(int x, int y, int z, int dimension);
void	draw_map(t_vars *vars);
#endif