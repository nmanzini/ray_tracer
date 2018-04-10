/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_keys_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 21:42:02 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/10 21:46:18 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	call_keys_camera_mov(int keycode, t_data *dt)
{
	if (keycode == 13)
	{
		ft_putendl("W		move forward");
		dt->ca->cam_p[2] += 2;
	}
	else if (keycode == 1)
	{
		ft_putendl("S		move backward");
		dt->ca->cam_p[2] -= 2;
	}
	else if (keycode == 0)
	{
		ft_putendl("A		move left");
		dt->ca->cam_p[0] -= 2;
	}
	else if (keycode == 2)
	{
		ft_putendl("D		move right");
		dt->ca->cam_p[0] += 2;
	}
}

void	call_keys_camera_mov2(int keycode, t_data *dt)
{
	if (keycode == 12)
	{
		ft_putendl("Q		move down");
		dt->ca->cam_p[1] -= 2;
	}
	else if (keycode == 14)
	{
		ft_putendl("E		move up");
		dt->ca->cam_p[1] += 2;
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
