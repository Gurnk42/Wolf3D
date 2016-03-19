/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 19:02:26 by ebouther          #+#    #+#             */
/*   Updated: 2016/03/19 19:37:24 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		ft_get_step(t_ray_cast *r)
{
	if (r->ray_dir.x < 0)
	{
		r->step.x = -1;
		r->side_dist.x = (r->ray_pos.x - r->map.x) * r->delta_dist.x;
	}
	else
	{
		r->step.x = 1;
		r->side_dist.x = (r->map.x + 1.0 - r->ray_pos.x) * r->delta_dist.x;
	}
	if (r->ray_dir.y < 0)
	{
		r->step.y = -1;
		r->side_dist.y = (r->ray_pos.y - r->map.y) * r->delta_dist.y;
	}
	else
	{
		r->step.y = 1;
		r->side_dist.y = (r->map.y + 1.0 - r->ray_pos.y) * r->delta_dist.y;
	}
}

static int		ft_get_nearest_wall(t_ray_cast *r, t_env *e)
{
	int	dist;

	dist = 0;
	while (r->hit == 0)
	{
		if (r->side_dist.x < r->side_dist.y)
		{
			r->side_dist.x += r->delta_dist.x;
			r->map.x += r->step.x;
			r->side = 0;
		}
		else
		{
			r->side_dist.y += r->delta_dist.y;
			r->map.y += r->step.y;
			r->side = 1;
		}
		if (e->map[(int)r->map.x][(int)r->map.y] > 0)
			r->hit = 1;
		dist++;
	}
	return (dist);
}

static int		ft_get_wall_color(int dist, t_ray_cast *r, t_env *e)
{
	int	color;
	int	red;
	int	g;
	int	b;

	if (e->map[(int)r->map.x][(int)r->map.y] == 1)
		color = 0xffff00;
	if (r->side == 1 && r->ray_dir.y < 0)
		color = 0x0000ff;
	else if (r->side == 0 && r->ray_dir.x > 0)
		color = 0x00ff00;
	else if (r->side == 0 && r->ray_dir.x < 0)
		color = 0xff0000;
	red = ((color >> 16) & 0xFF) - (dist * 8);
	g = ((color >> 8) & 0xFF) - (dist * 8);
	b = (color & 0xFF) - (dist * 8);
	return ((((red > 0) ? red : 0) << 16)
		+ (((g > 0) ? g : 0) << 8) + ((b > 0) ? b : 0));
}

static void		ft_get_wall_projection(int *start,
		int *end, t_ray_cast *r)
{
	int	height;

	if (r->side == 0)
		r->wall_dist = (r->map.x - r->ray_pos.x
			+ (1 - r->step.x) / 2) / r->ray_dir.x;
	else
		r->wall_dist = (r->map.y - r->ray_pos.y
				+ (1 - r->step.y) / 2) / r->ray_dir.y;
	height = (int)(WIN_HEIGHT / r->wall_dist);
	*start = -height / 2 + WIN_HEIGHT / 2;
	if (*start < 0)
		*start = 0;
	*end = height / 2 + WIN_HEIGHT / 2;
	if (*end >= WIN_HEIGHT)
		*end = WIN_HEIGHT - 1;
}

void			ft_ray_cast_core(int x, t_env *e)
{
	t_ray_cast	r;
	int			dist;
	int			start;
	int			end;

	ft_init_raycast(x, &r, e);
	ft_get_step(&r);
	dist = ft_get_nearest_wall(&r, e);
	ft_get_wall_projection(&start, &end, &r);
	ft_draw_line((t_point){x, start}, (t_point){x, end},
			ft_get_wall_color(dist, &r, e), e);
}
