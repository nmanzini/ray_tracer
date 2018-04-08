/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 00:08:38 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/09 00:08:46 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
	** 
	*/

void	print_vector(float *vec, char *str)
{
	// print a 3 dim vector of floats and its length
	float len;

	len = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	printf("x %f, y %f, z %f len %f \"%s\"\n",vec[0], vec[1], vec[2], len, str);
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
	vec_sub(ray->p, cone.p, Dp);
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
	a = cos_sqr * dot_prod(vv_vava, vv_vava) - (sin_sqr * v_va * v_va);
	b = 2 * cos_sqr * dot_prod(vv_vava, DpDp_VaVa) - (2 * sin_sqr * v_va * Dp_Va);
	c = cos_sqr * dot_prod(DpDp_VaVa, DpDp_VaVa) - (sin_sqr * Dp_Va * Dp_Va);
	t = solve_quadratic(a, b, c);
	if (t == 0)
		return (0);
	update_encounter_p(t, ray, enc);
	min_perp_vec(enc->p, cone.v, cone.p, enc->v);
	normalize(enc->v);
	return (t);
}

void	min_perp_vec(float *point, float *vector, float *origin, float *normal)
{
	float pa[3];
	float pa_d;
	float pa_dd[3];
	float neg_a[3];
	float neg_a_minus_pa_dd[3];

	// (P-a)
	vec_sub(point, origin,pa);
	// (P-a).D)
	pa_d = dot_prod(pa, vector);
	// ((P-a).D)D
	vec_mult(vector, pa_d, pa_dd);
	// -a
	vec_neg(origin, neg_a);
	// - a - ((P-a).D)D
	vec_sub(neg_a, pa_dd, neg_a_minus_pa_dd);
	// - a - ((P-a).D)D + P
	vec_add(neg_a_minus_pa_dd, point, normal);
}
