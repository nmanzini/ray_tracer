/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicola <nicola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:34:26 by nmanzini          #+#    #+#             */
/*   Updated: 2018/02/07 19:10:23 by nicola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

float	float_abs(float f)
{
	if (f < 0)
		return (-f);
	else
		return (f);
}

void	print_vector(float *vec, char *str)
{
	// print a 3 dim vector of floats and its length
	float len;

	len = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	printf("x %f, y %f, z %f len %f \"%s\"\n",vec[0], vec[1], vec[2], len, str);
}

void	normalize(float *vec)
{
	// normilizes a 3 dim array of ints.
	float len;

	len = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	vec[0] /= len;
	vec[1] /= len;
	vec[2] /= len;
}

void	ray(t_scn *sc)
{
	int i;
	int j;

	i = -1;
	while (++i < sc->res[1])
	{
		j = -1;
		while (++j < sc->res[0])
		{
			sc->ray_v[0] = - (sc->screen_s[0] / 2) + sc->screen_s[0] / (sc->res[0] - 1) * j;
			sc->ray_v[1] = (sc->screen_s[1] / 2) - sc->screen_s[1] / (sc->res[1] - 1) * i;
			sc->ray_v[2] = sc->screen_s[2];
						// normalize (sc->ray_v);

			print_vector(sc->ray_v,ft_strjoin(ft_itoa(j),ft_itoa(i)));
		}
		printf("\n");
	}

}


// TODO:
// test with different resolutions
// lokk how to turn the camera and teh screen_s
// see if would be usefull to malloc the rays

int		main(int ac, char **av)
{
	static t_data	*dt;
	static t_mlx	*md;

	dt = init_data(dt);
	// dt->md = mlx_data_init_return(md);

	// img_square(dt->md, BLUE);


	print_vector(dt->sc->screen_s, "screen_s\n");

	ray(dt->sc);
	// mlx_key_hook(dt->md->win, call_keys, dt);
	// mlx_loop(dt->md->mlx);
	return (0);
}
