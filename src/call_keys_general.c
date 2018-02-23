/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_keys_general.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 17:02:37 by nmanzini          #+#    #+#             */
/*   Updated: 2018/02/23 12:25:39 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

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

void	call_keys_camera_mov(int keycode, t_data *dt)
{
	if (keycode == 13)
	{
		ft_putendl("W		move forward");
		dt->ca->cam_p[2] += 0.5;
	}
	else if (keycode == 1)
	{
		ft_putendl("S		move backward");
		dt->ca->cam_p[2] -= 0.5;
	}
	else if (keycode == 0)
	{
		ft_putendl("A		move left");
		dt->ca->cam_p[0] -= 0.5;
	}
	else if (keycode == 2)
	{
		ft_putendl("D		move right");
		dt->ca->cam_p[0] += 0.5;
	}
	else if (keycode == 12)
	{
		ft_putendl("Q		move down");
		dt->ca->cam_p[1] -= 0.5;
	}
	else if (keycode == 14)
	{
		ft_putendl("E		move up");
		dt->ca->cam_p[1] += 0.5;
	}
}

void	call_keys_camera_rot(int keycode, t_data *dt)
{
	if (keycode == 124)
	{
		ft_putendl("->		rotate right");
		dt->ca->cam_a[1] += 10;
	}
	else if (keycode == 123)
	{
		ft_putendl("<-		rotate left");
		dt->ca->cam_a[1] -= 10;
	}
	else if (keycode == 126)
	{
		ft_putendl("^		rotate up");
		dt->ca->cam_a[0] -= 10;
	}
	else if (keycode == 125)
	{
		ft_putendl("v		rotate down");
		dt->ca->cam_a[0] += 10;
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
		ft_putendl("[		smaller resolution");
		if (dt->ca->res[0] != 16 && dt->ca->res[1] != 16)
		{
			dt->ca->res[0] /= 2;
			dt->ca->res[1] /= 2;
		}
	}
	else if (keycode == 30)
	{
		ft_putendl("]		bigger resolution");
		if (dt->ca->res[0] < WIDTH && dt->ca->res[1] < HEIGHT)
		{
			dt->ca->res[0] *= 2;
			dt->ca->res[1] *= 2;
		}
	}
}

int		call_keys(int keycode, t_data *dt)
{
	call_keys_general(keycode, dt);
	call_keys_camera_mov(keycode, dt);
	call_keys_camera_rot(keycode, dt);
	call_keys_camera_lens(keycode, dt);
	call_keys_resolution(keycode, dt);
	display(dt);
	return (0);
}
