#include"fdf.h"

// int	ft_power(int nbr, int power)
// {
// 	int i = 0;
// 	int r = 1;
// 	while (i < power)
// 	{
// 		r *= nbr;
// 		i++;
// 	}
// 	return (r);
// }

int ft_abs(int nbr)
{
	return (((nbr >= 0) - (nbr < 0 )) * nbr);
}

// int calc_dist(int x, int y, t_2d_point point)
// {
// 	int r;

// 	r = sqrt(ft_power(ft_abs(x - point.x), 2) + ft_power(ft_abs(y - point.y), 2));
// 	return (r);
// }


float	ft_min(float nbr1, float nbr2)
{
	if (nbr1 >= nbr2)
		return (nbr2);
	return (nbr1);
}

float	ft_max(float nbr1, float nbr2)
{
	if (nbr1 >= nbr2)
		return (nbr1);
	return (nbr2);
}
