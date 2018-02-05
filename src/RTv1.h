/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicola <nicola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:34:10 by nmanzini          #+#    #+#             */
/*   Updated: 2018/02/05 22:02:55 by nicola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include <math.h>

typedef struct		s_image_struct
{
	int				*lst;
	void			*image;
}					t_img_prm;

typedef struct		s_str_struct
{
	int				x;
	int				y;
	char			*av1;
}					t_str;

typedef struct		s_mlx_struct
{
	void			*mlx;
	void			*win;
	int				height;
	int				width;
	char			type;
	t_img_prm		*ip;
}					t_mlx;

typedef struct		s_cfg_struct
{
	float			x_zoom;
	float			y_zoom;
	float			x_move;
	float			y_move;
	float			x_center;
	float			y_center;
	float			x_julia;
	float			y_julia;
	char			mode;
	char			progressive;

	int				f_flag;
	int				max_iter;
	int				max_iter_original;

	int				c_flag;
	int				c_slices;
	int				c_s_size;
	unsigned int	c_inside;
	unsigned int	(*i_to_c[10])();
	void			(*fractal)();
}					t_cfg;

typedef struct		s_scn_struct
{
	int				n_obj;
}					t_scn;

typedef struct		s_data_struct
{
	t_cfg			*cf;
	t_str			*st;
	t_mlx			*md;
	t_scn			*sc;
	char			*name;
}					t_data;

# define WIDTH		1024
# define HEIGHT		512

# define BLACK		0x00000000
# define WHITE		0x00FFFFFF

# define RED		0x00FF0000
# define GREEN		0x0000FF00
# define BLUE		0x000000FF

/*
** main.c
*/
float				float_abs(float f);
int					read_input(t_data *dt, int ac, char **av);
int					motion_function(int x, int y, t_data *dt);
/*
** data_init.c
*/
t_mlx				*mlx_data_init_return(t_mlx *md);
void				cfg_setup(t_cfg *cf);
t_cfg				*cfg_data_init(t_cfg *cf);
t_data				*init_data(t_data *dt);
/*
** call_keys_general.c
*/
int					call_keys(int keycode, t_data *dt);
void				call_keys_general(int keycode, t_data *dt);
/*
** mlx_utils.c
*/
void				fill_dot(t_mlx *md, int x, int y, int radius);
void				make_image(t_mlx *md);
void				img_square(t_mlx *md, unsigned int color);
void				fill_pixel(t_mlx *md, int x, int y,
								unsigned int color);
void				display(t_data *dt, void (*f)(t_data*));
void				img_square_dim(t_mlx *md, int *p1, int *p2,
								unsigned int color);
/*
** colors_utlis.c
*/
unsigned int		rgb(int red, int green, int blue);
void				fractal_color(t_data *dt, int x, int y, int iter);

#endif
