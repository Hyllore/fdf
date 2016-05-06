/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lineput.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 16:24:49 by droly             #+#    #+#             */
/*   Updated: 2016/05/06 19:17:42 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	lineput(int *c1, int *c2, t_fdf *fdf)
{
	int dx,dy,i,xinc,yinc,cumul,x,y;
	char *tmp;

	i = 1;
	x = c1[1];
	y = c1[0];
	dx = c2[1] - x;
	dy = c2[0] - y;
	xinc = (dx > 0) ? 1 : -1;
	yinc = (dy > 0) ? 1 : -1;
	dx = abs(dx);
	dy = abs(dy);
	tmp = fdf->adr_img + ((x * fdf->bpp) + (y * fdf->sizeline));
	*(unsigned int *)tmp = 0x33FF00;
	if (dx > dy)
	{
		cumul = dx / 2;
		while ( i <= dx)
		{
			x += xinc;
			cumul += dy;
			if (cumul >= dx)
			{
				cumul -= dx;
				y += yinc;
			}
			tmp = fdf->adr_img + ((x * fdf->bpp) + (y * fdf->sizeline));
			*(unsigned int *)tmp = 0x33FF00;
			i++;
		}
	}
	else
	{
		cumul = dy / 2;
		while ( i <= dy)
		{
			y += yinc;
			cumul += dx;
			if (cumul >= dy)
			{
				cumul -= dy;
				x += xinc;
			}
			tmp = fdf->adr_img + ((x * fdf->bpp) + (y * fdf->sizeline));
			*(unsigned int *)tmp = 0x33FF00;
			i++;
		}
	}
}

void	prelineput(int c1[2], int c2[2], t_fdf *fdf)
{
	int tmp[2];

	tmp[0] = (int)((cos((45 + fdf->rotate)) * X1 -
			sin((45 + fdf->rotate)) * Y1) * fdf->zoom + fdf->pos);
	tmp[1] = (int)((-sin((45 + fdf->rotate)) * sin((35.26 +
				fdf->rotateup)) * X1 - cos((45 + fdf->rotate)) * sin((35.26 +
				fdf->rotateup)) * Y1 + cos((35.26 + fdf->rotateup)) *
				ft_atoi(fdf->tab2[c1[0]][c1[1]])) * fdf->zoom + fdf->pos);
	c1[0] = tmp[0];
	c1[1] = tmp[1];
	tmp[0] = (int)((cos((45 + fdf->rotate)) * X2 -
			sin((45 + fdf->rotate)) * Y2) * fdf->zoom + fdf->pos);
	tmp[1] = (int)((-sin((45 + fdf->rotate)) * sin((35.26 +
				fdf->rotateup)) * X2 - cos((45 + fdf->rotate)) * sin((35.26 +
				fdf->rotateup)) * Y2 + cos((35.26 + fdf->rotateup)) *
				ft_atoi(fdf->tab2[c2[0]][c2[1]])) * fdf->zoom + fdf->pos);
	c2[0] = tmp[0];
	c2[1] = tmp[1];
	lineput(c1,c2, fdf);
}
