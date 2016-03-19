/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/19 19:44:45 by ebouther          #+#    #+#             */
/*   Updated: 2016/03/19 20:15:37 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ft_move_left(t_env *e)
{
	double last_dir_x;
	double last_cam_x;

	last_dir_x = e->p.dir.x;
	e->p.dir.x = e->p.dir.x * cos(e->p.speed.rot) - e->p.dir.y
		* sin(e->p.speed.rot);
	e->p.dir.y = last_dir_x * sin(e->p.speed.rot) + e->p.dir.y
		* cos(e->p.speed.rot);
	last_cam_x = e->p.cam.x;
	e->p.cam.x = e->p.cam.x * cos(e->p.speed.rot) - e->p.cam.y
		* sin(e->p.speed.rot);
	e->p.cam.y = last_cam_x * sin(e->p.speed.rot) + e->p.cam.y
		* cos(e->p.speed.rot);
}

static void	ft_move_right(t_env *e)
{
	double last_dir_x;
	double last_cam_x;

	last_dir_x = e->p.dir.x;
	e->p.dir.x = e->p.dir.x * cos(-(e->p.speed.rot)) - e->p.dir.y
		* sin(-(e->p.speed.rot));
	e->p.dir.y = last_dir_x * sin(-(e->p.speed.rot)) + e->p.dir.y
		* cos(-(e->p.speed.rot));
	last_cam_x = e->p.cam.x;
	e->p.cam.x = e->p.cam.x * cos(-(e->p.speed.rot)) - e->p.cam.y
		* sin(-(e->p.speed.rot));
	e->p.cam.y = last_cam_x * sin(-(e->p.speed.rot)) + e->p.cam.y
		* cos(-(e->p.speed.rot));
}

void		ft_move(int keycode, t_env *e)
{
	if (keycode == LEFT_KEY)
		ft_move_left(e);
	else if (keycode == RIGHT_KEY)
		ft_move_right(e);
	else if (keycode == DOWN_KEY)
	{
		if (e->map[(int)(e->p.pos.x - e->p.dir.x
					* e->p.speed.move)][(int)(e->p.pos.y)] == 0)
			e->p.pos.x -= e->p.dir.x * e->p.speed.move;
		if (e->map[(int)(e->p.pos.x)][(int)(e->p.pos.y - e->p.dir.y
					* e->p.speed.move)] == 0)
			e->p.pos.y -= e->p.dir.y * e->p.speed.move;
	}
	else if (keycode == UP_KEY)
	{
		if (e->map[(int)(e->p.pos.x + e->p.dir.x * e->p.speed.move)]
				[(int)(e->p.pos.y)] == 0)
			e->p.pos.x += e->p.dir.x * e->p.speed.move;
		if (e->map[(int)(e->p.pos.x)][(int)(e->p.pos.y + e->p.dir.y
					* e->p.speed.move)] == 0)
			e->p.pos.y += e->p.dir.y * e->p.speed.move;
	}
}

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

int			main(void)
{
	t_env		env;

	if (!(env.mlx = mlx_init()))
		return (-1);
	if (!(env.win = mlx_new_window(env.mlx, WIN_WIDTH, WIN_HEIGHT, "Wolf3D")))
		return (-1);
	mlx_key_hook(env.win, ft_hook_key, &env);
/*	uint8_t map[24][24] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};*/
	env.p = (t_player){{0, 0}, {POS_X, POS_Y}, {DIR_X, DIR_Y}, {CAM_X, CAM_Y}};
	env.frame.current = 0;
	env.frame.current = 0;
	ft_memcpy(env.map, map, sizeof(map));

	srand(time(NULL));
	ft_draw_reload(&env);
	mlx_loop_hook(env.mlx, ft_draw_reload, &env);
	mlx_hook(env.win, 2, (1L << 0), ft_hook_key, &env);
	mlx_loop(env.mlx);
	return (0);
}
