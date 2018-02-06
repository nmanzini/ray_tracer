/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 17:07:52 by nmanzini          #+#    #+#             */
/*   Updated: 2018/02/06 14:43:01 by nmanzini         ###   ########.fr       */
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
	//camera position
	sc->cam_p[0] = 0;
	sc->cam_p[1] = 0;
	sc->cam_p[2] = -10;
	//camera direction
	sc->cam_v[0] = 0;
	sc->cam_v[1] = 0;
	sc->cam_v[2] = 1;
	//fov angle
	sc->fov = 60;
	// actual screen resolution;
	sc->res[0] = WIDTH;
	sc->res[1] = HEIGHT;
	// screen sizes: 2 = distance, 0 = x size in real diension, 1 = y size in real dimensions
	sc->screen_s[2] = 1;
	sc->screen_s[0] = sin(sc->fov / 2 * PI_R) * sc->screen_s[2] = 1;
	sc->screen_s[1] = sc->screen_s[0] / (float) sc->res[0] * sc->res[1];
	
	return (sc);
}

t_data	*init_data(t_data *dt)
{
	static t_data		actual_dt;
	static t_mlx		*md;
	static t_cfg		*cf;
	static t_str		*st;
	static t_scn		*sc;

	dt = &actual_dt;
	dt->md = mlx_data_init_return(md);
	dt->cf = cfg_data_init(cf);
	dt->st = str_data_init(st);
	dt->sc = scn_data_init(sc);
	return (dt);
}
