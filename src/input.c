/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 19:40:05 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/10 21:46:36 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** frees a list of strings
*/

void	free_list_str(char **list)
{
	int i;

	i = 0;
	while (list[i] != 0)
	{
		free(list[i++]);
	}
	free(list[i]);
	free(list);
}

/*
** returns the len of a string
*/

int		list_len(char **list)
{
	int i;

	i = 0;
	while (list[i] != 0)
		i++;
	return (i);
}

/*
** prepare the obj list and call for the loop to read trough the file
*/

int		read_file(char *path, t_data *dt, int obj_num)
{
	dt->ob = (t_obj*)malloc(sizeof(t_obj) * (obj_num + 1));
	dt->obj_num = obj_num;
	dt->ob[obj_num].type = 'n';
	ft_putnbr(obj_num);
	ft_putstr(" Objects Found\n");
	if (loop_trough(path, dt))
		return (1);
	dt->ob[obj_num].type = 'n';
	return (0);
}

/*
** general input reading function
*/

int		get_input(t_data *dt, int ac, char **av)
{
	int obj_num;

	obj_num = 0;
	if (ac != 2)
	{
		ft_putstr("usage: ./RTv1 scene\n");
		return (1);
	}
	else if (!(obj_num = check_file(av[1])))
	{
		ft_putstr("Invalid File\n");
		ft_putstr("usage: ./RTv1 scene\n");
		return (2);
	}
	else
	{
		ft_putstr("Reading Objects\n");
		if (read_file(av[1], dt, obj_num))
		{
			return (1);
		}
		else
			ft_putstr("Objects loaded.\n");
	}
	return (0);
}
