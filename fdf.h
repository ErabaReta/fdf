#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include <limits.h>
//==
# define WINDOW_HEIGHT 1000
# define WINDOW_WIDTH 1000
//==
# define ROTATION_ANGLE 1
# define TRANSLATION_DISTENCE ((ft_max(vars->width ,vars->height ) / 13) + 1)
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
# define SPACE 49
# define ENTER 36
# define DELETE 51
//=== colors ===
# define WHITE 0xffffff
# define BROWN 0xCC6600
# define RED 0xff0000
# define GREEN 0x009900
# define CYAN 0x00ffff
# define BLUE 0x0000ff
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
	int		color;
}				t_3d_point;
//===========================
typedef struct	s_2d_point
{
	int	x;
	int	y;
	int	color;
}				t_2d_point;
//===========================
typedef struct	s_vars {
	int			height;
	int			width;
	int			top_z;
	float		xangle;
	float		yangle;
	float		zangle;
	int			xtranslation;
	int			ytranslation;
	int			ztranslation;
	float		zoom;
	char		projection;
	char		orthognal_type;	
	char		coords_sestym;
	void		*mlx;
	void		*win;
	t_img_data	data;
	t_3d_point	**shape_3d;
}				t_vars;
//===========================
char	**ft_split(char const *s, char c);
size_t	count_words(char const *s, char c);
size_t	ft_strlen(const char *s);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*free_all(char **ptr, int i);
long	ft_atoi(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
void	ft_putstr_fd(char *s, int fd);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_str_tolower(char *str);
//=
int	check_height_width(char **chars_map, int *height, int *width);
int	check_file_name(char *file);
char **map_file_to_chars(char *file);
//=
int	ft_power(int nbr, int power);
int ft_abs(int nbr);
int calc_dist(int x, int y, t_2d_point point);
// char	matrix_is_valid(t_matrix matrix);
//=
t_3d_point rotateX_point(t_3d_point point, float angle);
t_3d_point rotateY_point(t_3d_point point, float angle);
t_3d_point rotateZ_point(t_3d_point point, float angle);
void	rotate_shape(t_vars *vars, float angle, char axis);
//=
int	new_value(int x, int y, char *str, t_3d_point *value);
void	draw_map(t_vars *vars);
float	ft_max(float nbr1, float nbr2);
t_3d_point	get_coords(t_vars *vars, int i, int j);
t_vars	*get_vars(void);
void	init_shape(t_vars *vars);
//=
void fdf_exiter(t_vars *vars);
#endif