/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lineput.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 16:24:49 by droly             #+#    #+#             */
/*   Updated: 2016/05/10 14:04:08 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			ft_tablen2(char **tab)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (tab[i] != NULL)
	{
		count++;
		i++;
	}
	return (count);
}

int			*addlineput1(int *num, t_fdf *fdf, char *tmp)
{
	num[5] = num[0] / 2;
	while (num[2] <= num[0])
	{
		num[6] += num[3];
		num[5] += num[1];
		if (num[5] >= num[0])
		{
			num[5] -= num[0];
			num[7] += num[4];
		}
		if (num[6] >= 0 && num[7] >= 0 && num[6] < SIZE && num[7] < SIZE)
		{
			tmp = fdf->adr_img + ((num[6] * fdf->bpp) + (num[7] *
						fdf->sizeline));
			*(unsigned int *)tmp = 0x33FF00;
		}
		num[2]++;
	}
	return (num);
}

int			*addlineput2(int *num, t_fdf *fdf, char *tmp)
{
	num[5] = num[1] / 2;
	while (num[2] <= num[1])
	{
		num[7] += num[4];
		num[5] += num[0];
		if (num[5] >= num[1])
		{
			num[5] -= num[1];
			num[6] += num[3];
		}
		if (num[6] >= 0 && num[7] >= 0 && num[6] < SIZE && num[7] < SIZE)
		{
			tmp = fdf->adr_img + ((num[6] * fdf->bpp) + (num[7] *
						fdf->sizeline));
			*(unsigned int *)tmp = 0x33FF00;
		}
		num[2]++;
	}
	return (num);
}

void		lineput(int *c1, int *c2, t_fdf *fdf)
{
	int		num[8];
	char	*tmp;

	num[2] = 1;
	num[6] = c1[1];
	num[7] = c1[0];
	num[0] = c2[1] - num[6];
	num[1] = c2[0] - num[7];
	num[3] = (num[0] > 0) ? 1 : -1;
	num[4] = (num[1] > 0) ? 1 : -1;
	num[0] = abs(num[0]);
	num[1] = abs(num[1]);
	if (num[6] >= 0 && num[7] >= 0 && num[6] < SIZE && num[7] < SIZE)
	{
		tmp = fdf->adr_img + ((num[6] * fdf->bpp) + (num[7] * fdf->sizeline));
		*(unsigned int *)tmp = 0x33FF00;
	}
	if (num[0] > num[1])
		addlineput1(num, fdf, tmp);
	else
		addlineput2(num, fdf, tmp);
}

void		prelineput(int c1[2], int c2[2], t_fdf *fdf)
{
	int		tmp[2];

	tmp[1] = (int)((cos((45 + fdf->rotate)) * X1 -
			sin((45 + fdf->rotate)) * Y1) * fdf->zoom + fdf->pos);
	tmp[0] = (int)((-sin((45 + fdf->rotate)) * sin((35.26 +
				fdf->rotateup)) * X1 - cos((45 + fdf->rotate)) * sin((35.26 +
				fdf->rotateup)) * Y1 + cos((35.26 + fdf->rotateup)) *
				ft_atoi(fdf->tab2[c1[0]][c1[1]])) * fdf->zoom + fdf->pos);
	c1[0] = tmp[0];
	c1[1] = tmp[1];
	tmp[1] = (int)((cos((45 + fdf->rotate)) * X2 -
			sin((45 + fdf->rotate)) * Y2) * fdf->zoom + fdf->pos);
	tmp[0] = (int)((-sin((45 + fdf->rotate)) * sin((35.26 +
				fdf->rotateup)) * X2 - cos((45 + fdf->rotate)) * sin((35.26 +
				fdf->rotateup)) * Y2 + cos((35.26 + fdf->rotateup)) *
				ft_atoi(fdf->tab2[c2[0]][c2[1]])) * fdf->zoom + fdf->pos);
	c2[0] = tmp[0];
	c2[1] = tmp[1];
	lineput(c1, c2, fdf);
}
