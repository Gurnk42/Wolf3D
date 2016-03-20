/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 11:59:11 by ebouther          #+#    #+#             */
/*   Updated: 2016/03/20 20:28:23 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ft_draw(t_env *e)
{
	int			x;
	double		frame_time;

	x = 0;
	ft_draw_floor_sky(e);
	while (x < WIN_WIDTH)
	{
		ft_ray_cast_core(x, e);
		x++;
	}
	e->frame.previous = e->frame.current;
	e->frame.current = (double)clock();
	frame_time = (e->frame.current - e->frame.previous) / CLOCKS_PER_SEC;
	e->fps = ft_strjoin_free(ft_strdup("FPS: "), ft_itoa(1.0 / frame_time));
	e->p.speed.move = frame_time * MOVE_SPEED;
	e->p.speed.rot = frame_time * ROT_SPEED;
	ft_mini_map(e);
}

int				ft_draw_reload(t_env *e)
{
	e->image.img = mlx_new_image(e->mlx, WIN_WIDTH, WIN_HEIGHT);
	e->image.data_addr = mlx_get_data_addr(e->image.img, &(e->image.bpp),
			&(e->image.sizeline), &(e->image.endian));
	ft_draw(e);
	mlx_put_image_to_window(e->mlx, e->win, e->image.img, 0, 0);
	mlx_string_put(e->mlx, e->win, WIN_WIDTH - 100, 10, 0xffffff, e->fps);
	if (e->p.compass == 0 || e->p.compass == 1)
		mlx_string_put(e->mlx, e->win, WIN_WIDTH - 90, 30, 0xff0000,
				e->p.compass == 0 ? "NORTH" : "EAST");
	else if (e->p.compass == 2 || e->p.compass == 3)
		mlx_string_put(e->mlx, e->win, WIN_WIDTH - 90, 30, 0xff0000,
				e->p.compass == 2 ? "SOUTH" : "WEST");
	mlx_destroy_image(e->mlx, e->image.img);
	return (0);
}

void			ft_draw_point(t_point point, int color, t_env *e)
{
	int i;

	if (point.x >= WIN_WIDTH || point.x < 0 || point.y >= WIN_HEIGHT
			|| point.y < 0)
		return ;
	i = ((int)point.x * 4) + ((int)point.y * e->image.sizeline);
	e->image.data_addr[i] = color;
	e->image.data_addr[++i] = color >> 8;
	e->image.data_addr[++i] = color >> 16;
}
