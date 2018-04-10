/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:14:02 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/10 21:47:20 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
