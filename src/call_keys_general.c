/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_keys_general.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 17:02:37 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/11 15:53:34 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	call_keys_general(int keycode, t_data *dt)
{
	if (keycode == 53)
	{
		ft_putendl("ESC		Bye bye!\n");
		mlx_destroy_window(dt->md->mlx, dt->md->win);
		exit(0);
	}
	else if (keycode == 50)
	{
		ft_putendl("`		Bye bye and may 0 leaks be with you\n");
		mlx_destroy_window(dt->md->mlx, dt->md->win);
		while (1)
			;
	}
}

void	call_keys_camera_lens(int keycode, t_data *dt)
{
	if (keycode == 78)
	{
		ft_putendl("-		smaller fov");
		dt->ca->fov += 10;
	}
	else if (keycode == 69)
	{
		ft_putendl("+		bigger fov");
		dt->ca->fov -= 10;
	}
}

void	call_keys_resolution(int keycode, t_data *dt)
{
	if (keycode == 33)
	{
		ft_putendl("[		lower resolution");
		if (dt->ca->res_factor != 64)
			dt->ca->res_factor *= 2;
		else
			ft_putendl("[		minimum resolution reached");
		dt->ca->res[0] = WIDTH / dt->ca->res_factor;
		dt->ca->res[1] = HEIGHT / dt->ca->res_factor;
	}
	else if (keycode == 30)
	{
		ft_putendl("]		higher resolution");
		if (dt->ca->res_factor != 1)
			dt->ca->res_factor /= 2;
		else
			ft_putendl("]		maximum resolution reached");
		dt->ca->res[0] = WIDTH / dt->ca->res_factor;
		dt->ca->res[1] = HEIGHT / dt->ca->res_factor;
	}
}

int		call_keys(int keycode, t_data *dt)
{
	if (keycode == 37)
	{
		ft_putendl("l		move ligth right");
		dt->px->lig->p[0] += 3;
	}
	if (keycode == 38)
	{
		ft_putendl("j		move ligth left");
		dt->px->lig->p[0] -= 3;
	}
	call_keys_general(keycode, dt);
	call_keys_camera_mov(keycode, dt);
	call_keys_camera_mov2(keycode, dt);
	call_keys_camera_rot(keycode, dt);
	call_keys_camera_lens(keycode, dt);
	call_keys_resolution(keycode, dt);
	display(dt);
	return (0);
}
