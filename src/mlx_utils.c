/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:21:46 by nmanzini          #+#    #+#             */
/*   Updated: 2018/02/20 16:45:18 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	fill_pixel(t_mlx *md, int x, int y, unsigned int color)
{
	if (x > 0 && x < md->width && y > 0 && y < md->height)
		md->ip->lst[y * md->width + x] = color;
}

void	img_square(t_mlx *md, unsigned int color)
{
	int i;
	int j;

	i = 0;
	while (i < md->width)
	{
		j = 0;
		while (j < md->height)
		{
			fill_pixel(md, i, j, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(md->mlx, md->win, md->ip->image, 0, 0);
}

void	img_square_dim(t_mlx *md, int *p1, int *p2, unsigned int color)
{
	int i;
	int j;

	i = p1[0];
	while (i < p2[0])
	{
		j = p1[1];
		while (j < p2[1])
		{
			fill_pixel(md, i, j, color);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(md->mlx, md->win, md->ip->image, p1[0], p1[1]);
}

void	make_image(t_mlx *md)
{
	int		bpp;
	int		s_l;
	int		endian;

	md->ip->image = mlx_new_image(md->mlx, md->width, md->height);
	md->ip->lst = (int *)mlx_get_data_addr(md->ip->image, &bpp, &s_l, &endian);
}

void	display(t_data	*dt)
{
	img_square(dt->md,BLACK);
	ray(dt);
	mlx_put_image_to_window(dt->md->mlx,dt-> md->win, dt->md->ip->image, 0, 0);
}
