/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicola <nicola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 17:07:52 by nmanzini          #+#    #+#             */
/*   Updated: 2018/05/08 12:31:40 by nicola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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

/*
** fills in the size of the screen in fornt of the camera.
** screen sizes: 2 = distance, 0 = x size in real dimension,
**  1 = y size in real dimension
*/

void	cam_data_update(t_cam *ca)
{
	ca->scr_s[2] = 1;
	ca->scr_s[0] = tan(ca->fov / 2 * PI_R) * ca->scr_s[2];
	ca->scr_s[1] = ca->scr_s[0] / (float)ca->res[0] * ca->res[1];
}

t_cam	*cam_data_init(t_cam *ca)
{
	static t_cam	actual_ca;

	ca = &actual_ca;
	ca->max_depth = 2048;
	ca->res_factor = 1;
	ca->res[0] = WIDTH / ca->res_factor;
	ca->res[1] = HEIGHT / ca->res_factor;
	ca->fov = 90;
	ca->cam_p[0] = 0;
	ca->cam_p[1] = 0;
	ca->cam_p[2] = -10;
	ca->cam_a[0] = 0;
	ca->cam_a[1] = 0;
	ca->cam_a[2] = 0;
	cam_data_update(ca);
	return (ca);
}

t_pix	*pix_data_init(t_pix *px)
{
	static t_pix	actual_px;
	static t_pv		actual_ray;
	static t_pv		actual_enc;
	static t_pv		actual_lig;

	px = &actual_px;
	px->ray = &actual_ray;
	px->enc = &actual_enc;
	px->lig = &actual_lig;
	return (px);
}

t_data	*init_data(t_data *dt)
{
	static t_data		actual_dt;
	static t_cam		*ca;
	static t_pix		*px;

	dt = &actual_dt;
	dt->ca = cam_data_init(ca);
	dt->px = pix_data_init(px);
	return (dt);
}
