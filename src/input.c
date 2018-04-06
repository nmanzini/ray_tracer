/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 19:40:05 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/05 20:04:39 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_file(av[1])
{
	// check if teh file is fine and returns the number of objects

	// check if the number of lines is fine
}

int	get_input(t_obj *ob, int ac, char **av)
{

	if (ac != 2)
	{
		ft_putstr("usage: ./RTv1 file.rt\n");
		return (1);
	}
	if (get_matrix(av[1], md))
	{
		ft_putstr("Invalid File\n");
		ft_putstr("usage: ./RTv1 file.rt\n");
		return (2);
	}
	md->in->name = av[1];
	get_max_size(md);
	md->in->matrix_p = get_matrix_p(md->in->m, md->in->n, 3);
	ft_putstr(av[1]);
	ft_putstr(" loaded.\n");
	return (0);
}