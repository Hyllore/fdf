/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixlput.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 14:03:06 by droly             #+#    #+#             */
/*   Updated: 2016/05/06 19:17:44 by droly            ###   ########.fr       */
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
	int c1[2];
	int c2[2];

	pixlput(fdf, x, y, 0);
	if (fdf->tab2[y + 1])
	{
		if (fdf->tab2[y + 1][x])
		{
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
		free(fdf->tab);
		free(fdf->tab2);
		free(fdf);
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
//	if (keycode == 116)
//		fdf->high += 1;
//	if (keycode == 121)
//		fdf->high -= 1;
}

void		pixlput(t_fdf *fdf, int x, int y, int tmp_t)
{
	char	*tmp;

	tmp_t = (cos((45 + fdf->rotate)) * X - sin((45 + fdf->rotate)) * Y)
		* fdf->zoom + fdf->pos;
	if (tmp_t >= 0 && tmp_t < SIZE)
	{
//		if (ft_atoi(fdf->tab2[y][x]) != 0)
//			tmp_t = (int)((-sin((45 + fdf->rotate)) * sin((35.26 +
//				fdf->rotateup)) * X - cos((45 + fdf->rotate)) * sin((35.26 +
///				fdf->rotateup)) * Y + cos((35.26 + fdf->rotateup)) *
//				(ft_atoi(fdf->tab2[y][x]) + fdf->high)) *
//				fdf->zoom + fdf->pos);
//		else
			tmp_t = (int)((-sin((45 + fdf->rotate)) * sin((35.26 +
				fdf->rotateup)) * X - cos((45 + fdf->rotate)) * sin((35.26 +
				fdf->rotateup)) * Y + cos((35.26 + fdf->rotateup)) *
				ft_atoi(fdf->tab2[y][x])) * fdf->zoom + fdf->pos);
		if (tmp_t >= 0 && tmp_t < SIZE)
		{
			tmp = fdf->adr_img + (int)((cos((45 + fdf->rotate)) * X -
			sin((45 + fdf->rotate)) * Y) * fdf->zoom + fdf->pos) * fdf->bpp +
			(tmp_t * fdf->sizeline);
			*(unsigned int *)tmp = 0x33FF00;
		}
	}
}
