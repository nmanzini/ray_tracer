/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:34:26 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/08 23:40:30 by nmanzini         ###   ########.fr       */
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
	// normilizes a 3 dim array of floats.
	float len;

	len = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	if (len != 1 && len != 0)
	{
		vec[0] /= len;
		vec[1] /= len;
		vec[2] /= len;
	}
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
	// create the ray vector based on the screen size, resolution and wich ixel we are analyzing
	ray->v[0] = - (scr_s[0] / 2) + (scr_s[0] / (res[0] - 1) * pixel[0]);
	ray->v[1] = + (scr_s[1] / 2) - (scr_s[1] / (res[1] - 1) * pixel[1]);
	ray->v[2] = + (scr_s[2]);
	normalize (ray->v);
}

float dot_prod(float *vec1, float *vec2)
{
	// returns the dot product
	float	result;
	int		i;

	i = -1;
	result = 0;

	while (++i < 3)
		result += vec1[i] * vec2[i];
	return (result);
}

void	vec_mult(float *vect, float scalar, float *result)
{
	// multiplies a vector by a scalar returned in result
	result[0] = scalar * vect[0];
	result[1] = scalar * vect[1]; 
	result[2] = scalar * vect[2]; 
}

void	vec_sub(float *vect1, float *vect2, float *result)
{
	// subtraction between two vector passed into the resul vector
	result[0] = vect1[0] - vect2[0];
	result[1] = vect1[1] - vect2[1];
	result[2] = vect1[2] - vect2[2];
}

void	vec_add(float *vect1, float *vect2, float *result)
{
	// addition between two vector passed into the resul vector
	result[0] = vect1[0] + vect2[0];
	result[1] = vect1[1] + vect2[1];
	result[2] = vect1[2] + vect2[2];
}

void	vec_neg(float *vect, float *result)
{
	// addition between two vector passed into the resul vector
	result[0] = - vect[0];
	result[1] = - vect[1];
	result[2] = - vect[2];
}

float	vec_len(float *vect)
{
	return (sqrt(float_abs(pow(vect[0],2) + pow(vect[1],2) + pow(vect[2],2))));
}

void	min_perp_vec(float *point, float *vector, float *origin, float *normal)
{
	// Minimal perpendicular vector between a point and a line

	float pa[3];
	float pa_d;
	float pa_dd[3];
	float neg_a[3];
	float neg_a_minus_pa_dd[3];

	// (P-A)
	vec_sub(point,origin,pa);
	// (P-A).D)
	pa_d = dot_prod(pa,vector);
	// ((P-A).D)D
	vec_mult(vector, pa_d, pa_dd);
	// -A
	vec_neg(origin,neg_a);
	// - A - ((P-A).D)D
	vec_sub(neg_a, pa_dd, neg_a_minus_pa_dd);
	// - A - ((P-A).D)D + P
	vec_add(neg_a_minus_pa_dd, point, normal);
}

void	update_encounter_p(float t, t_pv *ray, t_pv *enc)
{
	// given an encounter struct the ray and a distance, updates the poin of intersection
	enc->p[0] = ray->p[0] + t * ray->v[0];
	enc->p[1] = ray->p[1] + t * ray->v[1];
	enc->p[2] = ray->p[2] + t * ray->v[2];
}

void	update_light_v(t_pv *enc, t_pv *lig)
{
	// updates the light vector toward the encounter point, and normalizes it
	lig->v[0] = -lig->p[0] + enc->p[0];
	lig->v[1] = -lig->p[1] + enc->p[1];
	lig->v[2] = -lig->p[2] + enc->p[2];
	normalize (lig->v);
}

float	light_enc_dist(t_pv *enc, t_pv *lig)
{
	float light_enc[3];

	vec_sub(enc->p,lig->p,light_enc);
	return (vec_len(light_enc));
}

void	update_color(t_pix *px, t_obj *ob)
{
	float			projection;
	float			ra;	
	float 			light_factor;
	float			light_power;
	float			light_dist;
	float				ambient;



	projection = - dot_prod(px->enc->v, px->lig->v);
	if (projection < 0)
		projection = 0;

	light_power = 150;

	light_dist = light_enc_dist(px->enc, px->lig);
	light_factor = light_power / pow(0.5*light_dist,2);

	if (light_factor > 1)
		light_factor = 1;

	ambient = 0.10;
	ra = projection * (1 - ambient) * light_factor + ambient;
	if (px->shadow)
		ra = ambient;

	px->color = rgb_to_ui(ra * ob->rgb[0],ra * ob->rgb[1],ra * ob->rgb[2]);
	}

float check_obj_temp_t(t_pv *ray, t_pv *enc, t_obj ob)
{
	float temp_t;

	temp_t = 0;
	if (ob.type == 's')
	{
		temp_t = ray_sphere_encounter(ob.p, ray, enc);
	}
	else if (ob.type == 'o')
	{
		temp_t = ray_cone_encounter(ob.vp, ob.p[0], ray, enc);
	}
	else if (ob.type == 'y')
	{
		temp_t = ray_cylinder_encounter(ob.vp, ob.p[0], ray, enc);
	}
	else if (ob.type == 'p')
	{
		temp_t = ray_plane_encounter(ob.p ,ray, enc);
	}
	return temp_t;
}

int loop_obj_shadow(t_pv *enc, t_pv *lig, t_obj *ob, int exc)
{
	int i;
	float temp_t;
	t_pv	dummy;
	float	light_dist;

	light_dist = light_enc_dist(enc, lig);

	i = -1;

	while (ob[++i].type != 'n')
	{	
		if (i != exc)
			temp_t = check_obj_temp_t(lig, &dummy, ob[i]);
		if (temp_t > 0 && temp_t < light_dist -0.001)
			return (1);
	}
	return (0);
}

void color_point(t_data	*dt, int i)
{
	float dist;
	float dist_to_obj;
	float light_dist;
	int shadow;

	update_light_v(dt->px->enc, dt->px->lig);

	dt->px->shadow = loop_obj_shadow(dt->px->enc, dt->px->lig, dt->ob, i);


	update_color(dt->px, &dt->ob[i]);
	fill_pixel_res(dt, dt->px->pix_p[0], dt->px->pix_p[1], dt->px->color);
}

void loop_trough_objs(t_data	*dt)
{
	int		i;
	float	temp_t;
	float	t;

	t = 1024;
	i = -1;
	while (dt->ob[++i].type != 'n')
	{
		temp_t = check_obj_temp_t(dt->px->ray, dt->px->enc,dt->ob[i]);
		if (temp_t < t && temp_t != 0)
		{
			t = temp_t;
			color_point(dt, i);
		}
	}
}

void ray_trace(t_data	*dt)
{
	float	t;
	float	temp_t;

	cam_data_update(dt->ca);
	update_ray_p(dt->ca->cam_p, dt->px->ray);
	dt->px->pix_p[1] = -1;
	while (++dt->px->pix_p[1] < dt->ca->res[1])
	{
		dt->px->pix_p[0] = -1;
		while (++dt->px->pix_p[0] < dt->ca->res[0])
		{
			update_ray_v(dt->ca->res,dt->px->pix_p,dt->ca->scr_s,dt->px->ray);
			rotate_v(dt->px->ray->v, dt->ca->cam_a);

			loop_trough_objs(dt);
		}
	}
}

void ray_trace_old(t_data	*dt)
{
	float	t;
	float	temp_t;

	cam_data_update(dt->ca);
	update_ray_p(dt->ca->cam_p, dt->px->ray);
	dt->px->pix_p[1] = -1;
	while (++dt->px->pix_p[1] < dt->ca->res[1])
	{
		dt->px->pix_p[0] = -1;
		while (++dt->px->pix_p[0] < dt->ca->res[0])
		{
			t = 1024;
			update_ray_v(dt->ca->res,dt->px->pix_p,dt->ca->scr_s,dt->px->ray);
			rotate_v(dt->px->ray->v, dt->ca->cam_a);
			
			// temp_t = ray_cone_encounter(dt->sc->cone, 15, dt->px->ray, dt->px->enc);
			// if (temp_t < t && temp_t != 0)
			// {
			// 	t = temp_t;
			// 	color_point(dt, t, WHITE);
			// }

			// temp_t = ray_sphere_encounter(dt->sc->sphere, dt->px->ray, dt->px->enc);
			// if (temp_t < t && temp_t != 0)
			// {
			// 	t = temp_t;
			// 	color_point(dt, t, WHITE);
			// }

			// temp_t = ray_plane_encounter(dt->sc->plane ,dt->px->ray, dt->px->enc);
			// if (temp_t < t && temp_t != 0)
			// {
			// 	t = temp_t;
			// 	color_point(dt, t, WHITE);
			// }

			// temp_t = ray_cylinder_encounter(dt->sc->cylinder, 2, dt->px->ray, dt->px->enc);
			// if (temp_t < t && temp_t != 0)
			// {
			// 	t = temp_t;
			// 	color_point(dt, t, WHITE);
			// }

			// temp_t = ray_box_encounter(dt->sc->box, dt->px->ray, dt->px->enc);
			// if (temp_t < t && temp_t != 0)
			// {
			// 	t = temp_t;
			// 	color_point(dt, WHITE);
			// }
			
			// temp_t = ray_surface_encounter(dt->sc->surface, dt->px->ray, dt->px->enc);
			// if (temp_t < t && temp_t != 0)
			// {
			// 	t = temp_t;
			// 	color_point(dt, WHITE);
			// }
		}
	}
}

float	ray_cylinder_encounter(t_pv cyl, float r, t_pv *ray, t_pv *enc)
{
	float		A;
	float		B;
	float		C;
	float		t;
	float		Dp[3];
	float		Dp_Va;
	float		Dp_VaVa[3];
	float		DpDp_VaVa[3];
	float		v_va;
	float		v_vava[3];
	float		vv_vava[3];


	// Dp = ∆p = p - pa 
	vec_sub(ray->p,cyl.p, Dp);
	// Dp_Va = (∆p,va)
	Dp_Va = dot_prod(Dp, cyl.v);
	// Dp_VaVa = (∆p,va) * va
	vec_mult(cyl.v, Dp_Va, Dp_VaVa);
	// DpDp_VaVa =  ∆p - (∆p,va) * va
	vec_sub(Dp, Dp_VaVa, DpDp_VaVa);


	// v_va = (v,va)
	v_va = dot_prod(ray->v, cyl.v);
	// v_vava = (v,va) * va
	vec_mult(cyl.v, v_va, v_vava);
	// vv_vava = v - (v,va) * va
	vec_sub(ray->v, v_vava, vv_vava);


	A = dot_prod(vv_vava,vv_vava);
	B = 2 * dot_prod(vv_vava,DpDp_VaVa);
	C = dot_prod(DpDp_VaVa,DpDp_VaVa) - (r*r);


	t = solve_quadratic(A,B,C);
	if (t == 0)
		return(0);
	update_encounter_p(t, ray, enc);

	min_perp_vec(enc->p, cyl.v, cyl.p, enc->v);
	normalize(enc->v);

	return (t);
}

float	ray_cone_encounter(t_pv cone, int angle, t_pv *ray, t_pv *enc)
{
	float		A;
	float		B;
	float		C;
	float		t;
	float		Dp[3];
	float		Dp_Va;
	float		Dp_VaVa[3];
	float		DpDp_VaVa[3];
	float		v_va;
	float		v_vava[3];
	float		vv_vava[3];

	float		cos_sqr;
	float		sin_sqr;


	// Dp = ∆p = p - pa 
	vec_sub(ray->p,cone.p, Dp);
	// Dp_Va = (∆p,va)
	Dp_Va = dot_prod(Dp, cone.v);
	// Dp_VaVa = (∆p,va) * va
	vec_mult(cone.v, Dp_Va, Dp_VaVa);
	// DpDp_VaVa =  ∆p - (∆p,va) * va
	vec_sub(Dp, Dp_VaVa, DpDp_VaVa);


	// v_va = (v,va)
	v_va = dot_prod(ray->v, cone.v);
	// v_vava = (v,va) * va
	vec_mult(cone.v, v_va, v_vava);
	// vv_vava = v - (v,va) * va
	vec_sub(ray->v, v_vava, vv_vava);


	cos_sqr = cos(angle * PI_R) * cos(angle * PI_R);
	sin_sqr = sin(angle * PI_R) * sin(angle * PI_R);


	A = cos_sqr * dot_prod(vv_vava,vv_vava) - (sin_sqr * v_va * v_va);
	B = 2 * cos_sqr * dot_prod(vv_vava,DpDp_VaVa) - (2 * sin_sqr * v_va * Dp_Va);
	C = cos_sqr * dot_prod(DpDp_VaVa,DpDp_VaVa) - (sin_sqr * Dp_Va * Dp_Va);


	t = solve_quadratic(A,B,C);
	if (t == 0)
		return(0);
	update_encounter_p(t, ray, enc);
	min_perp_vec(enc->p, cone.v, cone.p, enc->v);
	normalize(enc->v);

	return (t);
}

float	ray_cone_encounter_old(t_pv cone, int angle, t_pv *ray, t_pv *enc)
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

	min_perp_vec(enc->p, cone.v, cone.p, enc->v);
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

	vec_sub(enc->p,sphere,enc->v);
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
			enc->v[- axis -1] = 1;
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
	float det_error;

	det_error = 0.1;

	det = pow(B,2) - (4 * A * C);

	if (det < 0)
		return(0);	
	else if (det == 0)
	{
		dist = - (B / (2 * A));
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
		else if (t[0] > 0)
			dist = t[0];
		else if (t[1] > 0)
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
	float	t;
	t = - (plane[0] * ray->p[0] + plane[1] * ray->p[1] + plane[2] * ray->p[2] -  plane[3]) / 
	(plane[0] * ray->v[0] + plane[1] * ray->v[1] + plane[2] * ray->v[2]);

	if (t > 0)
	{
		update_encounter_p(t, ray, enc);

		// normalize (plane);
		enc->v[0] = plane[0];
		enc->v[1] = plane[1];
		enc->v[2] = plane[2];
		normalize(enc->v);
		return (t);
	}
	return (0);
}


float	ray_plane_encounter_old(float *plane, t_pv *ray, t_pv *enc)
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
	Norminette this shit 4h
	check fof breaking the input
*/

int		main(int ac, char **av)
{
	static t_data	*dt;
	static t_mlx	*md;

	dt = init_data(dt);
	if (!get_input(dt,ac,av))
	{
		ft_putstr("Really good indeed!!!\n");
		dt->md = mlx_data_init_return(md);
		display(dt);
		mlx_key_hook(dt->md->win, call_keys, dt);
		mlx_loop(dt->md->mlx);
	}
	else
	{
		ft_putstr("ERROR, EXITING!!!\n");
		exit(0);
	}
	return (0);
}
