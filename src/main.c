/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:34:26 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/10 17:40:41 by nmanzini         ###   ########.fr       */
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
** normilizes a 3 dim array of floats.
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
** create the ray vector based on the screen size, resolution and wich pixel
** we are analyzing
*/

void	updt_ray_v(int *res, int *pixel, float *scr_s, t_pv *ray)
{
	ray->v[0] = -(scr_s[0] / 2) + (scr_s[0] / (res[0] - 1) * pixel[0]);
	ray->v[1] = +(scr_s[1] / 2) - (scr_s[1] / (res[1] - 1) * pixel[1]);
	ray->v[2] = +(scr_s[2]);
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
	float len2;

	len2 = float_abs(pow(vect[0], 2) + pow(vect[1], 2) + pow(vect[2], 2));
	return (sqrt(len2));
}

/*
** Minimal perpendicular vector between a point and a vector
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
** given an encounter struct the ray and a distance,
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

/*
** return the distance between ligth point and encounter point
*/

float	light_enc_dist(t_pv *enc, t_pv *lig)
{
	float light_enc[3];

	vec_sub(enc->p, lig->p, light_enc);
	return (vec_len(light_enc));
}

/*
** update the color in the pixel based on the attack angle, ligth distance
** power, light power and ambient light
*/

void	update_color(t_pix *px, t_obj *ob)
{
	float			projection;
	float			ra;
	float			light_factor;
	float			light_power;
	float			ambient;

	projection = -dot_prod(px->enc->v, px->lig->v);
	if (projection < 0)
		projection = 0;
	light_power = 150;
	light_factor = light_power / pow(0.5 * light_enc_dist(px->enc, px->lig), 2);
	if (light_factor > 1)
		light_factor = 1;
	ambient = 0.10;
	ra = projection * (1 - ambient) * light_factor + ambient;
	if (px->shadow)
		ra = ambient;
	px->color = rgb_to_ui(ra * ob->rgb[0], ra * ob->rgb[1], ra * ob->rgb[2]);
}

/*
** returns the encounter of a ray and a objec, updates the encounter vector
*/

float	check_obj_temp_t(t_pv *ray, t_pv *enc, t_obj ob)
{
	float temp_t;

	temp_t = 0;
	if (ob.type == 's')
		temp_t = ray_sphere_encounter(ob.p, ray, enc);
	else if (ob.type == 'o')
		temp_t = ray_cone_encounter(ob.vp, ob.p[0], ray, enc);
	else if (ob.type == 'y')
		temp_t = ray_cylinder_encounter(ob.vp, ob.p[0], ray, enc);
	else if (ob.type == 'p')
		temp_t = ray_plane_encounter(ob.p, ray, enc);
	return (temp_t);
}

/*
** loops trough objs to check if they are in between the object and
** a source of light,
*/

int		loop_obj_shadow(t_pv *enc, t_pv *lig, t_obj *ob, int exc)
{
	int		i;
	float	temp_t;
	t_pv	dummy;
	float	light_dist;

	light_dist = light_enc_dist(enc, lig);
	i = -1;
	while (ob[++i].type != 'n')
	{
		if (i != exc)
			temp_t = check_obj_temp_t(lig, &dummy, ob[i]);
		if (temp_t > 0 && temp_t < light_dist - 0.001)
			return (1);
	}
	return (0);
}

/*
** generates some variable for the update color functions
** and fill a pixel with that colour
*/

void	color_point(t_data *dt, int i)
{
	float	dist;
	float	dist_to_obj;
	float	light_dist;
	int		shadow;

	update_light_v(dt->px->enc, dt->px->lig);
	dt->px->shadow = loop_obj_shadow(dt->px->enc, dt->px->lig, dt->ob, i);
	update_color(dt->px, &dt->ob[i]);
	fill_pixel_res(dt, dt->px->pix_p[0], dt->px->pix_p[1], dt->px->color);
}

/*
**	loop trought objects and color if their t is less than the one before 
*/

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

/*
** generate rays and call for a loop of all the objs to chekck if they hit
*/

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
			updt_ray_v(dt->ca->res, dt->px->pix_p, dt->ca->scr_s, dt->px->ray);
			rotate_v(dt->px->ray->v, dt->ca->cam_a);
			loop_trough_objs(dt);
		}
	}
}

/*
** function for cylinder
*/

void	get_dpdp_vava(t_pv cyl, t_pv *ray, float *dd_vava)
{
	float		d[3];
	float		d_va;
	float		dp_vava[3];

	vec_sub(ray->p, cyl.p, d);
	d_va = dot_prod(d, cyl.v);
	vec_mult(cyl.v, d_va, dp_vava);
	vec_sub(d, dp_vava, dd_vava);
}

/*
** function for cylinder
*/

void	get_vv_vava(t_pv cyl, t_pv *ray, float *vv_vava)
{
	float		v_va;
	float		v_vava[3];

	v_va = dot_prod(ray->v, cyl.v);
	vec_mult(cyl.v, v_va, v_vava);
	vec_sub(ray->v, v_vava, vv_vava);
}

/*
** return cylinder encounter distance, and update the encounter vector
*/

float	ray_cylinder_encounter(t_pv cyl, float r, t_pv *ray, t_pv *enc)
{
	float		q[3];
	float		t;
	float		dd_vava[3];
	float		vv_vava[3];

	get_dpdp_vava(cyl, ray, dd_vava);
	get_vv_vava(cyl, ray, vv_vava);
	q[0] = dot_prod(vv_vava, vv_vava);
	q[1] = 2 * dot_prod(vv_vava, dd_vava);
	q[2] = dot_prod(dd_vava, dd_vava) - (r * r);
	t = solve_quadratic(q[0], q[1], q[2]);
	if (t == 0)
		return (0);
	update_encounter_p(t, ray, enc);
	min_perp_vec(enc->p, cyl.v, cyl.p, enc->v);
	normalize(enc->v);
	return (t);
}

/*
** function for cone
*/

float	dot_mult_sub(float *vec, t_pv shape, float *xx_vava)
{
	float		x_vava[3];
	float		x_va;

	x_va = dot_prod(vec, shape.v);
	vec_mult(shape.v, x_va, x_vava);
	vec_sub(vec, x_vava, xx_vava);
	return (x_va);
}

/*
** get intersection of cone
*/

float	get_t_cone(t_pv cone, float *cs_sr, t_pv *ray, float *q)
{
	float		d[3];
	float		d_va;
	float		dd_vava[3];
	float		v_va;
	float		vv_vava[3];

	vec_sub(ray->p, cone.p, d);
	d_va = dot_mult_sub(d, cone, dd_vava);
	v_va = dot_mult_sub(ray->v, cone, vv_vava);
	q[0] = cs_sr[0] * dot_prod(vv_vava, vv_vava) - (cs_sr[1] * pow(v_va, 2));
	q[1] = cs_sr[0] * dot_prod(vv_vava, dd_vava) - (cs_sr[1] * v_va * d_va);
	q[2] = cs_sr[0] * dot_prod(dd_vava, dd_vava) - (cs_sr[1] * pow(d_va, 2));
	return (solve_quadratic(q[0], 2 * q[1], q[2]));
}

/*
** return distance of coune encounter, and update the encounter vector
*/

float	ray_cone_encounter(t_pv cone, int angle, t_pv *ray, t_pv *enc)
{
	float		q[3];
	float		t;
	float		cs_sr[2];

	cs_sr[0] = cos(angle * PI_R) * cos(angle * PI_R);
	cs_sr[1] = sin(angle * PI_R) * sin(angle * PI_R);
	t = get_t_cone(cone, cs_sr, ray, q);
	if (t == 0)
		return (0);
	update_encounter_p(t, ray, enc);
	min_perp_vec(enc->p, cone.v, cone.p, enc->v);
	normalize(enc->v);
	return (t);
}

/*
** return distance of sphere encounter, and update the encounter vector
*/

float	ray_sphere_encounter(float *sphere, t_pv *ray, t_pv *enc)
{
	int			i;
	float		q[3];
	float		b_vec[3];
	float		length;
	float		t;

	q[0] = 1;
	i = -1;
	while (++i < 3)
		b_vec[i] = ray->v[i] * (ray->p[i] - sphere[i]);
	q[1] = 2 * (b_vec[0] + b_vec[1] + b_vec[2]);
	length = pow(ray->p[0] - sphere[0], 2) +
				pow(ray->p[1] - sphere[1], 2) +
				pow(ray->p[2] - sphere[2], 2);
	q[2] = length - pow(sphere[3], 2);
	t = solve_quadratic(q[0], q[1], q[2]);
	if (t == 0)
		return (0);
	update_encounter_p(t, ray, enc);
	vec_sub(enc->p, sphere, enc->v);
	normalize(enc->v);
	return (t);
}

/*
** solve quadratic function, return zero if no solutions
** returns the minor positive
*/

float	solve_quadratic(float a, float b, float c)
{
	float det;
	float dist;
	float t[2];

	det = pow(b, 2) - (4 * a * c);
	if (det == 0 && a != 0)
	{
		dist = -(b / (2 * a));
		if (dist > 0)
			return (dist);
	}
	else if (det > 0 && a != 0)
	{
		t[0] = (-b - sqrt(det)) / (2 * a);
		t[1] = (-b + sqrt(det)) / (2 * a);
		if (t[0] < t[1] && t[0] > 0)
			return (t[0]);
		else if (t[1] < t[0] && t[1] > 0)
			return (t[1]);
		else if (t[0] > 0)
			return (t[0]);
		else if (t[1] > 0)
			return (t[1]);
	}
	return (0);
}

/*
** return distance encounter of a ray and a plane, updates he enc vector
*/

float	ray_plane_encounter(float *plane, t_pv *ray, t_pv *enc)
{
	float	t;

	t = -(plane[0] * ray->p[0] + plane[1] * ray->p[1] + plane[2] * ray->p[2]
		- plane[3]) /
	(plane[0] * ray->v[0] + plane[1] * ray->v[1] + plane[2] * ray->v[2]);
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
