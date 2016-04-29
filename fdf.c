/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 17:12:46 by droly             #+#    #+#             */
/*   Updated: 2016/04/29 17:02:05 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>

int	putcolor(int keycode, void **mlx)
{
	int x;
	int y;

	x = 200;
	if (keycode == 49)
		while (x < 800)
		{
			y = 200;
			while (y < 800)
			{
				mlx_pixel_put(mlx[0], mlx[1], x, y, 0X00ff00f);
				y++;
			}
			x++;
		}
	x = 350;
	if (keycode == 260)
		while (x < 650)
		{
			y = 350;
			while (y < 650)
			{
				mlx_pixel_put(mlx[0], mlx[1], x, y, 0X00ff00ff);
				y++;
			}
			x++;
		}
	x = 450;
	if (keycode == 259)
		while (x < 550)
		{
			y = 450;
			while (y < 550)
			{
				mlx_pixel_put(mlx[0], mlx[1], x, y, 0X00fffff);
				y++;
			}
			x++;
		}
	x = 475;
	if (keycode == 261)
		while (x < 525)
		{
			y = 475;
			while (y < 525)
			{
				mlx_pixel_put(mlx[0], mlx[1], x, y, 0X00ff);
				y++;
			}
			x++;
		}
	printf("%d\n", keycode);
	return (0);
}

int	main()
{
	void **mlx;
//	void *win;
	int x;
	int y;


	mlx[0] = mlx_init();
	mlx[1] = mlx_new_window(mlx[0], 1000, 1000, "fdf");
	x = 0;
	while (x < 1000)
	{
		y = 0;
		while (y < 1000)
		{
			mlx_pixel_put(mlx[0], mlx[1], x, y, 0X00fff);
			y++;
		}
		x++;
	}
	mlx_key_hook(mlx[1], putcolor, mlx);
	mlx_loop(mlx[0]);
}
