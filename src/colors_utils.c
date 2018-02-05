/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicola <nicola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 14:16:18 by nmanzini          #+#    #+#             */
/*   Updated: 2018/02/05 22:25:51 by nicola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void			fractal_color(t_data *dt, int x, int y, int iter)
{
	int				slices;
	int				max_local;
	unsigned int	color;

	// fill_pixel(dt->md, x, y, dt->cf->i_to_c[dt->cf->c_flag](dt, iter));
}

unsigned int	rgb(int red, int green, int blue)
{
	unsigned int color;

	color = BLACK;
	if (blue < 256 && green < 256 && red < 255)
	{
		color += blue;
		color += 256 * green;
		color += 256 * 256 * red;
	}
	return (color);
}
