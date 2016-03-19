/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 16:06:46 by ebouther          #+#    #+#             */
/*   Updated: 2016/03/19 19:35:40 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		ft_draw_map(int x, int y, t_env *e)
{
	ft_draw_point((t_point){x * 4, y * 4}, 0xffffff, e);
	ft_draw_point((t_point){x * 4 + 1, y * 4}, 0xffffff, e);
	ft_draw_point((t_point){x * 4, y * 4 + 1}, 0xffffff, e);
	ft_draw_point((t_point){x * 4 + 1, y * 4 + 1}, 0xffffff, e);
	ft_draw_point((t_point){x * 4, y * 4 + 2}, 0xffffff, e);
	ft_draw_point((t_point){x * 4 + 2, y * 4}, 0xffffff, e);
	ft_draw_point((t_point){x * 4 + 2, y * 4 + 2}, 0xffffff, e);
	ft_draw_point((t_point){x * 4 + 1, y * 4 + 2}, 0xffffff, e);
	ft_draw_point((t_point){x * 4 + 2, y * 4 + 1}, 0xffffff, e);
}

static void		ft_draw_player(t_env *e)
{
	ft_draw_point((t_point){(int)e->p.pos.x * 4, (int)e->p.pos.y * 4},
			0xff0000, e);
	ft_draw_point((t_point){(int)e->p.pos.x * 4 + 1, (int)e->p.pos.y * 4},
			0xff0000, e);
	ft_draw_point((t_point){(int)e->p.pos.x * 4, (int)e->p.pos.y * 4 + 1},
			0xff0000, e);
	ft_draw_point((t_point){(int)e->p.pos.x * 4 + 1, (int)e->p.pos.y * 4 + 1},
			0xff0000, e);
	ft_draw_point((t_point){(int)e->p.pos.x * 4, (int)e->p.pos.y * 4 + 2},
			0xff0000, e);
	ft_draw_point((t_point){(int)e->p.pos.x * 4 + 2, (int)e->p.pos.y * 4},
			0xff0000, e);
	ft_draw_point((t_point){(int)e->p.pos.x * 4 + 2, (int)e->p.pos.y * 4 + 2},
			0xff0000, e);
	ft_draw_point((t_point){(int)e->p.pos.x * 4 + 1, (int)e->p.pos.y * 4 + 2},
			0xff0000, e);
	ft_draw_point((t_point){(int)e->p.pos.x * 4 + 2, (int)e->p.pos.y * 4 + 1},
			0xff0000, e);
}

void			ft_mini_map(t_env *e)
{
	int	x;
	int	y;

	x = 0;
	while (x < 24)
	{
		y = 0;
		while (y < 24)
		{
			if (e->map[x][y] != 0)
				ft_draw_map(x, y, e);
			y++;
		}
		x++;
	}
	ft_draw_player(e);
}
