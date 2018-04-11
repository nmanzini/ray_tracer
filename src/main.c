/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:34:26 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/11 10:53:08 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float	float_abs(float f)
{
	if (f < 0)
		return (-f);
	else
		return (f);
}

/*
** generate rays and call for a loop of all the objs to chekck if they hit
*/

void	ray_trace(t_data *dt)
{
	float	t;
	float	temp_t;

	cam_data_update(dt->ca);
	update_ray_p(dt->ca->cam_p, dt->px->ray);
	dt->px->pix_p[1] = -1;
	while (++dt->px->pix_p[1] < dt->ca->res[1])
	{
		dt->px->pix_p[0] = -1;
		while (++dt->px->pix_p[0] < dt->ca->res[0])
		{
			updt_ray_v(dt->ca->res, dt->px->pix_p, dt->ca->scr_s, dt->px->ray);
			rotate_v(dt->px->ray->v, dt->ca->cam_a);
			loop_trough_objs(dt);
		}
	}
}

int		main(int ac, char **av)
{
	static t_data	*dt;
	static t_mlx	*md;

	dt = init_data(dt);
	if (!get_input(dt, ac, av))
	{
		ft_putstr("RTv1 starting\n");
		dt->md = mlx_data_init_return(md);
		display(dt);
		mlx_key_hook(dt->md->win, call_keys, dt);
		mlx_loop(dt->md->mlx);
	}
	else
	{
		ft_putstr("Error reading the file.\nExiting.\n");
		exit(0);
	}
	return (0);
}
