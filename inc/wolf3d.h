/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 11:54:42 by ebouther          #+#    #+#             */
/*   Updated: 2016/03/16 12:23:36 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include <mlx.h>
# include <fcntl.h>

# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000

typedef struct	s_point
{
	double		x;
	double		y;
}				t_point;

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

typedef struct s_env
{
	void		*mlx;
	void		*win;
	t_img		image;
}				t_env;

typedef struct	s_player
{
	t_point		pos;
	t_point		dir;
	t_point		cam;
}				t_player;

/*
** Draw.c:
*/
void			ft_draw_point(t_point point, int color, t_env *e);
void			ft_draw_reload(t_env *e);

#endif
