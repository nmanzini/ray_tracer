/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 17:07:52 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/06 15:58:09 by nmanzini         ###   ########.fr       */
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
	// fills in the size of the screen in fornt of the camera.
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
	ca->res[0] = WIDTH / 4;
	ca->res[1] = HEIGHT / 4;

	//fov angle
	ca->fov = 90;

	/*
	** asdasdasdasdasd
	*/

	// camera position xyz
	ca->cam_p[0] = 0;
	ca->cam_p[1] = 3;
	ca->cam_p[2] = -15;

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

	// pointvector struct of the light
	px->lig->p[0] = 0;
	px->lig->p[1] = 3;
	px->lig->p[2] = -10;

	px->lig->v[0] = 0;
	px->lig->v[1] = 0;
	px->lig->v[2] = 0;



	px->color = 0;
	return (px);
}

t_scn	*scn_data_init(t_scn *sc)
{
	static t_scn	actual_sc;

	sc = &actual_sc;
	// sphere data
	sc->sphere[0] = 5;
	sc->sphere[1] = 0;
	sc->sphere[2] = 0;
	sc->sphere[3] = 2;

	// axis of plane
	sc->plane[0] = 1;
	// value of axis of plane
	sc->plane[1] = -1;

	sc->cone.p[0] = -5;
	sc->cone.p[1] = 5;
	sc->cone.p[2] = 0;
	sc->cone.v[0] = 1;
	sc->cone.v[1] = 1;
	sc->cone.v[2] = 0;
	normalize(sc->cone.v);

	sc->cylinder.p[0] = 10;
	sc->cylinder.p[1] = 0;
	sc->cylinder.p[2] = 0;
	sc->cylinder.v[0] = 1;
	sc->cylinder.v[1] = 1;
	sc->cylinder.v[2] = 0;
	normalize(sc->cylinder.v);

	// spheres axis

	// sc->x_sphere[0] = 2;
	// sc->x_sphere[1] = 0;
	// sc->x_sphere[2] = 0;
	// sc->x_sphere[3] = 0.2;
	// sc->y_sphere[0] = 0;
	// sc->y_sphere[1] = 2;
	// sc->y_sphere[2] = 0;
	// sc->y_sphere[3] = 0.2;
	// sc->z_sphere[0] = 0;
	// sc->z_sphere[1] = 0; 
	// sc->z_sphere[2] = 2;
	// sc->z_sphere[3] = 0.2;
	// sc->a_sphere[0] = 0;
	// sc->a_sphere[1] = 0;
	// sc->a_sphere[2] = 0;
	// sc->a_sphere[3] = 0.2;

	// box not in use anymore

	// sc->box[0] = 0;
	// sc->box[1] = 0;
	// sc->box[2] = 0;
	// sc->box[3] = 1.0;
	// sc->box[4] = 2.0;
	// sc->box[5] = 3.0;

	// surface not in use anymore

	// sc->surface[0] = 3.5;
	// sc->surface[1] = 0;
	// sc->surface[2] = 5.5;
	// sc->surface[3] = 3;
	// sc->surface[4] = 0;
	// sc->surface[5] = 5;
	return (sc);
}

t_data	*init_data(t_data *dt)
{
	// commented the mlx structs and initiated outside to avoid changin window
	static t_data		actual_dt;
	// static t_mlx		*md;
	static t_cfg		*cf;
	static t_str		*st;
	static t_scn		*sc;
	static t_cam		*ca;
	static t_pix		*px;

	dt = &actual_dt;
	// can cancel v
	dt->cf = cfg_data_init(cf);
	// can cancel v
	dt->st = str_data_init(st);
	// can cancel v
	dt->sc = scn_data_init(sc);
	dt->ca = cam_data_init(ca);
	dt->px = pix_data_init(px);

	int obj_num;
	int i;

	obj_num = 15;

	static t_obj		*ob;

	ob = (t_obj*)malloc(sizeof(t_obj) * (obj_num + 1));
	dt->ob = ob;
	dt->obj_num = obj_num;

	ob[obj_num].type = 'n';

	int x = -10;
	int y = 0;
	int z = 0;

	int step = 5;

	ob[0].type = 'p';
	ob[0].p[0] = 1;
	ob[0].p[1] = -10;
	ob[1].type = 'p';
	ob[1].p[0] = 0;
	ob[1].p[1] = -10;


	i = 2;

	while (i < obj_num)
	{
		if (i % 3 == 0)
			ob[i].type = 's';
		else if (i % 3 == 1)
			ob[i].type = 'o';
		else if (i % 3 == 2)
			ob[i].type = 'y';

		ob[i].p[0] = x;
		ob[i].p[1] = 0;
		ob[i].p[2] = z;
		ob[i].p[3] = 1;
		ob[i].vp.p[0] = x;
		ob[i].vp.p[1] = 0;
		ob[i].vp.p[2] = z;
		ob[i].vp.v[0] = i % 2;
		ob[i].vp.v[1] = 1;
		ob[i].vp.v[2] = 0;
		normalize(ob[i].vp.v);
		ob[i].color = WHITE;
		x += step;
		y += step;
		z += step;

		i++;
	}



	return (dt);
}
