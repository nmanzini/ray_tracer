/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:34:26 by nmanzini          #+#    #+#             */
/*   Updated: 2018/02/22 14:56:13 by nmanzini         ###   ########.fr       */
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

void	update_ray_p(float *cam_p, float *ray_p )
{
	ray_p = cam_p;
}

void	update_ray_v(int *res, int *pixel, float *scr_s, float *ray_v)
{	
	ray_v[0] = - (scr_s[0] / 2) + (scr_s[0] / (res[0] - 1) * pixel[0]);
	ray_v[1] = + (scr_s[1] / 2) - (scr_s[1] / (res[1] - 1) * pixel[1]);
	ray_v[2] = + (scr_s[2]);
	normalize (ray_v);
}

void	update_intersection_p(float t, float *ray_v, float *cam_p, float *int_p)
{
	int_p[0] = cam_p[0] + t * ray_v[0];
	int_p[1] = cam_p[1] + t * ray_v[1];
	int_p[2] = cam_p[2] + t * ray_v[2];
}

void	update_sphere_normal_v(float *int_p, float *sphere_p, float *int_n)
{
	int_n[0] = int_p[0] - sphere_p[0];
	int_n[1] = int_p[1] - sphere_p[1];
	int_n[2] = int_p[2] - sphere_p[2];
	normalize (int_n);
}

void	update_plane_normal_v(float *plane, float *int_n)
{
	int_n[0] = 0;
	int_n[1] = 0;
	int_n[2] = 0;
	if (plane[0] == 0)
	{
		int_n[0] = 1.0;
	}
	else if (plane[0] == 1)
	{
		int_n[1] = 1.0;
	}
	else if (plane[0] == 2)
	{
		int_n[2] = - 1.0;
	}
}

void	update_light_v(float *lig_p, float *int_p, float *lig_v)
{
	lig_v[0] = lig_p[0] - int_p[0];
	lig_v[1] = lig_p[1] - int_p[1];
	lig_v[2] = lig_p[2] - int_p[2];
	normalize (lig_v);
}

void	update_color(float *int_n, float *lig_v, unsigned int *color)
{
	float			projection;
	unsigned int	range;

	projection = int_n[0] * lig_v [0] + int_n[1] * lig_v [1] + int_n[2] * lig_v [2];

	range = (projection + 1) / 2 * 256;

	*color = range + range * 256 + range * 256 * 256;
}

void ray_trace(t_data	*dt)
{
	float			ray[3];
	float			t;

	cam_data_update(dt->ca);
	update_ray_p(dt->ca->cam_p, dt->px->ray_p);
	dt->px->pix_p[1] = -1;
	while (++dt->px->pix_p[1] < dt->ca->res[1])
	{
		dt->px->pix_p[0] = -1;
		while (++dt->px->pix_p[0] < dt->ca->res[0])
		{
			update_ray_v(dt->ca->res,dt->px->pix_p,dt->ca->scr_s,dt->px->ray_v);
			
			rotate_v(dt->px->ray_v, dt->ca->cam_a);

			t = 0;

			while (t < dt->ca->max_depth)
			{
				update_intersection_p(t, dt->px->ray_v, dt->ca->cam_p, dt->px->int_p);
				if (ray_sphere(dt->sc->x_sphere, dt->px->int_p))
				{
					update_sphere_normal_v(dt->px->int_p, dt->sc->x_sphere, dt->px->int_n);
					update_light_v(dt->sc->light,dt->px->int_p,dt->px->lig_v);
					update_color(dt->px->int_n,dt->px->lig_v,&dt->px->color);
					fill_pixel_res(dt,dt->px->pix_p[0],dt->px->pix_p[1],dt->px->color);
					break;
				}
				else if (ray_sphere(dt->sc->y_sphere, dt->px->int_p))
				{
					update_sphere_normal_v(dt->px->int_p, dt->sc->y_sphere, dt->px->int_n);
					update_light_v(dt->sc->light,dt->px->int_p,dt->px->lig_v);
					update_color(dt->px->int_n,dt->px->lig_v,&dt->px->color);
					fill_pixel_res(dt,dt->px->pix_p[0],dt->px->pix_p[1],dt->px->color);
					break;
				}
				else if (ray_sphere(dt->sc->z_sphere, dt->px->int_p))
				{
					update_sphere_normal_v(dt->px->int_p, dt->sc->z_sphere, dt->px->int_n);
					update_light_v(dt->sc->light,dt->px->int_p,dt->px->lig_v);
					update_color(dt->px->int_n,dt->px->lig_v,&dt->px->color);
					fill_pixel_res(dt,dt->px->pix_p[0],dt->px->pix_p[1],dt->px->color);
					break;
				}
				else if (ray_sphere(dt->sc->a_sphere, dt->px->int_p))
				{
					update_sphere_normal_v(dt->px->int_p, dt->sc->a_sphere, dt->px->int_n);
					update_light_v(dt->sc->light,dt->px->int_p,dt->px->lig_v);
					update_color(dt->px->int_n,dt->px->lig_v,&dt->px->color);
					fill_pixel_res(dt,dt->px->pix_p[0],dt->px->pix_p[1],dt->px->color);
					break;
				}
				else if (ray_sphere(dt->sc->light, dt->px->int_p))
				{
					update_sphere_normal_v(dt->px->int_p, dt->sc->light, dt->px->int_n);
					update_light_v(dt->sc->light,dt->px->int_p,dt->px->lig_v);
					update_color(dt->px->int_n,dt->px->lig_v,&dt->px->color);
					fill_pixel_res(dt,dt->px->pix_p[0],dt->px->pix_p[1],dt->px->color);
					break;
				}
				else if (ray_plane(dt->sc->plane, dt->px->int_p))
				{
					update_plane_normal_v(dt->sc->plane, dt->px->int_n);
					update_light_v(dt->sc->light,dt->px->int_p,dt->px->lig_v);
					update_color(dt->px->int_n,dt->px->lig_v,&dt->px->color);
					fill_pixel_res(dt,dt->px->pix_p[0],dt->px->pix_p[1],dt->px->color);
					break;
				}
				else if (ray_plane(dt->sc->plane2, dt->px->int_p))
				{
					update_plane_normal_v(dt->sc->plane2, dt->px->int_n);
					update_light_v(dt->sc->light,dt->px->int_p,dt->px->lig_v);
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

// int	ray_box(float *box, float *int_p)
// {
// 	if (int_p <= (box[0] + box[3]/2) && int_p >= (box[0] - box[3]/2) &&
// 		int_p <= (box[1] + box[4]/2) && int_p >= (box[1] - box[4]/2) &&
// 		int_p <= (box[2] + box[5]/2) && int_p >= (box[2] - box[5]/2))
// 		return (1);
// 	return (0);
// }

int	ray_plane(float *plane, float	*int_p)
{
	if (plane[0] == 0 && int_p[0] <= plane[1] + 0.1 && int_p[0] >= plane[1] - 0.1)
			return (1);
	else if (plane[0] == 1 && int_p[1] <= plane[1] + 0.1 && int_p[1] >= plane[1] - 0.1)
			return (1);
	else if (plane[0] == 2 && int_p[2] <= plane[1] + 0.1 && int_p[2] >= plane[1] - 0.1)
			return (1);
	return (0);
}


int	ray_sphere(float *sphere, float *int_p)
{
	float	s[5];

	s[0] = sphere[0] - int_p[0];
	s[1] = sphere[1] - int_p[1];
	s[2] = sphere[2] - int_p[2];
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
