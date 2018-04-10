/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_read2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 21:35:41 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/10 21:46:58 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** check the number of objs in the file
*/

int		check_file(char *path)
{
	int		fd;
	char	*line;
	int		obj_n;

	obj_n = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	while (get_next_line(fd, &line) > 0)
	{
		if (*line == 's' || *line == 'o' || *line == 'y' || *line == 'p')
			obj_n += 1;
		free(line);
	}
	free(line);
	if (close(fd) == -1)
		return (0);
	return (obj_n);
}

/*
** reads and fills a camera obj
*/

int		read_c(t_data *dt, int fd, int *i_obj)
{
	int		i;
	char	*line2;
	char	**list;

	i = 0;
	get_next_line(fd, &line2);
	list = ft_strsplit(line2, ',');
	if (list_len(list) < 6)
		return (1);
	while (i < 3)
	{
		dt->ca->cam_p[i] = ft_atoi(list[i]);
		dt->ca->cam_a[i] = ft_atoi(list[i + 3]);
		i++;
	}
	free(line2);
	free_list_str(list);
	return (0);
}

/*
** reads and fills a light obj
*/

int		read_l(t_data *dt, int fd, int *i_obj)
{
	int		i;
	char	*line2;
	char	**list;

	i = 0;
	get_next_line(fd, &line2);
	list = ft_strsplit(line2, ',');
	if (list_len(list) < 3)
		return (1);
	while (i < 3)
	{
		dt->px->lig->p[i] = ft_atoi(list[i]);
		i++;
	}
	free(line2);
	free_list_str(list);
	return (0);
}

/*
** read what kind of onj and calls the reigh reading function
*/

int		write_obj(t_data *dt, int fd, char *line, int *i_obj)
{
	char	*line2;
	char	**list;
	int		error;

	error = 0;
	if (line[0] == 's')
		error = read_s(dt, fd, i_obj);
	else if (line[0] == 'o')
		error = read_o(dt, fd, i_obj);
	else if (line[0] == 'y')
		error = read_y(dt, fd, i_obj);
	else if (line[0] == 'p')
		error = read_p(dt, fd, i_obj);
	else if (line[0] == 'c' && line[2] == '1')
		error = read_c(dt, fd, i_obj);
	else if (line[0] == 'l' && line[2] == '1')
		error = read_l(dt, fd, i_obj);
	return (error);
}

/*
** loop trough every line, and if valid it write it into a obj
*/

int		loop_trough(char *file_path, t_data *dt)
{
	int		fd;
	char	*line;
	int		i_obj;
	int		error;

	i_obj = -1;
	error = 0;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] != '#' && line[0] != 0 && line[0] != 10)
			error = write_obj(dt, fd, line, &i_obj);
		if (error)
			return (1);
		free(line);
	}
	free(line);
	if (close(fd) == -1)
		return (-1);
	return (0);
}
