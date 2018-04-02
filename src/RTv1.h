/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:34:10 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/02 16:10:35 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include <math.h>

// remove!!!
# include <stdio.h>

# define PI_R		3.14142/180

# define MAX(x, y) (((x) > (y)) ? (x) : (y))
# define MIN(x, y) (((x) < (y)) ? (x) : (y))

# define WIDTH		1024
# define HEIGHT		1024

typedef struct		s_point_vector
{
	float			p[3];
	float			v[3];
}					t_pv;

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
	int				cfgs;
}					t_cfg;

typedef struct		s_cam_struct
{
	int				res[2];
	int				max_depth;
	float			fov;
	float			cam_p[3];
	float			cam_v[3];
	float			cam_a[3];
	float			scr_s[3];
}					t_cam;

typedef struct		s_pix_struct
{
	t_pv			*ray;
	t_pv			*enc;
	t_pv			*lig;
	int				pix_p[2];

	float			ray_p[3];
	float			ray_v[3];

	float			int_p[3];
	float			int_n[3];

	float			lig_v[3];
	unsigned int	color;
}					t_pix;

typedef struct		s_scn_struct
{
	float			sphere[4];
	float			x_sphere[4];
	float			y_sphere[4];
	float			z_sphere[4];
	float			a_sphere[4];
	float			*spheres[4];
	float			light[4];
	float			plane[2];
	float			plane2[2];
	float			box[6];
	float			surface[6];
	t_pv			cone;
}					t_scn;

typedef struct		s_data_struct
{
	t_cfg			*cf;
	t_str			*st;
	t_mlx			*md;
	t_scn			*sc;
	t_cam			*ca;
	t_pix			*px;
}					t_data;

# define BLACK		0x00000000
# define WHITE		0x00FFFFFF

# define RED		0x00FF0000
# define GREEN		0x0000FF00
# define BLUE		0x000000FF

/*
** main.c
*/
void	ray_trace(t_data	*dt);
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
void	cam_data_update(t_cam *ca);
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
void	display(t_data	*dt);
void	fill_pixel_res(t_data *dt,int r_x, int r_y, unsigned int color);
void				img_square_dim(t_mlx *md, int *p1, int *p2,
								unsigned int color);
/*
** colors_utlis.c
*/
unsigned int		rgb(int red, int green, int blue);
void				fractal_color(t_data *dt, int x, int y, int iter);

float	solve_quadratic(float A, float B, float C);
void	rotate_v(float *vec,float *angles);
float 	ray_plane_encounter(float *plane, t_pv *ray, t_pv *enc);
float 	ray_surface_encounter(float *surface, t_pv *ray, t_pv *enc);
float	ray_sphere_encounter(float *surface, t_pv *ray, t_pv *enc);
float	ray_box_encounter(float *box, t_pv *ray, t_pv *enc);
float	ray_cone_encounter(t_pv cone, int angle, t_pv *ray, t_pv *enc);


#endif
