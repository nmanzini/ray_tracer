/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmanzini <nmanzini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:34:26 by nmanzini          #+#    #+#             */
/*   Updated: 2018/04/18 15:21:34 by nmanzini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float	float_abs(float f)
{
	if (f < 0)
		return (-f);
	else
		return (f);
}

void fill_pixel_res_sdl(t_data *dt,int x,int y)
{
	int *rgb;

	rgb = dt->px->rgb;
	SDL_SetRenderDrawColor(dt->sd.renderer,rgb[0], rgb[1], rgb[2], 255);
	// SDL_RenderDrawPoint(dt->sd.renderer, x, y);
// }

// {
	int	win[2];
	int	ratio[2];
	int ij[2];

	if (dt->ca->res[0] == 0 || dt->ca->res[0] == 0)
		return ;
	ratio[0] = WIDTH / dt->ca->res[0];
	ratio[1] = HEIGHT / dt->ca->res[1];
	win[0] = x * ratio[0];
	win[1] = y * ratio[1];
	ij[1] = 0;
	while (ij[1] != ratio[1])
	{
		ij[0] = 0;
		while (ij[0] != ratio[0])
		{
			// fill_pixel(dt->md, win[0] + ij[0], win[1] + ij[1], color);
			SDL_RenderDrawPoint(dt->sd.renderer, win[0] + ij[0], win[1] + ij[1]);
			ij[0]++;
		}
		ij[1]++;
	}
}

void	display(t_data *dt)
{
	SDL_RenderClear(dt->sd.renderer);
	ray_trace(dt);
	SDL_RenderPresent(dt->sd.renderer);
}

/*
** generate rays and call for a loop of all the objs to chekck if they hit
*/

void	ray_trace(t_data *dt)
{
	float	t;
	float	temp_t;

	cam_data_update(dt->ca);
	update_ray_p(dt->ca->cam_p, dt->px->ray);
	dt->px->pix_p[1] = -1;
	while (++dt->px->pix_p[1] < dt->ca->res[1])
	{
		dt->px->pix_p[0] = -1;
		while (++dt->px->pix_p[0] < dt->ca->res[0])
		{
			updt_ray_v(dt->ca->res, dt->px->pix_p, dt->ca->scr_s, dt->px->ray);
			rotate_v(dt->px->ray->v, dt->ca->cam_a);
			loop_trough_objs(dt);
		}
	}
}

int		main(int ac, char **av)
{
	static t_data	*dt;

	dt = init_data(dt);
	if (!get_input(dt, ac, av))
	{
		SDL_Event e;
		// SDL_Renderer *renderer;
		// SDL_Window *window;
		SDL_Surface *surface;
		SDL_Init(SDL_INIT_VIDEO);
		SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &(dt->sd.window), &(dt->sd.renderer));

		ft_putstr("rtv1 starting\n");
		display(dt);

		bool quit = false;


		//While application is running
		while( !quit )
		{
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit
				if( e.type == SDL_QUIT || e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					quit = true;
				}
				// mouse button print
				else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_C)
				{
					surface = SDL_GetWindowSurface(dt->sd.window);
					ft_putstr("C		pressed\n");
					SDL_SaveBMP(surface,"./screen.bmp");
				}
				else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_W)
				{
					ft_putendl("W		move forward");
					dt->ca->cam_p[2] += 2;
					display(dt);
				}
				else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_S)
				{
					ft_putendl("S		move backward");
					dt->ca->cam_p[2] -= 2;
					display(dt);
				}
				else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_A)
				{
					ft_putendl("A		move left");
					dt->ca->cam_p[0] -= 2;
					display(dt);
				}
				else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_D)
				{
					ft_putendl("D		move right");
					dt->ca->cam_p[0] += 2;
					display(dt);
				}
				else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_LEFTBRACKET)
				{
					ft_putendl("[		lower resolution");
					if (dt->ca->res_factor != 64)
						dt->ca->res_factor *= 2;
					else
						ft_putendl("[		minimum resolution reached");
					dt->ca->res[0] = WIDTH / dt->ca->res_factor;
					dt->ca->res[1] = HEIGHT / dt->ca->res_factor;
					display(dt);
				}
				else if (e.type == SDL_KEYDOWN && e.key.keysym.scancode == SDL_SCANCODE_RIGHTBRACKET)
				{
					ft_putendl("]		higher resolution");
					if (dt->ca->res_factor != 1)
						dt->ca->res_factor /= 2;
					else
						ft_putendl("]		maximum resolution reached");
					dt->ca->res[0] = WIDTH / dt->ca->res_factor;
					dt->ca->res[1] = HEIGHT / dt->ca->res_factor;
					display(dt);
				}
			}

			//Apply the image
			// SDL_BlitSurface( gXOut, NULL, gScreenSurface, NULL );
		
			//Update the surface
			// SDL_UpdateWindowSurface( gWindow );
		}

		// while (1) 
		// {

		// 	if (SDL_PollEvent(&(dt->sd.event)) && dt->sd.event.type == SDL_QUIT)
		// 		break;
		// }
		SDL_DestroyRenderer(dt->sd.renderer);
		SDL_DestroyWindow(dt->sd.window);
		SDL_Quit();
	}
	else
	{
		ft_putstr("Error reading the file.\nExiting.\n\n");
		exit(0);
	}
	return (0);
}
