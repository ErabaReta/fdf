#include "fdf.h"

void fdf_exiter(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->height)
	{
		free(vars->shape_3d[i]);
		i++;
	}
	free(vars->shape_3d);
	system("leaks fdf");
	exit(0);
}