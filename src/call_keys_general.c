/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_keys_general.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicola <nicola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 17:02:37 by nmanzini          #+#    #+#             */
/*   Updated: 2018/02/05 01:12:57 by nicola           ###   ########.fr       */
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

int		call_keys(int keycode, t_data *dt)
{
	call_keys_general(keycode, dt);
	display(dt, dt->cf->fractal);
	return (0);
}
