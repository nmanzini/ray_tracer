/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:34:26 by nmanzini          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/04/09 13:32:17 by nmanzini         ###   ########.fr       */
=======
/*   Updated: 2018/04/08 23:07:49 by nmanzini         ###   ########.fr       */
>>>>>>> parent of 862c7f6... pre norminette owrking
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

/*
** normilizes a 3 dim array of floats
*/

void	normalize(float *vec)
{
	float len;

	len = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	if (len != 1 && len != 0)
	{
		vec[0] /= len;
		vec[1] /= len;
		vec[2] /= len;
	}
}

/*
** takes the point of the camera and gives it to the pix struct
*/

void	update_ray_p(float *cam_p, t_pv *ray)
{
	ray->p[0] = cam_p[0];
	ray->p[1] = cam_p[1];
	ray->p[2] = cam_p[2];
}

/*
** create the ray vector based on the screen size,
** resolution and wich ixel we are analyzing
*/

void	update_ray_v(int *res, int *pixel, float *scr_s, t_pv *ray)
{
	ray->v[0] = -(scr_s[0] / 2) + (scr_s[0] / (res[0] - 1) * pixel[0]);
	ray->v[1] = (scr_s[1] / 2) - (scr_s[1] / (res[1] - 1) * pixel[1]);
	ray->v[2] = (scr_s[2]);
	normalize(ray->v);
}

/*
** returns the dot product
*/

float	dot_prod(float *vec1, float *vec2)
{
	float	result;
	int		i;

	i = -1;
	result = 0;
	while (++i < 3)
		result += vec1[i] * vec2[i];
	return (result);
}

/*
** multiplies a vector by a scalar returned in result
*/

void	vec_mult(float *vect, float scalar, float *result)
{
	result[0] = scalar * vect[0];
	result[1] = scalar * vect[1];
	result[2] = scalar * vect[2];
}

/*
** subtraction between two vector passed into the resul vector
*/

void	vec_sub(float *vect1, float *vect2, float *result)
{
	result[0] = vect1[0] - vect2[0];
	result[1] = vect1[1] - vect2[1];
	result[2] = vect1[2] - vect2[2];
}

/*
** addition between two vector passed into the resul vector
*/

void	vec_add(float *vect1, float *vect2, float *result)
{
	result[0] = vect1[0] + vect2[0];
	result[1] = vect1[1] + vect2[1];
	result[2] = vect1[2] + vect2[2];
}

/*
** addition between two vector passed into the resul vector
*/

void	vec_neg(float *vect, float *result)
{
	result[0] = -vect[0];
	result[1] = -vect[1];
	result[2] = -vect[2];
}

float	vec_len(float *vect)
{
	return (sqrt(float_abs(pow(vect[0], 2) + pow(vect[1], 2)
		+ pow(vect[2], 2))));
}

/*
** Minimal perpendicular vector between a point and a line
*/

void	min_perp_vec(float *point, float *vector, float *origin, float *normal)
{
	float pa[3];
	float pa_d;
	float pa_dd[3];
	float neg_a[3];
	float neg_a_minus_pa_dd[3];

	vec_sub(point, origin, pa);
	pa_d = dot_prod(pa, vector);
	vec_mult(vector, pa_d, pa_dd);
	vec_neg(origin, neg_a);
	vec_sub(neg_a, pa_dd, neg_a_minus_pa_dd);
	vec_add(neg_a_minus_pa_dd, point, normal);
}

/*
** given an encounter struct the ray and a distance
** updates the poin of intersection
*/

void	update_encounter_p(float t, t_pv *ray, t_pv *enc)
{
	enc->p[0] = ray->p[0] + t * ray->v[0];
	enc->p[1] = ray->p[1] + t * ray->v[1];
	enc->p[2] = ray->p[2] + t * ray->v[2];
}

/*
** updates the light vector toward the encounter point, and normalizes it
*/

void	update_light_v(t_pv *enc, t_pv *lig)
{
	lig->v[0] = -lig->p[0] + enc->p[0];
	lig->v[1] = -lig->p[1] + enc->p[1];
	lig->v[2] = -lig->p[2] + enc->p[2];
	normalize(lig->v);
}

float	light_enc_dist(t_pv *enc, t_pv *lig)
{
	float light_enc[3];

	vec_sub(enc->p, lig->p, light_enc);
	return (vec_len(light_enc));
}

void	update_color(t_pix *px, t_obj *ob, int i)
{
	float			projection;
<<<<<<< HEAD
	float			ra;
	float			light_factor;
	float			light_dist;
	float			ambient;

	projection = -dot_prod(px->enc->v, px->lig->v);
=======
	float			range;	
	float 			light_factor;
	// units taht it turns it into zero
	float			light_power;
	float			light_dist;
	float				ambient;
	float			shadow_range;

	shadow_range = 1;
	if (px->shadow)
		shadow_range = 0.5;

	projection = - dot_prod(px->enc->v, px->lig->v);
>>>>>>> parent of 862c7f6... pre norminette owrking
	if (projection < 0)
		projection = 0;
	light_dist = light_enc_dist(px->enc, px->lig);
<<<<<<< HEAD
	light_factor = 50 / pow(0.2 * light_dist, 2);
=======

	// linear
	light_factor = (- (1 / light_power) * light_dist ) + 1;

	// quadratic with power
	light_factor = light_power / pow(0.1 * light_dist,2);

>>>>>>> parent of 862c7f6... pre norminette owrking
	if (light_factor > 1)
		light_factor = 1;
	ambient = 0.10;
<<<<<<< HEAD
	ra = projection * (1 - ambient) * light_factor + ambient;
	if (px->shadow == 1)
		ra = ambient;
	px->color = rgb_to_ui(ra * ob[i].rgb[0], ra * ob[i].rgb[1], ra * ob[i].rgb[2]);
}

float	check_obj_temp_t(t_pv *ray, t_pv *enc, t_obj ob)
=======

	range = projection * (1 - ambient) * light_factor * shadow_range + ambient;

	if (px->shadow)
		range = ambient;

	// range /= range / 255;

	px->color = rgb_to_ui(range * ob->rgb[0],range * ob->rgb[1],range * ob->rgb[2]);
	// px->color = range;

	}

float check_obj_temp_t(t_pv *ray, t_pv *enc, t_obj ob)
>>>>>>> parent of 862c7f6... pre norminette owrking
{
	float temp_t;

	temp_t = 0;
	if (ob.type == 's')
	{
		temp_t = ray_sphere_encounter(ob.p, ray, enc);
	}
	else if (ob.type == 'o')
	{
		temp_t = ray_cone_encounter(ob.vp, 15, ray, enc);
	}
	else if (ob.type == 'y')
	{
		temp_t = ray_cylinder_encounter(ob.vp, 1, ray, enc);
	}
	else if (ob.type == 'p')
	{
		temp_t = ray_plane_encounter(ob.p, ray, enc);
	}
	return (temp_t);
}

int		loop_obj_shadow(t_pv *enc, t_pv *lig, t_obj *ob, int exc)
{
	int		i;
	float	temp_t;
	t_pv	dummy;
	float	light_dist;

	light_dist = light_enc_dist(enc, lig);
	i = -1;
	temp_t = 0;
	while (ob[++i].type != 'n')
	{
		if (i != exc)
			temp_t = check_obj_temp_t(lig, &dummy, ob[i]);
		if (temp_t > 0 && temp_t < light_dist - 0.001)
			return (1);
	}
	return (0);
}

void	color_point(t_data *dt, int i)
{
	float	dist;
	float	dist_to_obj;
	float	light_dist;
	int		shadow;

	update_light_v(dt->px->enc, dt->px->lig);
	dt->px->shadow = loop_obj_shadow(dt->px->enc, dt->px->lig, dt->ob, i);
	update_color(dt->px, dt->ob, i);
	fill_pixel_res(dt, dt->px->pix_p[0], dt->px->pix_p[1], dt->px->color);
}

void	loop_trough_objs(t_data *dt)
{
	int		i;
	float	temp_t;
	float	t;

	t = 1024;
	i = -1;
	while (dt->ob[++i].type != 'n')
	{
		temp_t = check_obj_temp_t(dt->px->ray, dt->px->enc, dt->ob[i]);
		if (temp_t < t && temp_t != 0)
		{
			t = temp_t;
			color_point(dt, i);
		}
	}
}

void	ray_trace(t_data *dt)
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
			update_ray_v(dt->ca->res, dt->px->pix_p,
			dt->ca->scr_s, dt->px->ray);
			rotate_v(dt->px->ray->v, dt->ca->cam_a);
			loop_trough_objs(dt);
		}
	}
}

float	ray_cylinder_encounter(t_pv cyl, float r, t_pv *ray, t_pv *enc)
{
	float		a;
	float		b;
	float		c;
	float		t;
	float		Dp[3];
	float		Dp_Va;
	float		Dp_VaVa[3];
	float		DpDp_VaVa[3];
	float		v_va;
	float		v_vava[3];
	float		vv_vava[3];

	// Dp = ∆p = p - pa 
	vec_sub(ray->p, cyl.p, Dp);
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
	a = dot_prod(vv_vava, vv_vava);
	b = 2 * dot_prod(vv_vava, DpDp_VaVa);
	c = dot_prod(DpDp_VaVa, DpDp_VaVa) - (r*r);
	t = solve_quadratic(a, b, c);
	if (t == 0)
		return (0);
	update_encounter_p(t, ray, enc);
	min_perp_vec(enc->p, cyl.v, cyl.p, enc->v);
	normalize(enc->v);
	return (t);
}

float	ray_cone_encounter(t_pv cone, int angle, t_pv *ray, t_pv *enc)
{
	float		a;
	float		b;
	float		c;
	float		t;
	float		dp[3];
	float		dp_va;
	float		dp_vava[3];
	float		dpdp_vava[3];
	float		v_va;
	float		v_vava[3];
	float		vv_vava[3];
	float		cos_sqr;
	float		sin_sqr;

	vec_sub(ray->p, cone.p, dp);
	dp_va = dot_prod(dp, cone.v);
	vec_mult(cone.v, dp_va, dp_vava);
	vec_sub(dp, dp_vava, dpdp_vava);
	v_va = dot_prod(ray->v, cone.v);
	vec_mult(cone.v, v_va, v_vava);
	vec_sub(ray->v, v_vava, vv_vava);
	cos_sqr = cos(angle * PI_R) * cos(angle * PI_R);
	sin_sqr = sin(angle * PI_R) * sin(angle * PI_R);
	a = cos_sqr * dot_prod(vv_vava, vv_vava) - (sin_sqr * v_va * v_va);
	b = 2 * cos_sqr * dot_prod(vv_vava, dpdp_vava)
	- (2 * sin_sqr * v_va * dp_va);
	c = cos_sqr * dot_prod(dpdp_vava, dpdp_vava) - (sin_sqr * dp_va * dp_va);
	t = solve_quadratic(a, b, c);
	if (t == 0)
		return (0);
	update_encounter_p(t, ray, enc);
	min_perp_vec(enc->p, cone.v, cone.p, enc->v);
	normalize(enc->v);
	return (t);
}

float	ray_sphere_encounter(float *sphere, t_pv *ray, t_pv *enc)
{
	int			i;
	float		a;
	float		b;
	float		c;
	float		b_vec[3];
	float		length;
	float		t;

	a = 1;
	i = -1;
	while (++i < 3)
		b_vec[i] = ray->v[i] * (ray->p[i] - sphere[i]);
	b = 2 * (b_vec[0] + b_vec[1] + b_vec[2]);
	length = pow(ray->p[0] - sphere[0], 2) +
				pow(ray->p[1] - sphere[1], 2) +
				pow(ray->p[2] - sphere[2], 2);
	c = length - pow(sphere[3], 2);
	t = solve_quadratic(a, b, c);
	if (t == 0)
		return (0);
	update_encounter_p(t, ray, enc);
	vec_sub(enc->p, sphere, enc->v);
	normalize(enc->v);
	return (t);
}

float	solve_quadratic(float a, float b, float c)
{
	float det;
	float dist;
	float t[2];
	float det_error;

	det_error = 0.1;
	det = pow(b, 2) - (4 * a * c);
	if (det < 0)
		return (0);
	else if (det == 0)
	{
		dist = -(b / (2 * a));
		if (dist < 0)
			return (0);
	}
	else if (a == 0)
		return (0);
	else
	{
		t[0] = (-b - sqrt(det)) / (2 * a);
		t[1] = (-b + sqrt(det)) / (2 * a);
		if (t[0] < t[1] && t[0] > 0)
			dist = t[0];
		else if (t[1] < t[0] && t[1] > 0)
			dist = t[1];
		else if (t[0] > 0)
			dist = t[0];
		else if (t[1] > 0)
			dist = t[1];
	}
	return (dist);
}

float	ray_plane_encounter(float *plane, t_pv *ray, t_pv *enc)
{
	float	t;

	t = -(plane[0] * ray->p[0] + plane[1] * ray->p[1] + plane[2] * ray->p[2]
		- plane[3])
	/ (plane[0] * ray->v[0] + plane[1] * ray->v[1] + plane[2] * ray->v[2]);
	if (t > 0)
	{
		update_encounter_p(t, ray, enc);
		enc->v[0] = plane[0];
		enc->v[1] = plane[1];
		enc->v[2] = plane[2];
		normalize(enc->v);
		return (t);
	}
	return (0);
}

void	rotate_z(float degree, float *xp, float *yp, float *zp)
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

void	rotate_v(float *vec, float *angles)
{
	rotate_x(angles[0], &vec[0], &vec[1], &vec[2]);
	rotate_y(angles[1], &vec[0], &vec[1], &vec[2]);
	rotate_z(angles[2], &vec[0], &vec[1], &vec[2]);
}

<<<<<<< HEAD
=======
/*
	TODO:
	ALSO NOT: fix the ft_atof (maybe not necessary) 1-2 h
	Norminette this shit 4h
	bring color in 2h
	check fof breaking the input
*/

>>>>>>> parent of 862c7f6... pre norminette owrking
int		main(int ac, char **av)
{
	static t_data	*dt;
	static t_mlx	*md;

	dt = init_data(dt);
	if (!get_input(dt, ac, av))
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
