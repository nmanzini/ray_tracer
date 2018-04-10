/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_algebra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:23:12 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/10 21:47:16 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
** returns the length of a vector
*/

float	vec_len(float *vect)
{
	float len2;

	len2 = pow(vect[0], 2) + pow(vect[1], 2) + pow(vect[2], 2);
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
** return the distance between ligth point and encounter point
*/

float	light_enc_dist(t_pv *enc, t_pv *lig)
{
	float light_enc[3];

	vec_sub(enc->p, lig->p, light_enc);
	return (vec_len(light_enc));
}
