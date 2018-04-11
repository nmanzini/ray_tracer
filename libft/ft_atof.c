/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 21:07:06 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/11 10:48:59 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\r')
		return (1);
	else if (c == '\f' || c == '\v' || c == ' ')
		return (1);
	else
		return (0);
}

float		ft_atof(char *str)
{
	float	res;
	float	fac;
	int		seen;

	fac = 1;
	res = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		fac = -1;
	if (*str == '+' || *str == '-')
		str++;
	while ((*str >= '0' && *str <= '9') || *str == '.')
	{
		if (*str == '.')
		{
			seen = 1;
			str++;
		}
		if (seen)
			fac /= 10;
		res = (res * 10) + (*str++ - '0');
	}
	return (fac * res);
}
