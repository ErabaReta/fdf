#include"fdf.h"

int	ft_power(int nbr, int power)
{
	int i = 0;
	int r = 1;
	while (i < power)
	{
		r *= nbr;
		i++;
	}
	return (r);
}

int ft_abs(int nbr)
{
	return (((nbr >= 0) - (nbr < 0 )) * nbr);
}

int calc_dist(int x, int y, t_2d_point point)
{
	int r;

	r = sqrt(ft_power(ft_abs(x - point.x), 2) + ft_power(ft_abs(y - point.y), 2));
	return (r);
}
char	matrix_is_valid(t_matrix matrix)
{
	int	i;
	int j;

	if (matrix.value == 0 || matrix.rows <= 0 || matrix.cols <= 0)
		return (0);
	i = 0;
	while (i < matrix.rows)
	{
		j = 0;
		while (j < matrix.cols)
		{
			if (matrix.value[i][j] == NULL)
				return (0);
		}
	}
	return (1);
}

long	matrix_dot_product(t_matrix matrix1, int row, t_matrix matrix2, int col)
{
	long	result;
	int		i;

	i = 0;
	result = 0;
	while (i < matrix1.cols && i < matrix2.rows)
	{
		result += matrix1.value[row][i] * matrix2.value[i][col];
		i++;
	}
	return (result);
}

t_matrix	matrix_mult(t_matrix matrix1, t_matrix matrix2)
{
	int			i;
	int			j;
	t_matrix	result;

	if (matrix_is_valid(matrix1) == 0 || matrix_is_valid(matrix2) == 0)
	{
		result.value = 0;
		return (result);
	}

	result.rows = matrix1.rows;
	result.cols = matrix2.cols;
	result.value = (int **)malloc(sizeof(int *) * result.rows);
	i = 0;
	while (i < result.rows)
	{
		result.value[i] = (int *)malloc(sizeof(int) * result.cols);
		i++;
	}
	i = 0;
	j = 0;
	while (i < result.rows)
	{
		j = 0;
		while (j < result.cols)
		{
			result.value[i][j] = matrix_dot_product(matrix1, i, matrix2, j);
			j++;
		}
		i++;
	}
	return (result);
}