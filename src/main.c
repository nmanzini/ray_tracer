/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:34:26 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/02 16:10:19 by nmanzini         ###   ########.fr       */
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
	if (len != 1 && len != 0)
	{
		vec[0] /= len;
		vec[1] /= len;
		vec[2] /= len;
	}
	else
		return;
}

void	update_ray_p(float *cam_p, t_pv *ray)
{
	// takes the point of the camera and gives it to the pix struct
	ray->p[0] = cam_p[0];
	ray->p[1] = cam_p[1];
	ray->p[2] = cam_p[2];
}

void	update_ray_v(int *res, int *pixel, float *scr_s, t_pv *ray)
{	
	ray->v[0] = - (scr_s[0] / 2) + (scr_s[0] / (res[0] - 1) * pixel[0]);
	ray->v[1] = + (scr_s[1] / 2) - (scr_s[1] / (res[1] - 1) * pixel[1]);
	ray->v[2] = + (scr_s[2]);
	normalize (ray->v);
}

float dot_prod(float *vec1, float *vec2)
{
	float	result;
	int		i;

	i = -1;
	result = 0;

	while (++i < 3)
		result += vec1[i] * vec2[i];
	return (result);
}

// void	update_intersection_p(float t, float *ray_v, float *cam_p, float *int_p)
// {
// 	int_p[0] = cam_p[0] + t * ray_v[0];
// 	int_p[1] = cam_p[1] + t * ray_v[1];
// 	int_p[2] = cam_p[2] + t * ray_v[2];
// }

void	update_encounter_p(float t, t_pv *ray, t_pv *enc)
{
	enc->p[0] = ray->p[0] + t * ray->v[0];
	enc->p[1] = ray->p[1] + t * ray->v[1];
	enc->p[2] = ray->p[2] + t * ray->v[2];
}

// void	update_sphere_normal_v(float *int_p, float *sphere_p, float *int_n)
// {
// 	int_n[0] = int_p[0] - sphere_p[0];
// 	int_n[1] = int_p[1] - sphere_p[1];
// 	int_n[2] = int_p[2] - sphere_p[2];
// 	normalize (int_n);
// }

// void	update_plane_normal_v(float *plane, float *int_n)
// {
// 	int_n[0] = 0;
// 	int_n[1] = 0;
// 	int_n[2] = 0;
// 	if (plane[0] == 0)
// 	{
// 		int_n[0] = 1.0;
// 	}
// 	else if (plane[0] == 1)
// 	{
// 		int_n[1] = 1.0;
// 	}
// 	else if (plane[0] == 2)
// 	{
// 		int_n[2] = - 1.0;
// 	}
// }

void	update_light_v(t_pv *enc, t_pv *lig)
{
	lig->v[0] = lig->p[0] - enc->p[0];
	lig->v[1] = lig->p[1] - enc->p[1];
	lig->v[2] = lig->p[2] - enc->p[2];
	normalize (lig->v);
}

void	update_color(t_pv *enc, t_pv *lig, unsigned int *color)
{
	float			projection;
	unsigned int	range;
	int				cheker;

	projection = enc->v[0] * lig->v[0] + enc->v[1] * lig->v[1] + enc->v[2] * lig->v[2];

	cheker = 0;

	if (cheker)
	{
		if ((int)enc->p[0] % 2 >= 1 || (int)enc->p[2] % 2 >= 1)
		{
			range = (projection + 1) / 2 * 256;
			*color = range + range * 256 + range * 256 * 256;
		}
		else
		{
			range = (projection + 1) / 2 * 128;
			*color = range + range * 256 + range * 256 * 256;
		}
	}
	else
	{
		range = (projection + 1) / 2 * 255;
		*color = range + range * 256 + range * 256 * 256;
	}
}
void color_point(t_data	*dt)
{
	update_light_v(dt->px->enc, dt->px->lig);
	update_color(dt->px->enc, dt->px->lig, &dt->px->color);
	fill_pixel_res(dt, dt->px->pix_p[0], dt->px->pix_p[1], dt->px->color);
}

void ray_trace(t_data	*dt)
{
	float	t;
	float	temp_t;

	t = 100000000;

	cam_data_update(dt->ca);
	update_ray_p(dt->ca->cam_p, dt->px->ray);
	dt->px->pix_p[1] = -1;
	while (++dt->px->pix_p[1] < dt->ca->res[1])
	{
		dt->px->pix_p[0] = -1;
		while (++dt->px->pix_p[0] < dt->ca->res[0])
		{
			t = 100000000;
			update_ray_v(dt->ca->res,dt->px->pix_p,dt->ca->scr_s,dt->px->ray);
			rotate_v(dt->px->ray->v, dt->ca->cam_a);
			
			temp_t = ray_cone_encounter(dt->sc->cone, 25, dt->px->ray, dt->px->enc);
			if (temp_t < t && temp_t != 0)
			{
				t = temp_t;
				color_point(dt);
			}

			temp_t = ray_box_encounter(dt->sc->box, dt->px->ray, dt->px->enc);
			if (temp_t < t && temp_t != 0)
			{
				t = temp_t;
				color_point(dt);
			}

			temp_t = ray_sphere_encounter(dt->sc->sphere, dt->px->ray, dt->px->enc);
			if (temp_t < t && temp_t != 0)
			{
				t = temp_t;
				color_point(dt);
			}

			temp_t = ray_surface_encounter(dt->sc->surface, dt->px->ray, dt->px->enc);
			if (temp_t < t && temp_t != 0)
			{
				t = temp_t;
				color_point(dt);
			}

			temp_t = ray_plane_encounter(dt->sc->plane ,dt->px->ray, dt->px->enc);
			if (temp_t < t && temp_t != 0)
			{
				t = temp_t;
				color_point(dt);
			}
		}
	}
}

// float	ray_cylinder_encounter(t_pv cyl, float r, t_pv *ray, t_pv *enc)
// {
// 	float		A;
// 	float		B;
// 	float		C;

// 	// general cylinder equation;
// 	// x^2 + z^2 - r^2 = 0;

// 	// cylinder orientation:
// 	// pa + va * t

// 	// vector cylinder equation; q is a point
// 	// (q - pa - (va,q - pa)va)2 - r2 = 0

// 	// substitute q = p + vt and solve
// 	// (p - pa + vt - (va,p - pa + vt)va)2 - r2 = 0

// 	//--------------------------------------------------------------------------
// 	// Ray : P(t) = O + V * t
// 	// Cylinder [O, D, r].
// 	// point Q on cylinder if ((Q - O) x D)^2 = r^2
// 	//
// 	// Cylinder [A, B, r].
// 	// Point P on infinite cylinder if ((P - A) x (B - A))^2 = r^2 * (B - A)^2
// 	// expand : ((O - A) x (B - A) + t * (V x (B - A)))^2 = r^2 * (B - A)^2
// 	// equation in the form (X + t * Y)^2 = d
// 	// where : 
// 	//  X = (O - A) x (B - A)
// 	//  Y = V x (B - A)
// 	//  d = r^2 * (B - A)^2
// 	// expand the equation :
// 	// t^2 * (Y . Y) + t * (2 * (X . Y)) + (X . X) - d = 0
// 	// => second order equation in the form : a*t^2 + b*t + c = 0 where
// 	// a = (Y . Y)
// 	// b = 2 * (X . Y)
// 	// c = (X . X) - d
// 	//--------------------------------------------------------------------------

// 	Vector AB = (B - A);
// 	Vector AO = (O - A);
// 	Vector AOxAB = (AO ^ AB); // cross product
// 	Vector VxAB  = (V ^ AB); // cross product
// 	float  ab2   = (AB * AB); // dot product
// 	float a      = (VxAB * VxAB); // dot product
// 	float b      = 2 * (VxAB * AOxAB); // dot product
// 	float c      = (AOxAB * AOxAB) - (r*r * ab2);


// 	Vector AB = cyl.v;
// 	Vector AO = (ray->p - cyl.p);
// 	Vector AOxAB = (AO ^ AB); // cross product
// 	Vector VxAB  = (V ^ AB); // cross product
// 	float  ab2   = (AB * AB); // dot product
// 	float a      = (VxAB * VxAB); // dot product
// 	float b      = 2 * (VxAB * AOxAB); // dot product
// 	float c      = (AOxAB * AOxAB) - (r*r * ab2);

// 	// solve second order equation : a*t^2 + b*t + c = 0
// }

float	ray_cone_encounter(t_pv cone, int angle, t_pv *ray, t_pv *enc)
{
	float		A;
	float		B;
	float		C;
	float		DV;
	float		CO[3];
	float		CO_CO_dot;
	float		COV;
	float		DCO;
	float		cos_sqr;
	float		t;

	DV = dot_prod(ray->v,cone.v);

	cos_sqr = pow(cos(angle * PI_R), 2);

	CO[0] = ray->p[0] - cone.p[0];
	CO[1] = ray->p[1] - cone.p[1];
	CO[2] = ray->p[2] - cone.p[2];

	CO_CO_dot = dot_prod(CO,CO) * cos_sqr;

	COV = dot_prod(CO,cone.v);

	DCO = dot_prod(ray->v, CO);

	A = pow(DV,2) - cos_sqr;
	B = 2 * ((DV * COV) - DCO * cos_sqr);
	C = pow(COV,2) - CO_CO_dot;

	t = solve_quadratic(A,B,C);
	if (t == 0)
		return(0);
	update_encounter_p(t, ray, enc);

	// fux the normal, now it is half assed

	enc->v[0] = - cone.p[0] + enc->p[0];
	enc->v[1] = - cone.p[1] + enc->p[1];
	// enc->v[2] = cone.p[2] - enc->p[2];

	// enc->v[0] = -1;
	// enc->v[1] = 0;
	enc->v[2] = 0;
	normalize(enc->v);
	return (t);
}

float	ray_sphere_encounter(float *sphere, t_pv *ray, t_pv *enc)
{
	int			i;
	float		A;
	float		B;
	float		C;
	// float		det;
	float		b_vec[3];
	float		length;
	float		t;

	A = 1;
	// b= 2 * ray_v * (ray_p − sphere_p)
	i = -1;
	while(++i < 3)
		b_vec[i] = ray->v[i] * (ray->p[i] - sphere [i]);
	B = 2 * (b_vec[0] + b_vec[1] + b_vec[2]);
	// c=|ray_origin - center|^2 − Radius ^2 
	length = pow(ray->p[0] - sphere[0],2) +
				pow(ray->p[1] - sphere[1],2) +
				pow(ray->p[2] - sphere[2],2);
	C = length - pow(sphere[3],2);

	t = solve_quadratic(A,B,C);
	if (t == 0)
		return(0);
	update_encounter_p(t, ray, enc);

	enc->v[0] = enc->p[0] - sphere[0];
	enc->v[1] = enc->p[1] - sphere[1];
	enc->v[2] = enc->p[2] - sphere[2];
	normalize(enc->v);
	return (t);
}

float	ray_box_encounter(float *box, t_pv *ray, t_pv *enc)
{
	float t1[3];
	float t2[3];

	float tmin = 0, tmax = INFINITY;
	int i;
	int axis;

	i = -1;
	enc->v[0] = 0;
	enc->v[1] = 0;
	enc->v[2] = 0;
	axis = 1;

	while (++i<3)
	{
		if (ray->v[i] != 0.0) 
		{
			t1[i] = (box[i] - ray->p[i])/ray->v[i];
			t2[i] = (box[i + 3] - ray->p[i])/ray->v[i];

			if (tmin < MIN(t1[i], t2[i]))
			{
				if (t1[i] < t2[i])
					axis = i + 1;
				else
					axis = -i - 1;
			}
			tmin = MAX(tmin, MIN(t1[i], t2[i]));
			tmax = MIN(tmax, MAX(t1[i], t2[i]));
		}
	}
	if (tmax >= tmin)
	{
		update_encounter_p(tmin, ray, enc);

		if (axis > 0)
			enc->v[axis -1] = - 1;
		else 
			enc->v [ - axis -1] = 1;
		return (tmin);
	}
	else
		return (0);
}

float	solve_quadratic(float A, float B, float C)
{
	float det;
	float dist;
	float t[2];

	det = pow(B,2) - 4 * A * C;

	if (det < 0)
		return(0);	
	else if (det == 0)
	{
		dist = - B / (2 * A);
		if (dist < 0)
			return(0);
	}
	else if (A == 0)
	{
		return (0);
	}
	else
	{
		t[0] = (- B - sqrt(det)) / (2 * A);
		t[1] = (- B + sqrt(det)) / (2 * A);
		if (t[0] < t[1] && t[0] > 0)
			dist = t[0];
		else if (t[1] < t[0] && t[1] > 0)
			dist = t[1];
		else
			return(0); // should not exist
	}
	// if (dist > 1024)
	// 	return (0);
	return (dist);
}

float	ray_surface_encounter(float *surface, t_pv *ray, t_pv *enc)
{
	int 	axis;
	float	t;
	int		i;

	i = -1;
	while(++i < 3)
		if (surface[i + 3] == 0)
			axis = i;

	if (ray->v[axis] != 0)
		// ray->v[axis] * t + ray->p[axis] = plane[1]
		t  = (surface[axis] - ray->p[axis]) / ray->v[axis];
	else
		return (0);
	if (t > 0)
	{
		// enc->p[0] = ray->p[0] + t * ray->v[0];
		// enc->p[1] = ray->p[1] + t * ray->v[1];
		// enc->p[2] = ray->p[2] + t * ray->v[2];

		update_encounter_p(t, ray, enc);

		enc->v[0] = 0;
		enc->v[1] = 0;
		enc->v[2] = 0;
		enc->v[axis] = 1;

		i = -1;
		while(++i < 3)
			if (i != axis)
			{
				if (!(enc->p[i] <= surface[i] + surface[i + 3] && enc->p[i] >= surface[i] - surface[i + 3]))
					return (0);
			}
		return (t);
	}
	return (0);
}

float	ray_plane_encounter(float *plane, t_pv *ray, t_pv *enc)
{
	int 	axis;
	float	t;

	axis = (int)plane[0];
	if (ray->v[axis] != 0)
	// ray->v[axis] * t + ray->p[axis] = plane[1]
		t  = (plane[1] - ray->p[axis]) / ray->v[axis];
	else
		return (0);
	if (t > 0)
	{
		update_encounter_p(t, ray, enc);

		enc->v[0] = 0;
		enc->v[1] = 0;
		enc->v[2] = 0;
		enc->v[axis] = 1;
		return (t);
	}
	return (0);
}

// int	ray_plane_prog(float *plane, float	*int_p)
// {
// 	if (plane[0] == 0 && int_p[0] <= plane[1] + 0.1 && int_p[0] >= plane[1] - 0.1)
// 			return (1);
// 	else if (plane[0] == 1 && int_p[1] <= plane[1] + 0.1 && int_p[1] >= plane[1] - 0.1)
// 			return (1);
// 	else if (plane[0] == 2 && int_p[2] <= plane[1] + 0.1 && int_p[2] >= plane[1] - 0.1)
// 			return (1);
// 	return (0);
// }

// int	ray_sphere_prog(float *sphere, float *int_p)
// {
// 	float	s[5];

// 	s[0] = sphere[0] - int_p[0];
// 	s[1] = sphere[1] - int_p[1];
// 	s[2] = sphere[2] - int_p[2];
// 	s[3] = s[0] * s[0] + s[1] * s[1] + s[2] * s[2];
// 	s[4] = sphere[3] * sphere[3];
// 	if (s[3] <= s[4] + 0.1 && s[3] >= s[4] - 0.1)
// 		return (1);
// 	else
// 		return (0);
// }

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

/*
	TODO:
	-	for every ray check this sphere
	-	check the distance at whete it hits it
	-	then save the intesection point then after all normal
	next do it for multiple objs
	next do it for multiple kind of objs
*/



int		main(int ac, char **av)
{
	static t_data	*dt;
	static t_mlx	*md;

	dt = init_data(dt);
	dt->md = mlx_data_init_return(md);

	display(dt);
	mlx_key_hook(dt->md->win, call_keys, dt);
	mlx_loop(dt->md->mlx);
	return (0);
}
