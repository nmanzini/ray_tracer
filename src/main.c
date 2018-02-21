/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:34:26 by nmanzini          #+#    #+#             */
/*   Updated: 2018/02/21 19:14:38 by nmanzini         ###   ########.fr       */
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

void	update_ray(int *res, int *pixel, float *scr_s, float *ray)
{	
	ray[0] = - (scr_s[0] / 2) + (scr_s[0] / (res[0] - 1) * pixel[0]);
	ray[1] = + (scr_s[1] / 2) - (scr_s[1] / (res[1] - 1) * pixel[1]);
	ray[2] = + (scr_s[2]);
}

void	update_intersection(float t, float *ray_v, float *cam_p, float *int_p)
{
	int_p[0] = cam_p[0] + t * ray_v[0];
	int_p[1] = cam_p[1] + t * ray_v[1];
	int_p[2] = cam_p[2] + t * ray_v[2];
}

void	update_normal(float *int_p, float *cent, float *int_n)
{
	int_n[0] = int_p[0] - cent[0];
	int_n[1] = int_p[1] - cent[1];
	int_n[2] = int_p[2] - cent[2];
}

void	update_lig_v(float *lig_p, float *int_p, float *lig_v)
{
	lig_v[0] = lig_p[0] - int_p[0];
	lig_v[1] = lig_p[1] - int_p[1];
	lig_v[2] = lig_p[2] - int_p[2];
}

void	update_color(float *int_n, float *lig_v, unsigned int *color)
{
	float			projection;

	projection = int_n[0] * lig_v [0] + int_n[1] * lig_v [1] + int_n[2] * lig_v [2];

	*color = (projection + 1) / 2 * 255;

}

void ray_trace(t_data	*dt)
{
	float			ray[3];
	float			t;

	cam_data_update(dt->ca);
	dt->px->pix_p[1] = -1;
	while (++dt->px->pix_p[1] < dt->ca->res[1])
	{
		dt->px->pix_p[0] = -1;
		while (++dt->px->pix_p[0] < dt->ca->res[0])
		{
			update_ray(dt->ca->res,dt->px->pix_p,dt->ca->scr_s,dt->px->ray_v);
			// normalize (dt->px->ray_v);
			rotate_v(dt->px->ray_v, dt->ca->cam_a);

			t = 0;

			while (t < dt->ca->max_depth)
			{
				if (ray_sphere(dt->px->ray_v,dt->ca->cam_p,dt->sc->x_sphere, t))
				{
					update_intersection(t, dt->px->ray_v, dt->ca->cam_p, dt->px->int_p);
					update_normal(dt->px->int_p, dt->sc->x_sphere, dt->px->int_n);
					update_lig_v(dt->sc->light,dt->px->int_p,dt->px->lig_v);
					update_color(dt->px->int_n,dt->px->lig_v,&dt->px->color);
					fill_pixel_res(dt,dt->px->pix_p[0],dt->px->pix_p[1],dt->px->color);
					break;
				}
				else if (ray_sphere(dt->px->ray_v,dt->ca->cam_p,dt->sc->y_sphere, t))
				{
					update_intersection(t, dt->px->ray_v, dt->ca->cam_p, dt->px->int_p);
					update_normal(dt->px->int_p, dt->sc->y_sphere, dt->px->int_n);
					update_lig_v(dt->sc->light,dt->px->int_p,dt->px->lig_v);
					update_color(dt->px->int_n,dt->px->lig_v,&dt->px->color);
					fill_pixel_res(dt,dt->px->pix_p[0],dt->px->pix_p[1],dt->px->color);
					break;
				}
				else if (ray_sphere(dt->px->ray_v,dt->ca->cam_p,dt->sc->z_sphere, t))
				{
					update_intersection(t, dt->px->ray_v, dt->ca->cam_p, dt->px->int_p);
					update_normal(dt->px->int_p, dt->sc->z_sphere, dt->px->int_n);
					update_lig_v(dt->sc->light,dt->px->int_p,dt->px->lig_v);
					update_color(dt->px->int_n,dt->px->lig_v,&dt->px->color);
					fill_pixel_res(dt,dt->px->pix_p[0],dt->px->pix_p[1],dt->px->color);
					break;
				}
				else if (ray_sphere(dt->px->ray_v,dt->ca->cam_p,dt->sc->a_sphere, t))
				{
					update_intersection(t, dt->px->ray_v, dt->ca->cam_p, dt->px->int_p);
					update_normal(dt->px->int_p, dt->sc->a_sphere, dt->px->int_n);
					update_lig_v(dt->sc->light,dt->px->int_p,dt->px->lig_v);
					update_color(dt->px->int_n,dt->px->lig_v,&dt->px->color);
					fill_pixel_res(dt,dt->px->pix_p[0],dt->px->pix_p[1],dt->px->color);
					break;
				}
				// else if (ray_sphere(dt->px->ray_v,dt->ca->cam_p,dt->sc->y_sphere, t))
				// {
				// 	fill_pixel_res(dt,dt->px->pix_p[0],dt->px->pix_p[1],GREEN);
				// 	break;
				// }
				// else if (ray_sphere(dt->px->ray_v,dt->ca->cam_p,dt->sc->z_sphere, t))
				// {
				// 	fill_pixel_res(dt,dt->px->pix_p[0],dt->px->pix_p[1],BLUE);
				// 	break;
				// }
				// else if (ray_sphere(dt->px->ray_v,dt->ca->cam_p,dt->sc->a_sphere, t))
				// {
				// 	fill_pixel_res(dt,dt->px->pix_p[0],dt->px->pix_p[1],WHITE);
				// 	break;
				// }
				t += 0.05;
			}
		}
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
	if (s[3] <= s[4] + 0.1 && s[3] >= s[4] - 0.1)
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
	rotate_x(angles[0], &vec[0], &vec[1], &vec[2]);
	rotate_y(angles[1], &vec[0], &vec[1], &vec[2]);
	rotate_z(angles[2], &vec[0], &vec[1], &vec[2]);
}

// TODO:
// improve the camera movements to follow the camera orientation
// rayflow
// 	-	for each pixel i create a ray and store it in ray
// 	-	get the normal
// 	-	get the light vector
// the color is 255 - arcos (dot product norm and light)




int		main(int ac, char **av)
{
	static t_data	*dt;
	static t_mlx	*md;

	dt = init_data(dt);
	dt->md = mlx_data_init_return(md);

	img_square(dt->md, BLUE);


	display(dt);
	mlx_key_hook(dt->md->win, call_keys, dt);
	mlx_loop(dt->md->mlx);
	return (0);
}
