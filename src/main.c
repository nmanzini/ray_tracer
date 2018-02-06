/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:34:26 by nmanzini          #+#    #+#             */
/*   Updated: 2018/02/06 16:39:33 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

float	float_abs(float f)
{
	if (f < 0)
		return (-f);
	else
		return (f);
}

int		main(int ac, char **av)
{
	static t_data	*dt;

	dt = init_data(dt);

	img_square(dt->md, BLUE);

	mlx_key_hook(dt->md->win, call_keys, dt);
	mlx_loop(dt->md->mlx);
	return (0);
}
