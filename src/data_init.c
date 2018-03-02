/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 17:07:52 by nmanzini          #+#    #+#             */
/*   Updated: 2018/03/02 16:53:16 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_mlx	*mlx_data_init_return(t_mlx *md)
{
	static t_mlx		actual_md;
	static t_img_prm	actual_ip;

	md = &actual_md;
	md->ip = &actual_ip;
	md->width = WIDTH;
	md->height = HEIGHT;
	md->mlx = mlx_init();
	md->win = mlx_new_window(md->mlx, md->width, md->height, "RTv1");
	make_image(md);
	return (md);
}

void	cfg_setup(t_cfg *cf)
{

}

t_cfg	*cfg_data_init(t_cfg *cf)
{
	static t_cfg	actual_cfg;

	cf = &actual_cfg;
	cfg_setup(cf);
	return (cf);
}

t_str	*str_data_init(t_str *st)
{
	static t_str actual_st;

	st = &actual_st;
	st->x = 18;
	st->y = 18;
	return (st);
}

void	cam_data_update(t_cam *ca)
{
	// screen sizes: 2 = distance, 0 = x size in real dimension, 1 = y size in real dimension
	ca->scr_s[2] = 1;
	ca->scr_s[0] = tan(ca->fov / 2 * PI_R) * ca->scr_s[2];
	ca->scr_s[1] = ca->scr_s[0] / (float) ca->res[0] * ca->res[1];
}

void	*cam_data_init(t_cam *ca)
{
	static t_cam	actual_ca;

	ca = &actual_ca;

	ca->max_depth = 20;

	// actual camera sensor resolution;
	ca->res[0] = WIDTH / 2;
	ca->res[1] = HEIGHT / 2;

	//fov angle
	ca->fov = 90;

	// camera position xyz
	ca->cam_p[0] = 0;
	ca->cam_p[1] = 0;
	ca->cam_p[2] = -5;

	// camera vector direction xyz
	// NOT IN USE
	ca->cam_v[0] = 0;
	ca->cam_v[1] = 0;
	ca->cam_v[2] = 1;

	// camera angles in degrees 
	ca->cam_a[0] = 0;
	ca->cam_a[1] = 0;
	ca->cam_a[2] = 0;

	cam_data_update(ca);

	return(ca);
}

void	*pix_data_init(t_pix *px)
{
	static t_pix	actual_px;
	static t_pv		actual_ray;
	static t_pv		actual_enc;
	static t_pv		actual_lig;

	px = &actual_px;
	px->ray = &actual_ray;
	px->enc = &actual_enc;
	px->lig = &actual_lig;
	// point of origin of the ray
	px->ray_p[0] = 0;
	px->ray_p[1] = 0;
	px->ray_p[2] = 0;

	// vector of  the ray
	px->ray_v[0] = 0;
	px->ray_v[1] = 0;
	px->ray_v[2] = 0;

	// ___________________________________
	// 

	// pointvector struct of the ray
	px->ray->p[0] = 0;
	px->ray->p[1] = 0;
	px->ray->p[2] = 0;

	px->ray->v[0] = 0;
	px->ray->v[1] = 0;
	px->ray->v[2] = 0;

	// pointvector struct of the encounter
	px->enc->p[0] = 0;
	px->enc->p[1] = 0;
	px->enc->p[2] = 0;

	px->enc->v[0] = 0;
	px->enc->v[1] = 0;
	px->enc->v[2] = 0;

	// pointvector struct of the encounter
	px->lig->p[0] = 5;
	px->lig->p[1] = 0;
	px->lig->p[2] = 0;

	px->lig->v[0] = 0;
	px->lig->v[1] = 0;
	px->lig->v[2] = 0;

	// ___________________________________
	// 

	// point of intersection with an obj
	px->int_p[0] = 0;
	px->int_p[1] = 0;
	px->int_p[2] = 0;

	// Normal of point of intersection
	px->int_n[0] = 0;
	px->int_n[1] = 0;
	px->int_n[2] = 0;

	// Vector from light to point
	px->lig_v[0] = 0;
	px->lig_v[1] = 0;
	px->lig_v[2] = 0;

	px->color = 0;
	return (px);
}

t_scn	*scn_data_init(t_scn *sc)
{
	static t_scn	actual_sc;

	sc = &actual_sc;
	// sphere data
	sc->sphere[0] = 0;
	sc->sphere[1] = 0;
	sc->sphere[2] = 0;
	sc->sphere[3] = 2;

	sc->x_sphere[0] = 2;
	sc->x_sphere[1] = 0;
	sc->x_sphere[2] = 0;
	sc->x_sphere[3] = 0.2;

	sc->y_sphere[0] = 0;
	sc->y_sphere[1] = 2;
	sc->y_sphere[2] = 0;
	sc->y_sphere[3] = 0.2;

	sc->z_sphere[0] = 0;
	sc->z_sphere[1] = 0; 
	sc->z_sphere[2] = 2;
	sc->z_sphere[3] = 0.2;

	sc->a_sphere[0] = 0;
	sc->a_sphere[1] = 0;
	sc->a_sphere[2] = 0;
	sc->a_sphere[3] = 0.2;

	sc->plane[0] = 1;
	sc->plane[1] = -1;

	sc->plane2[0] = 1;
	sc->plane2[1] = -1;

	// sc->light[0] = 2;
	// sc->light[1] = 2;
	// sc->light[2] = -1;

	sc->box[0] = 0.0;
	sc->box[1] = 0.0;
	sc->box[2] = 0.0;
	sc->box[3] = 1.0;
	sc->box[4] = 2.0;
	sc->box[5] = 3.0;

	sc->surface[0] = 3.5;
	sc->surface[1] = 0;
	sc->surface[2] = 5.5;
	sc->surface[3] = 3;
	sc->surface[4] = 0;
	sc->surface[5] = 5;

	sc->cone.p[0] = 0;
	sc->cone.p[1] = 0;
	sc->cone.p[2] = 0;
	sc->cone.v[0] = 0;
	sc->cone.v[1] = 1;
	sc->cone.v[2] = 0;
	return (sc);
}

t_data	*init_data(t_data *dt)
{
	// commented the mlx structs and initiated outside to avoid changin window
	// if the
	static t_data		actual_dt;
	// static t_mlx		*md;
	static t_cfg		*cf;
	static t_str		*st;
	static t_scn		*sc;
	static t_cam		*ca;
	static t_pix		*px;

	dt = &actual_dt;
	// dt->md = mlx_data_init_return(md);
	dt->cf = cfg_data_init(cf);
	dt->st = str_data_init(st);
	dt->sc = scn_data_init(sc);
	dt->ca = cam_data_init(ca);
	dt->px = pix_data_init(px);
	return (dt);
}
