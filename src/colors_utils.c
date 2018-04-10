/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 14:16:18 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/10 21:46:27 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

unsigned int	rgb_to_ui(int red, int green, int blue)
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
