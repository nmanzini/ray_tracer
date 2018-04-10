/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:18:44 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/10 21:47:25 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
