/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 17:07:52 by nmanzini          #+#    #+#             */
/*   Updated: 2018/02/20 16:51:13 by nmanzini         ###   ########.fr       */
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
	md->win = mlx_new_window(md->mlx, md->width, md->height, "fractol");
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

t_scn	*scn_data_init(t_scn *sc)
{
	static t_scn	actual_sc;

	sc = &actual_sc;
	// max_depth
	sc->max_depth = 10;

	//camera position
	sc->cam_p[0] = 1;
	sc->cam_p[1] = 1;
	sc->cam_p[2] = -5;

	// camera startingdirection
	// NOT IN USE
	sc->cam_v[0] = 0;
	sc->cam_v[1] = 0;
	sc->cam_v[2] = 1;

	// camera angles 
	sc->cam_a[0] = 0;
	sc->cam_a[1] = 0;
	sc->cam_a[2] = 0;

	// sphere data
	sc->sphere[0] = 2;
	sc->sphere[1] = 2;
	sc->sphere[2] = 2;
	sc->sphere[2] = 12;

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

	//fov angle
	sc->fov = 90;

	// actual screen resolution;
	sc->res[0] = WIDTH;
	sc->res[1] = HEIGHT;
	// screen sizes: 2 = distance, 0 = x size in real dimension, 1 = y size in real dimension
	sc->screen_s[2] = 1;
	sc->screen_s[0] = tan(sc->fov / 2 * PI_R) * sc->screen_s[2];
	sc->screen_s[1] = sc->screen_s[0] / (float) sc->res[0] * sc->res[1];
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

	dt = &actual_dt;
	// dt->md = mlx_data_init_return(md);
	dt->cf = cfg_data_init(cf);
	dt->st = str_data_init(st);
	dt->sc = scn_data_init(sc);
	return (dt);
}
