/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 11:59:11 by ebouther          #+#    #+#             */
/*   Updated: 2016/03/19 18:53:16 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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

static void		ft_init_raycast(int x, t_ray_cast *r, t_env *e)
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

	if (e->map[(int)r->map.x][(int)r->map.y] == 1)
		color = 0xffff00;
	if (r->side == 1 && r->ray_dir.y < 0)
		color = 0x0000ff;
	else if (r->side == 0 && r->ray_dir.x > 0)
		color = 0x00ff00;
	else if (r->side == 0 && r->ray_dir.x < 0)
		color = 0xff0000;
	int red = ((color >> 16 ) & 0xFF) - (dist * 8);
	int g = ((color >> 8 ) & 0xFF) - (dist * 8);
	int b = (color & 0xFF) - (dist * 8);
	return ((((red > 0) ? red : 0) << 16) + (((g > 0) ? g : 0) << 8) + ((b > 0) ? b : 0));
}

static void		ft_get_wall_projection(int *start, int *end, t_ray_cast *r)
{
	int	height;

	if (r->side == 0)
		r->wall_dist = (r->map.x - r->ray_pos.x + (1 - r->step.x) / 2) / r->ray_dir.x;
	else
		r->wall_dist = (r->map.y - r->ray_pos.y + (1 - r->step.y) / 2) / r->ray_dir.y;
	height = (int)(WIN_HEIGHT / r->wall_dist);
	*start = -height / 2 + WIN_HEIGHT / 2;
	if (*start < 0)
		*start = 0;
	*end = height / 2 + WIN_HEIGHT / 2;
	if (*end >= WIN_HEIGHT)
		*end = WIN_HEIGHT - 1;
}

static void		ft_ray_cast_core(int x, t_env *e)
{
		t_ray_cast	r;
		int			dist;
		int			start;
		int			end;

		ft_init_raycast(x, &r, e);
		ft_get_step(&r);
		dist = ft_get_nearest_wall(&r, e);

		ft_get_wall_projection(&start, &end, &r);
		ft_draw_line((t_point){x, start}, (t_point){x, end}, ft_get_wall_color(dist, &r, e), e);
}

void			ft_draw(t_env *e)
{
	int			x;

	x = 0;
	ft_draw_floor_sky(e);
	while (x < WIN_WIDTH)
	{
		ft_ray_cast_core(x, e);
		x++;
	}
	e->frame.previous = e->frame.current;
	e->frame.current = (double)clock();
	double frameTime = (e->frame.current - e->frame.previous) / CLOCKS_PER_SEC; 
	e->fps = ft_strjoin_free(ft_strdup("FPS: "), ft_itoa(1.0 / frameTime));
	e->p.speed.move = frameTime * MOVE_SPEED;
	e->p.speed.rot = frameTime * ROT_SPEED;
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
