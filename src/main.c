/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:34:26 by nmanzini          #+#    #+#             */
/*   Updated: 2018/02/19 19:30:45 by nmanzini         ###   ########.fr       */
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

void	ray(t_data	*dt)
{
	int		i;
	int		j;
	float	ray[3];
	float		t;

	i = -1;
	while (++i < dt->sc->res[1])
	{
		j = -1;
		while (++j < dt->sc->res[0])
		{
			ray[0] = - (dt->sc->screen_s[0] / 2) + dt->sc->screen_s[0] / (dt->sc->res[0] - 1) * j;
			ray[1] = (dt->sc->screen_s[1] / 2) - dt->sc->screen_s[1] / (dt->sc->res[1] - 1) * i;
			ray[2] = dt->sc->screen_s[2];
			normalize (ray);
			rotate_v(ray, dt->sc->cam_a);

			t = 0;

			while (t < dt->sc->max_depth)
			{
				if (ray_sphere(ray,dt->sc->cam_p,dt->sc->x_sphere, t))
				{
					fill_pixel(dt->md,j,i,RED);
					break;
				}
				else if (ray_sphere(ray,dt->sc->cam_p,dt->sc->y_sphere, t))
				{
					fill_pixel(dt->md,j,i,GREEN);
					break;
				}
				else if (ray_sphere(ray,dt->sc->cam_p,dt->sc->z_sphere, t))
				{
					fill_pixel(dt->md,j,i,BLUE);
					break;
				}
				else if (ray_sphere(ray,dt->sc->cam_p,dt->sc->a_sphere, t))
				{
					fill_pixel(dt->md,j,i,WHITE);
					break;
				}
				else if (ray_sphere(ray,dt->sc->cam_p,dt->sc->sphere, t))
				{
					fill_pixel(dt->md,j,i,RED);
					break;
				}
				t += 0.1;
			}
			// print_vector(ray,ft_strjoin(ft_itoa(j),ft_itoa(i)));
		}
		// printf("\n");
	}
}

int	ray_sphere(float *vec, float *pos, float *sphere, float	t)
{
	
	float	p[3];
	float	s[5];

	p[0] = pos[0] + t * vec[0];
	p[1] = pos[1] + t * vec[1];
	p[2] = pos[2] + t * vec[2];

	s[0] = sphere[0] - p[0];
	s[1] = sphere[1] - p[1];
	s[2] = sphere[2] - p[2];
	s[3] = s[0] * s[0] + s[1] * s[1] + s[2] * s[2];
	s[4] = sphere[3] * sphere[3];
	if (s[3] <= s[4] + 0.05 && s[3] >= s[4] - 0.05)
		return (1);
	else
		return (0);
}

void	rotate_z(float degree,float *xp, float *yp, float *zp)
{
	float	tempx;
	float	tempy;

	tempx = *xp;
	tempy = *yp;
	*xp = tempx * cos(degree * PI_R) - tempy * sin(degree * PI_R);
	*yp = tempx * sin(degree * PI_R) + tempy * cos(degree * PI_R);
}

void	rotate_x(float degree, float *xp, float *yp, float *zp)
{
	float	tempy;
	float	tempz;

	tempy = *yp;
	tempz = *zp;
	*yp = tempy * cos(degree * PI_R) - tempz * sin(degree * PI_R);
	*zp = tempy * sin(degree * PI_R) + tempz * cos(degree * PI_R);
}

void	rotate_y(float degree, float *xp, float *yp, float *zp)
{
	float	tempx;
	float	tempz;

	tempx = *xp;
	tempz = *zp;
	*zp = tempz * cos(degree * PI_R) - tempx * sin(degree * PI_R);
	*xp = tempz * sin(degree * PI_R) + tempx * cos(degree * PI_R);
}


void	rotate_v(float *vec,float *angles)
{
	rotate_y(angles[1], &vec[0], &vec[1], &vec[2]);
	rotate_x(angles[0], &vec[0], &vec[1], &vec[2]);
	rotate_z(angles[2], &vec[0], &vec[1], &vec[2]);
}

// TODO:
// test with different resolutions
// lokk how to turn the camera and teh screen_s
// look hot to then move the camera
// see if would be usefull to malloc the rays

int		main(int ac, char **av)
{
	static t_data	*dt;
	static t_mlx	*md;

	dt = init_data(dt);
	dt->md = mlx_data_init_return(md);

	// img_square(dt->md, BLUE);


	print_vector(dt->sc->screen_s, "screen_s\n");

	ray(dt);
	mlx_put_image_to_window(dt->md->mlx,dt-> md->win, dt->md->ip->image, 0, 0);
	mlx_key_hook(dt->md->win, call_keys, dt);
	mlx_loop(dt->md->mlx);
	return (0);
}
