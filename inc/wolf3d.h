/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 11:54:42 by ebouther          #+#    #+#             */
/*   Updated: 2016/03/19 19:06:11 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include <time.h>
# include <math.h>
# include <mlx.h>

# define WIN_WIDTH 1024//2560
# define WIN_HEIGHT 720//1440

# define MOVE_SPEED 10
# define ROT_SPEED 5

# define POS_X 20
# define POS_Y 10
# define DIR_X -1
# define DIR_Y 0
# define CAM_X 0
# define CAM_Y 0.66

# define LEFT_KEY 123
# define RIGHT_KEY 124
# define DOWN_KEY 125
# define UP_KEY 126

typedef union	u_color
{
	int			color;
	char		r;
	char		g;
	char		b;
}				t_color;

typedef struct	s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct	s_speed
{
	double		move;
	double		rot;
}				t_speed;

typedef struct	s_player
{
	t_speed		speed;
	t_point		pos;
	t_point		dir;
	t_point		cam;
}				t_player;

typedef struct	s_img
{
	void		*img;
	int			width;
	int			height;
	char		*data_addr;
	int			bpp;
	int			sizeline;
	int			endian;
	int			color;
}				t_img;

typedef struct	s_frame
{
	double		current;
	double		previous;
}				t_frame;

typedef struct	s_ray_cast
{
	double		cam_x;
	t_point		ray_pos;
	t_point		ray_dir;
	t_point		map;
	t_point		side_dist;
	t_point		delta_dist;
	t_point		step;
	double		wall_dist;
	int			hit;
	int			side;
}				t_ray_cast;

typedef struct s_env
{
	char		*fps;
	char		*background;
	void		*mlx;
	void		*win;
	t_img		image;
	uint8_t		map[24][24];
	t_player	p;
	t_frame		frame;
}				t_env;

/*
** Draw.c:
*/
void			ft_draw_point(t_point point, int color, t_env *e);
int				ft_draw_reload(t_env *e);
void			ft_draw_floor_sky(t_env *e);

/*
** Minimap.c
*/
void			ft_mini_map(t_env *e);

/*
** utils.c
*/
void			ft_draw_line(t_point v0, t_point v1, int color, t_env *env);
void			ft_draw_floor_sky(t_env *e);
void			ft_init_raycast(int x, t_ray_cast *r, t_env *e);

/*
** ray_cast.c
*/
void			ft_ray_cast_core(int x, t_env *e);

#endif
