/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 17:12:46 by droly             #+#    #+#             */
/*   Updated: 2016/05/05 16:40:00 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	error(char *str)
{
	ft_putendl(str);
	exit(0);
}

void	split_tab(t_fdf *fdf)
{
	int i;

	i = 0;
	if ((fdf->tab2 = (char***)malloc(sizeof(char**) * (fdf->count + 1))) == NULL)
		error("ERROR : Malloc.");
	while (i < fdf->count)
	{
		fdf->tab2[i] = ft_strsplit(fdf->tab[i], ' ');
		i++;
	}
	fdf->tab2[i] = NULL;
}

int		ft_tablen(char ***tab)
{
	int i;
	int i2;
	int count;

	count = 0;
	i = 0;
	i2 = 0;
	while (tab[i] != NULL)
	{
		while (tab[i][i2] != NULL)
			i2++;
		if (i2 > count)
			count = i2;
		i2 = 0;
		i++;
	}
	return (count);
}

void	clear_img(t_fdf *fdf)
{
	int x;
	int y;
	char *tmp;

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

int		analyze_tab(int keycode, t_fdf *fdf)
{
	int x;
	int y;
	char	*tmp;
	int		tmp_t;
//	int i;

	x = 0;
	y = 0;
	mlx_clear_window(fdf->mlx, fdf->win);
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
	if (keycode == 116)
		fdf->high += 1;
	if (keycode == 121)
		fdf->high -= 1;
	while (fdf->tab2[y] != NULL)
	{
		while (fdf->tab2[y][x] != NULL)
		{
			tmp_t = (cos((45 + fdf->rotate)) * X - sin((45 + fdf->rotate)) * Y) * fdf->zoom + fdf->pos;
			if (tmp_t >= 0 && tmp_t < SIZE)
			{
				if (ft_atoi(fdf->tab2[y][x]) != 0)
					tmp_t = (int)((-sin((45 + fdf->rotate)) * sin((35.26 + fdf->rotateup)) * X -cos((45 + fdf->rotate)) * sin((35.26 + fdf->rotateup)) * Y + cos((35.26 + fdf->rotateup)) * (ft_atoi(fdf->tab2[y][x]) + fdf->high)) * fdf->zoom + fdf->pos);
				else
					tmp_t = (int)((-sin((45 + fdf->rotate)) * sin((35.26 + fdf->rotateup)) * X -cos((45 + fdf->rotate)) * sin((35.26 + fdf->rotateup)) * Y + cos((35.26 + fdf->rotateup)) * ft_atoi(fdf->tab2[y][x])) * fdf->zoom + fdf->pos);
				if (tmp_t >= 0 && tmp_t < SIZE)
				{
					tmp = fdf->adr_img + (int)((cos((45 + fdf->rotate)) * X - sin((45 + fdf->rotate)) * Y) * fdf->zoom + fdf->pos) * fdf->bpp + (tmp_t * fdf->sizeline);
					*(unsigned int *)tmp = 0xFFFFFF;
				}
			}
				x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	clear_img(fdf);
	return (0);
}

char	**init_tab(char *tab, char **argv, t_fdf *fdf)
{
	int i;
	char **tab2;
	int fd;

	fd = open(argv[1], 0, O_RDONLY);
	i = 0;
	tab2 = NULL;
	fdf->count = 0;
	while (get_next_line(fd, &tab) == 1)
		fdf->count++;
	if ((tab2 = (char**)malloc(sizeof(char*) * (fdf->count + 1))) == NULL)
		error("ERROR : malloc.");
	fd = open(argv[1], 0, O_RDONLY);
	while (get_next_line(fd, &tab2[i]) == 1)
		i++;
	tab2[i] = NULL;
	return (tab2);
}

int	main(int argc, char **argv)
{
	t_fdf *fdf;
	int i;

	i = 0;
	argc = 1;
	if ((fdf = (t_fdf*)malloc(sizeof(t_fdf))) == NULL)
		error("ERROR : malloc.");
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, SIZE, SIZE, "fdf");
	fdf->tab = init_tab(NULL, argv, fdf);
	split_tab(fdf);
	fdf->zoom = 25;
	fdf->pos = SIZE / 2;
	fdf->rotate = 0;
	fdf->rotateup = 0;
	fdf->high = 0;
	fdf->line_max = ft_tablen(fdf->tab2);
	fdf->img = mlx_new_image(fdf->mlx, SIZE, SIZE);
	fdf->adr_img = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->sizeline, &fdf->bidon);
	fdf->bpp /= 8;
	analyze_tab(0, fdf);
	mlx_hook(fdf->win, KeyPress, KeyPressMask, analyze_tab, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
