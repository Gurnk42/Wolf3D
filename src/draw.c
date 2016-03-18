/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 11:59:11 by ebouther          #+#    #+#             */
/*   Updated: 2016/03/18 16:45:18 by ebouther         ###   ########.fr       */
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

void			ft_draw(t_env *e)
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
				c = 0x0000ff;
				ft_draw_point((t_point){x, y}, c, e);
			}
			else
			{
				c = 0xffffff;
				int r = ((c >> 16 ) & 0xFF) - ((y - WIN_HEIGHT / 2));
				int g = ((c >> 8 ) & 0xFF) - ((y - WIN_HEIGHT / 2));
				int b = (c & 0xFF) - ((y - WIN_HEIGHT / 2));
				c = (((r > 0) ? 255 - r : 255) << 16)
					+ (((g > 0) ? 255 - g : 255) << 8) + ((b > 0) ? 255 - b : 255);
				ft_draw_point((t_point){x, y}, c, e);
			}
			y++;
		}
		x++;
	}
	x = 0;
	while (x < WIN_WIDTH)
	{
		double	cameraX = 2 * x / (double)WIN_WIDTH - 1;
		double	rayPosX = e->p.pos.x;
		double	rayPosY = e->p.pos.y;
		double	rayDirX = e->p.dir.x + e->p.cam.x * cameraX;
		double	rayDirY = e->p.dir.y + e->p.cam.y * cameraX;
		int		mapX = (int)(rayPosX);
		int		mapY = (int)(rayPosY);
		double	sideDistX;
		double	sideDistY;
		double	deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double	deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		double	perpWallDist;
		int		stepX;
		int		stepY;
		int		hit = 0;
		int		side;


		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (rayPosX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (rayPosY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
		}
		int		dist = 0;
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (e->map[mapX][mapY] > 0)
				hit = 1;
			dist++;
		}
		if (side == 0)
			perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(WIN_HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawEnd >= WIN_HEIGHT)
			drawEnd = WIN_HEIGHT - 1;

		int	color;
		if (e->map[mapX][mapY] == 1)
			color = 0xff0000;
		if (side == 1)
		{
			color = 0x00ff00;
			//color = (color & 0xfefefe) >> 1;
		}

		int r = ((color >> 16 ) & 0xFF) - (dist * 8);
		int g = ((color >> 8 ) & 0xFF) - (dist * 8);
		int b = (color & 0xFF) - (dist * 8);
		color = (((r > 0) ? r : 0) << 16) + (((g > 0) ? g : 0) << 8) + ((b > 0) ? b : 0);

		ft_draw_line((t_point){x, drawStart}, (t_point){x, drawEnd}, color, e);
		x++;
	}
	e->frame.previous = e->frame.current;
	e->frame.current = (double)clock();
	double frameTime = (e->frame.current - e->frame.previous) / CLOCKS_PER_SEC; 
	printf("FPS: '%f'\n", (1.0 / frameTime));
	e->p.speed.move = frameTime * MOVE_SPEED;
	e->p.speed.rot = frameTime * ROT_SPEED;
}

int				ft_draw_reload(t_env *e)
{
	e->image.img = mlx_new_image(e->mlx, WIN_WIDTH, WIN_HEIGHT);
	e->image.data_addr = mlx_get_data_addr(e->image.img, &(e->image.bpp),
			&(e->image.sizeline), &(e->image.endian));
	ft_draw(e);
	mlx_put_image_to_window(e->mlx, e->win, e->image.img, 0, 0);
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
