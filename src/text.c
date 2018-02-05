/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicola <nicola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 18:49:53 by nmanzini          #+#    #+#             */
/*   Updated: 2018/02/05 01:08:31 by nicola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	put_next_str(t_data *dt, char *str)
{
	mlx_string_put(dt->md->mlx, dt->md->win, dt->st->x, dt->st->y, WHITE, str);
	dt->st->y += 18;
}

void	put_str_and_int(t_data *dt, char *str, int n)
{
	char *number;
	char *str_number;

	number = ft_itoa(n);
	str_number = ft_strjoin(str, number);
	put_next_str(dt, str_number);
	free(number);
	free(str_number);
}

void	put_str_and_str(t_data *dt, char *str, char *c)
{
	char *str_number;

	str_number = ft_strjoin(str, c);
	put_next_str(dt, str_number);
	free(str_number);
}

void	put_strings(t_data *dt)
{
	dt->st->y = 18;
	dt->st->x = 18;
	if (dt->cf->f_flag == 0)
		put_str_and_str(dt, "Fractal       = ", "Mandelbrot");
	else if (dt->cf->f_flag == 1)
		put_str_and_str(dt, "Fractal       = ", "Julia");
	else if (dt->cf->f_flag == 2)
		put_str_and_str(dt, "Fractal       = ", "Burning_ship");
	else if (dt->cf->f_flag == 3)
		put_str_and_str(dt, "Fractal       = ", "Tricorn");
	put_str_and_int(dt, "Color Palette = ", dt->cf->c_flag);
	put_str_and_str(dt, "Progressive   = ", &(dt->cf->progressive));
	if (dt->cf->progressive == 'y')
		put_str_and_int(dt, "iters         = ", dt->cf->max_iter);
	if (dt->cf->mode == 'z')
		put_str_and_str(dt, "Mode          = ", "zooming");
	else
		put_str_and_str(dt, "Mode          = ", "parameters");
}
