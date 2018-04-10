/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:34:37 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/10 21:47:03 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
