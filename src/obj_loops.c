/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_loops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:30:39 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/12 14:45:11 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** update the color in the pixel based on the attack angle, ligth distance
** power, light power and ambient light
*/

void	update_color(t_pix *px, t_obj *ob)
{
	float			projection;
	float			ra;
	float			light_factor;
	float			shadow;
	float			ambient;

	projection = -dot_prod(px->enc->v, px->lig->v);
	shadow = 1;
	ambient = 0.10;
	light_factor = 100 / pow(0.5 * light_enc_dist(px->enc, px->lig), 2);
	if (light_factor > 1)
		light_factor = 1;
	if (projection < 0)
		projection = 0;
	if (px->shadow)
		shadow = SHAD_LIGHT;
	ra = projection * (1 - ambient) * light_factor * shadow + ambient;
	px->color = rgb_to_ui(ra * ob->rgb[0], ra * ob->rgb[1], ra * ob->rgb[2]);
}

/*
** returns the encounter of a ray and a objec, updates the encounter vector
*/

float	check_obj_temp_t(t_pv *ray, t_pv *enc, t_obj ob)
{
	float temp_t;

	temp_t = 0;
	if (ob.type == 's' && ob.active == 1)
		temp_t = ray_sphere_encounter(ob.p, ray, enc);
	else if (ob.type == 'o' && ob.active == 1)
		temp_t = ray_cone_encounter(ob.vp, ob.p[0], ray, enc);
	else if (ob.type == 'y' && ob.active == 1)
		temp_t = ray_cylinder_encounter(ob.vp, ob.p[0], ray, enc);
	else if (ob.type == 'p' && ob.active == 1)
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

	t = dt->ca->max_depth;
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
