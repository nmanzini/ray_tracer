/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_keys_general.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 17:02:37 by nmanzini          #+#    #+#             */
/*   Updated: 2018/02/20 16:54:42 by nmanzini         ###   ########.fr       */
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
		ft_putendl("W		move forward\n");
		dt->sc->cam_p[2] += 0.5;
	}
	else if (keycode == 1)
	{
		ft_putendl("S		move backward\n");
		dt->sc->cam_p[2] -= 0.5;
	}
	else if (keycode == 0)
	{
		ft_putendl("A		move left\n");
		dt->sc->cam_p[0] -= 0.5;
	}
	else if (keycode == 2)
	{
		ft_putendl("D		move right\n");
		dt->sc->cam_p[0] += 0.5;
	}
	else if (keycode == 12)
	{
		ft_putendl("Q		move down\n");
		dt->sc->cam_p[1] -= 0.5;
	}
	else if (keycode == 14)
	{
		ft_putendl("E		move up\n");
		dt->sc->cam_p[1] += 0.5;
	}
}

void	call_keys_camera_rot(int keycode, t_data *dt)
{
	if (keycode == 124)
	{
		ft_putendl("->		rotate right\n");
		dt->sc->cam_a[1] += 5;
	}
	else if (keycode == 123)
	{
		ft_putendl("<-		rotate left\n");
		dt->sc->cam_a[1] -= 5;
	}
	else if (keycode == 126)
	{
		ft_putendl("^		rotate down\n");
		dt->sc->cam_a[0] -= 5;
	}
	else if (keycode == 125)
	{
		ft_putendl("v		rotate up\n");
		dt->sc->cam_a[0] += 5;
	}
}

void	call_keys_camera_lens(int keycode, t_data *dt)
{
	if (keycode == 78)
	{
		ft_putendl("-		smaller fov\n");
		dt->sc->fov += 10;
	}
	else if (keycode == 69)
	{
		ft_putendl("+		bigger fov\n ");
		dt->sc->fov -= 10;
	}
	ft_putnbr(dt->sc->fov);
	ft_putchar(10);
}

int		call_keys(int keycode, t_data *dt)
{
	call_keys_general(keycode, dt);
	call_keys_camera_mov(keycode, dt);
	call_keys_camera_rot(keycode, dt);
	call_keys_camera_lens(keycode, dt);
	display(dt);
	return (0);
}
