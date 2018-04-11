/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:34:10 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/11 10:52:36 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include <math.h>

# define PI_R		3.14159265/180

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

typedef struct		s_mlx_struct
{
	void			*mlx;
	void			*win;
	int				height;
	int				width;
	char			type;
	t_img_prm		*ip;
}					t_mlx;

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
	int				shadow;
	unsigned int	color;
}					t_pix;

typedef struct		s_obj_struct
{
	char			type;
	int				active;
	t_pv			vp;
	float			p[6];
	unsigned int	color;
	int				rgb[3];
}					t_obj;

typedef struct		s_data_struct
{
	t_mlx			*md;
	t_cam			*ca;
	t_pix			*px;
	t_obj			*ob;
	int				obj_num;
}					t_data;

# define BLACK		0x00000000
# define WHITE		0x00FFFFFF

# define RED		0x00FF0000
# define GREEN		0x0000FF00
# define BLUE		0x000000FF

/*
** rotate.c
*/
void				rotate_z(float degree, float *xp, float *yp, float *zp);
void				rotate_x(float degree, float *xp, float *yp, float *zp);
void				rotate_y(float degree, float *xp, float *yp, float *zp);
void				rotate_v(float *vec, float *angles);
/*
** vect_operations.c
*/
void				vec_mult(float *vect, float scalar, float *result);
void				vec_sub(float *vect1, float *vect2, float *result);
void				vec_add(float *vect1, float *vect2, float *result);
void				vec_neg(float *vect, float *result);
/*
** vect_update.c
*/
void				update_encounter_p(float t, t_pv *ray, t_pv *enc);
void				update_light_v(t_pv *enc, t_pv *lig);
void				update_ray_p(float *cam_p, t_pv *ray);
void				updt_ray_v(int *res, int *pixel, float *scr_s, t_pv *ray);
/*
** vect_algebra.c
*/
void				normalize(float *vec);
float				dot_prod(float *vec1, float *vec2);
float				vec_len(float *vect);
void				min_perp_vec(float *point, float *vector,
						float *origin, float *normal);
float				light_enc_dist(t_pv *enc, t_pv *lig);
/*
** obj_loops.c
*/
void				update_color(t_pix *px, t_obj *ob);
float				check_obj_temp_t(t_pv *ray, t_pv *enc, t_obj ob);
int					loop_obj_shadow(t_pv *enc, t_pv *lig, t_obj *ob, int exc);
void				color_point(t_data *dt, int i);
void				loop_trough_objs(t_data *dt);
/*
** obj_utilities.c
*/
float				solve_quadratic(float a, float b, float c);
void				get_dpdp_vava(t_pv cyl, t_pv *ray, float *dd_vava);
void				get_vv_vava(t_pv cyl, t_pv *ray, float *vv_vava);
float				dot_mult_sub(float *vec, t_pv shape, float *xx_vava);
float				get_t_cone(t_pv cone, float *cs_sr, t_pv *ray, float *q);
/*
** obj_ray_encounter.c
*/
float				ray_cylinder_encounter(t_pv cyl, float r, t_pv *ray,
											t_pv *enc);
float				ray_cone_encounter(t_pv cone, int angle, t_pv *ray,
											t_pv *enc);
float				ray_sphere_encounter(float *sphere, t_pv *ray, t_pv *enc);
float				ray_plane_encounter(float *plane, t_pv *ray, t_pv *enc);
/*
** obj_ray_encounter.c
*/
int					read_color(t_data *dt, int fd, int *i_obj);
int					read_s(t_data *dt, int fd, int *i_obj);
int					read_o(t_data *dt, int fd, int *i_obj);
int					read_y(t_data *dt, int fd, int *i_obj);
int					read_p(t_data *dt, int fd, int *i_obj);
/*
** obj_read2.c
*/
int					check_file(char *path);
int					read_c(t_data *dt, int fd, int *i_obj);
int					read_l(t_data *dt, int fd, int *i_obj);
int					write_obj(t_data *dt, int fd, char *line, int *i_obj);
int					loop_trough(char *file_path, t_data *dt);
/*
** inout.c
*/
void				free_list_str(char **list);
int					list_len(char **list);
int					read_file(char *path, t_data *dt, int obj_num);
int					get_input(t_data *dt, int ac, char **av);
/*
** main.c
*/
void				ray_trace(t_data	*dt);
float				float_abs(float f);
/*
** data_init.c
*/
t_mlx				*mlx_data_init_return(t_mlx *md);
t_data				*init_data(t_data *dt);
void				cam_data_update(t_cam *ca);
t_cam				*cam_data_init(t_cam *ca);
t_pix				*pix_data_init(t_pix *px);
/*
** call_keys_general.c
*/
int					call_keys(int keycode, t_data *dt);
void				call_keys_general(int keycode, t_data *dt);
void				call_keys_camera_lens(int keycode, t_data *dt);
void				call_keys_resolution(int keycode, t_data *dt);
/*
** call_keys_camera.c
*/
void				call_keys_camera_mov(int keycode, t_data *dt);
void				call_keys_camera_mov2(int keycode, t_data *dt);
void				call_keys_camera_rot(int keycode, t_data *dt);
/*
** mlx_utils.c
*/
void				make_image(t_mlx *md);
void				img_square(t_mlx *md, unsigned int color);
void				fill_pixel(t_mlx *md, int x, int y, unsigned int color);
void				display(t_data	*dt);
void				fill_pixel_res(t_data *dt, int r_x, int r_y,
								unsigned int color);
/*
** colors_utlis.c
*/
unsigned int		rgb_to_ui(int red, int green, int blue);
#endif
