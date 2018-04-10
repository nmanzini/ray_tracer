/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:11:25 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/10 21:47:07 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
