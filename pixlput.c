/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixlput.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 14:03:06 by droly             #+#    #+#             */
/*   Updated: 2016/05/09 18:19:51 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		clear_img(t_fdf *fdf)
{
	int		x;
	int		y;
	char	*tmp;

	x = 0;
	y = 0;
	while (y != SIZE)
	{
		while (x != SIZE)
		{
			tmp = fdf->adr_img + x * fdf->bpp + y * fdf->sizeline;
			*(unsigned int *)tmp = 0x000000;
			x++;
		}
		x = 0;
		y++;
	}
}

void		add_analyze_tab(int x, int y, t_fdf *fdf)
{
	int		c1[2];
	int		c2[2];

	if (fdf->tab2[y + 1])
	{
		if (fdf->tab2[y + 1][x])
		{
			ft_putstr(fdf->tab2[y + 1][x]);
			ft_putchar(' ');
			c1[0] = y;
			c1[1] = x;
			c2[0] = y + 1;
			c2[1] = x;
			prelineput(c1, c2, fdf);
		}
	}
	if (fdf->tab2[y][x + 1])
	{
		c1[0] = y;
		c1[1] = x;
		c2[0] = y;
		c2[1] = x + 1;
		prelineput(c1, c2, fdf);
	}
}

int			analyze_tab(int keycode, t_fdf *fdf)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	mlx_clear_window(fdf->mlx, fdf->win);
	ft_keycode(keycode, fdf);
	while (fdf->tab2[y] != NULL)
	{
		while (fdf->tab2[y][x] != NULL)
		{
			add_analyze_tab(x, y, fdf);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	clear_img(fdf);
	return (0);
}

void		ft_keycode(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
	{
		free_all(fdf);
		exit(0);
	}
	if (keycode == 69)
		if (fdf->zoom > 0)
			fdf->zoom *= 1.1;
	if (keycode == 78)
		if (fdf->zoom > 0)
			fdf->zoom /= 1.1;
	if (keycode == 124)
		fdf->rotate -= 0.02;
	if (keycode == 123)
		fdf->rotate += 0.02;
	if (keycode == 125)
		fdf->rotateup += 0.02;
	if (keycode == 126)
		fdf->rotateup -= 0.02;
}
