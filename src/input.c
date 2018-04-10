/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 19:40:05 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/10 14:42:07 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

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

int		check_file(char *path)
{
	int		fd;
	char	*line;
	int		obj_n;

	obj_n = 0;
	fd = open(path, O_RDONLY);
	ft_putendl("OPENED");
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
	ft_putendl("CLOSED");
	return (obj_n);
}

void	read_color(t_data *dt, int fd, int *i_obj)
{
	int		i;
	char	*line2;
	char	**list;

	get_next_line(fd, &line2);
	list = ft_strsplit(line2, ',');
	i = 0;
	while (i < 3)
	{
		dt->ob[*i_obj].rgb[i] = ft_atoi(list[i]);
		i++;
	}
	free(line2);
	free_list_str(list);
}

void	read_s(t_data *dt, int fd, int *i_obj)
{
	int		i;
	char	*line2;
	char	**list;

	i = 0;
	*i_obj = *i_obj + 1;
	dt->ob[*i_obj].type = 's';
	get_next_line(fd, &line2);
	list = ft_strsplit(line2, ',');
	while (i < 4)
	{
		dt->ob[*i_obj].p[i] = ft_atoi(list[i]);
		i++;
	}
	free(line2);
	free_list_str(list);
	read_color(dt, fd, i_obj);
}

void	read_o(t_data *dt, int fd, int *i_obj)
{
	int		i;
	char	*line2;
	char	**list;

	i = 0;
	*i_obj = *i_obj + 1;
	dt->ob[*i_obj].type = 'o';
	get_next_line(fd, &line2);
	list = ft_strsplit(line2, ',');
	while (i < 3)
	{
		dt->ob[*i_obj].vp.p[i] = ft_atoi(list[i]);
		dt->ob[*i_obj].vp.v[i] = ft_atoi(list[i + 3]);
		i++;
	}
	dt->ob[*i_obj].p[0] = ft_atoi(list[6]);
	normalize(dt->ob[*i_obj].vp.v);
	free(line2);
	free_list_str(list);
	read_color(dt, fd, i_obj);
}

void	read_y(t_data *dt, int fd, int *i_obj)
{
	int		i;
	char	*line2;
	char	**list;

	i = 0;
	*i_obj = *i_obj + 1;
	dt->ob[*i_obj].type = 'y';
	get_next_line(fd, &line2);
	list = ft_strsplit(line2, ',');
	while (i < 3)
	{
		dt->ob[*i_obj].vp.p[i] = ft_atoi(list[i]);
		dt->ob[*i_obj].vp.v[i] = ft_atoi(list[i + 3]);
		i++;
	}
	dt->ob[*i_obj].p[0] = ft_atoi(list[6]);
	normalize(dt->ob[*i_obj].vp.v);
	free(line2);
	free_list_str(list);
	read_color(dt, fd, i_obj);
}

void	read_p(t_data *dt, int fd, int *i_obj)
{
	int		i;
	char	*line2;
	char	**list;

	i = 0;
	*i_obj = *i_obj + 1;
	dt->ob[*i_obj].type = 'p';
	get_next_line(fd, &line2);
	list = ft_strsplit(line2, ',');
	while (i < 4)
	{
		dt->ob[*i_obj].p[i] = ft_atoi(list[i]);
		i++;
	}
	normalize(dt->ob[*i_obj].p);
	free(line2);
	free_list_str(list);
	read_color(dt, fd, i_obj);
}

void	read_c(t_data *dt, int fd, int *i_obj)
{
	int		i;
	char	*line2;
	char	**list;

	i = 0;
	get_next_line(fd, &line2);
	list = ft_strsplit(line2, ',');
	while (i < 3)
	{
		dt->ca->cam_p[i] = ft_atoi(list[i]);
		dt->ca->cam_a[i] = ft_atoi(list[i + 3]);
		i++;
	}
	free(line2);
	free_list_str(list);
}

void	read_l(t_data *dt, int fd, int *i_obj)
{
	int		i;
	char	*line2;
	char	**list;

	i = 0;
	get_next_line(fd, &line2);
	list = ft_strsplit(line2, ',');
	while (i < 3)
	{
		dt->px->lig->p[i] = ft_atoi(list[i]);
		i++;
	}
	free(line2);
	free_list_str(list);
}

int		write_obj(t_data *dt, int fd, char *line, int *i_obj)
{
	int		i;
	char	*line2;
	char	**list;

	i = 0;
	if (line[0] == 's' && line[2] == '1')
		read_s(dt, fd, i_obj);
	else if (line[0] == 'o' && line[2] == '1')
		read_o(dt, fd, i_obj);
	else if (line[0] == 'y' && line[2] == '1')
		read_y(dt, fd, i_obj);
	else if (line[0] == 'p' && line[2] == '1')
		read_p(dt, fd, i_obj);
	else if (line[0] == 'c' && line[2] == '1')
		read_c(dt, fd, i_obj);
	else if (line[0] == 'l' && line[2] == '1')
		read_l(dt, fd, i_obj);
	return (0);
}

int		loop_trough(char *file_path, t_data *dt)
{
	int		fd;
	char	*line;
	int		i_obj;

	i_obj = -1;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] != '#' && line[0] != 0 && line[0] != 10)
		{
			write_obj(dt, fd, line, &i_obj);
		}
		free(line);
	}
	free(line);
	if (close(fd) == -1)
		return (-1);
	return (0);
}

int		read_file(char *path, t_data *dt, int obj_num)
{
	dt->ob = (t_obj*)malloc(sizeof(t_obj) * (obj_num + 1));
	dt->obj_num = obj_num;
	dt->ob[obj_num].type = 'n';
	ft_putnbr(obj_num);
	ft_putstr(" objs allocated\n");
	loop_trough(path, dt);
	return (0);
}

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
		ft_putstr("Reading\n");
		read_file(av[1], dt, obj_num);
	}
	ft_putstr(" loaded.\n");
	return (0);
}
