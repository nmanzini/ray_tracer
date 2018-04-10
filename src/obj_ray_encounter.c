/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_ray_encounter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:39:13 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/10 21:46:53 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
