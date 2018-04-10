/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 21:32:12 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/10 21:46:10 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** reads the third line of the obj and fills the rgb values with it
*/

int		read_color(t_data *dt, int fd, int *i_obj)
{
	int		i;
	char	*line2;
	char	**list;

	get_next_line(fd, &line2);
	list = ft_strsplit(line2, ',');
	if (list_len(list) < 3)
	{
		dt->ob[*i_obj].rgb[0] = 255;
		dt->ob[*i_obj].rgb[1] = 255;
		dt->ob[*i_obj].rgb[2] = 255;
		return (0);
	}
	i = 0;
	while (i < 3)
	{
		dt->ob[*i_obj].rgb[i] = ft_atoi(list[i]);
		i++;
	}
	free(line2);
	free_list_str(list);
	return (0);
}

/*
** reads and fills a a sphere obj
*/

int		read_s(t_data *dt, int fd, int *i_obj)
{
	int		i;
	char	*line2;
	char	**list;

	i = 0;
	*i_obj = *i_obj + 1;
	dt->ob[*i_obj].type = 's';
	dt->ob[*i_obj].active = 0;
	get_next_line(fd, &line2);
	list = ft_strsplit(line2, ',');
	if (list_len(list) < 4)
		return (1);
	while (i < 4)
	{
		dt->ob[*i_obj].p[i] = ft_atoi(list[i]);
		i++;
	}
	free(line2);
	free_list_str(list);
	read_color(dt, fd, i_obj);
	dt->ob[*i_obj].active = 1;
	return (0);
}

/*
** reads and fills a cone obj
*/

int		read_o(t_data *dt, int fd, int *i_obj)
{
	int		i;
	char	*line2;
	char	**list;

	i = -1;
	*i_obj = *i_obj + 1;
	dt->ob[*i_obj].type = 'o';
	dt->ob[*i_obj].active = 0;
	get_next_line(fd, &line2);
	list = ft_strsplit(line2, ',');
	if (list_len(list) < 7)
		return (1);
	while (++i < 3)
	{
		dt->ob[*i_obj].vp.p[i] = ft_atoi(list[i]);
		dt->ob[*i_obj].vp.v[i] = ft_atoi(list[i + 3]);
	}
	dt->ob[*i_obj].p[0] = ft_atoi(list[6]);
	normalize(dt->ob[*i_obj].vp.v);
	free(line2);
	free_list_str(list);
	read_color(dt, fd, i_obj);
	dt->ob[*i_obj].active = 1;
	return (0);
}

/*
** reads and fills a cylinder obj
*/

int		read_y(t_data *dt, int fd, int *i_obj)
{
	int		i;
	char	*line2;
	char	**list;

	i = -1;
	*i_obj = *i_obj + 1;
	dt->ob[*i_obj].type = 'y';
	dt->ob[*i_obj].active = 0;
	get_next_line(fd, &line2);
	list = ft_strsplit(line2, ',');
	if (list_len(list) < 7)
		return (1);
	while (++i < 3)
	{
		dt->ob[*i_obj].vp.p[i] = ft_atoi(list[i]);
		dt->ob[*i_obj].vp.v[i] = ft_atoi(list[i + 3]);
	}
	dt->ob[*i_obj].p[0] = ft_atoi(list[6]);
	normalize(dt->ob[*i_obj].vp.v);
	free(line2);
	free_list_str(list);
	read_color(dt, fd, i_obj);
	dt->ob[*i_obj].active = 1;
	return (0);
}

/*
** reads and fills a plane obj
*/

int		read_p(t_data *dt, int fd, int *i_obj)
{
	int		i;
	char	*line2;
	char	**list;

	i = 0;
	*i_obj = *i_obj + 1;
	dt->ob[*i_obj].type = 'p';
	dt->ob[*i_obj].active = 0;
	get_next_line(fd, &line2);
	list = ft_strsplit(line2, ',');
	if (list_len(list) < 4)
		return (1);
	while (i < 4)
	{
		dt->ob[*i_obj].p[i] = ft_atoi(list[i]);
		i++;
	}
	normalize(dt->ob[*i_obj].p);
	free(line2);
	free_list_str(list);
	read_color(dt, fd, i_obj);
	dt->ob[*i_obj].active = 1;
	return (0);
}
