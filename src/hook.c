/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 20:52:50 by ebouther          #+#    #+#             */
/*   Updated: 2016/03/20 21:10:46 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			ft_hook_key(int keycode, t_env *e)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == LEFT_KEY
			|| keycode == RIGHT_KEY
			|| keycode == DOWN_KEY
			|| keycode == UP_KEY)
		ft_move(keycode, e);
	return (0);
}

int			ft_mouse_hook(int button, int x, int y, t_env *e)
{
	t_point	offset;

	(void)x;
	(void)y;
	if (e->p.compass == NORTH)
		offset = (t_point){-2, 0};
	else if (e->p.compass == SOUTH)
		offset = (t_point){2, 0};
	else if (e->p.compass == WEST)
		offset = (t_point){0, -2};
	else if (e->p.compass == EAST)
		offset = (t_point){0, 2};
	if ((int)e->p.pos.x + (int)offset.x < 23
			&& (int)e->p.pos.x + (int)offset.x > 0
			&& (int)e->p.pos.y + (int)offset.y < 23
			&& (int)e->p.pos.y + (int)offset.y > 0)
		e->map[(int)e->p.pos.x + (int)offset.x]
			[(int)e->p.pos.y + (int)offset.y] = button == 1;
	return (0);
}
