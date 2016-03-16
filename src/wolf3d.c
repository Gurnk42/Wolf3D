/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 11:53:35 by ebouther          #+#    #+#             */
/*   Updated: 2016/03/16 13:56:29 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int ft_hook_key(int keycode)
{
	ft_printf("KEYCODE: '%d'\n", keycode);
	if (keycode == 53)
		exit(0);
	return (0);
}

int				main(/*int argc, char **argv*/)
{
//	char		*line;
	t_env		env;
//	int			fd;
//	int			i;

	if (!(env.mlx = mlx_init()))
		return (-1);
	if (!(env.win = mlx_new_window(env.mlx, WIN_WIDTH, WIN_HEIGHT, "Texture")))
		return (-1);
	mlx_key_hook(env.win, ft_hook_key, &env);

/*	fd = open(argv[1], O_RDONLY);
	int n = 0;
	while (get_next_line(fd, &line))
	{
		if (n > 2)
		{
			
		}
		i = 0;
		while (line[i] != '\0')
		{
			ft_printf("%c", ((unsigned char *)line)[i]);
			i++;
		}
		ft_printf("\n");
		n++;
	}
	close(fd);*/

	//	mlx_expose_hook(env.win, ft_expose_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}
