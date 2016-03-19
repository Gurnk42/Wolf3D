/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 18:56:11 by ebouther          #+#    #+#             */
/*   Updated: 2016/03/19 19:03:58 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_init_raycast(int x, t_ray_cast *r, t_env *e)
{
	r->hit = 0;
	r->cam_x = 2 * x / (double)WIN_WIDTH - 1;
	r->ray_pos.x = e->p.pos.x;
	r->ray_pos.y = e->p.pos.y;
	r->ray_dir.x = e->p.dir.x + e->p.cam.x * r->cam_x;
	r->ray_dir.y = e->p.dir.y + e->p.cam.y * r->cam_x;
	r->map.x = (int)(r->ray_pos.x);
	r->map.y = (int)(r->ray_pos.y);
	r->delta_dist.x = sqrt(1 + (r->ray_dir.y * r->ray_dir.y) / (r->ray_dir.x * r->ray_dir.x));
	r->delta_dist.y = sqrt(1 + (r->ray_dir.x * r->ray_dir.x) / (r->ray_dir.y * r->ray_dir.y));
}

void	ft_draw_line(t_point v0, t_point v1, int color, t_env *env)
{
	t_point		s;
	t_point		d;
	int			err;
	int			e2;

	d = (t_point){fabs(v1.x - v0.x), fabs(v1.y - v0.y)};
	s = (t_point){(v0.x < v1.x ? 1 : -1), (v0.y < v1.y ? 1 : -1)};
	err = (d.x > d.y ? d.x : -d.y) / 2;
	while (!(v0.x == v1.x && v0.y == v1.y))
	{
		ft_draw_point(v0, color, env);
		e2 = err;
		if (e2 > -d.x)
		{
			err -= d.y;
			v0.x += s.x;
		}
		if (e2 < d.y)
		{
			err += d.x;
			v0.y += s.y;
		}
	}
}

void			ft_draw_floor_sky(t_env *e)
{
	int	x;
	int	y;
	int	c;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			if (y < WIN_HEIGHT / 2.0)
			{
				c = 0x301860;
				if (rand() % 20000 == 0)
				{
					ft_draw_point((t_point){x, y}, 0xffffe0, e);
					ft_draw_point((t_point){x - 1, y}, 0xffffe0, e);
					ft_draw_point((t_point){x, y - 1}, 0xffffe0, e);
					ft_draw_point((t_point){x - 1, y - 1}, 0xffffe0, e);
					ft_draw_point((t_point){x - 2, y}, 0xffffe0, e);
					ft_draw_point((t_point){x, y - 2}, 0xffffe0, e);
					ft_draw_point((t_point){x - 2, y - 2}, 0xffffe0, e);
					ft_draw_point((t_point){x - 2, y - 1}, 0xffffe0, e);
					ft_draw_point((t_point){x - 1, y - 2}, 0xffffe0, e);
				}
				else
					ft_draw_point((t_point){x, y}, c, e);
			}
			else
			{
				c = 0xb3b3b3;
				int r = ((c >> 16 ) & 0xFF) - ((y - WIN_HEIGHT / 2) * 0.5);
				int g = ((c >> 8 ) & 0xFF) - ((y - WIN_HEIGHT / 2) * 0.5);
				int b = (c & 0xFF) - ((y - WIN_HEIGHT / 2) * 0.5);
				c = (((r > 0) ? 255 - r : 255) << 16)
					+ (((g > 0) ? 255 - g : 255) << 8) + ((b > 0) ? 255 - b : 255);
				ft_draw_point((t_point){x, y}, c, e);
			}
			y++;
		}
		x++;
	}
}
