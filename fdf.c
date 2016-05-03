/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 17:12:46 by droly             #+#    #+#             */
/*   Updated: 2016/05/03 18:06:58 by droly            ###   ########.fr       */
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
	int i2;

	i2 = 0;
	i = 0;
	if ((fdf->tab2 = (char***)malloc(sizeof(char**) * (fdf->count + 1))) == NULL)
		error("ERROR : Malloc.");
	while (i < fdf->count)
	{
		fdf->tab2[i] = ft_strsplit(fdf->tab[i], ' ');
		i++;
	}
	fdf->tab2[i] = NULL;
	i = 0;
}

//int test(int keycode, t_fdf *fdf)
//{
//	printf("keycode : %i // zoom : %i\n", keycode, fdf->zoom);
//	return (0);
//}

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

int		analyze_tab(int keycode, t_fdf *fdf)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if (keycode == 69)
	{
		mlx_clear_window(fdf->mlx, fdf->win);
//		if (fdf->zoom < 10)
			fdf->zoom += 0.4;
//		if (fdf->zoom > 10 && fdf->zoom < 20)
//			fdf->zoom += 5;
	}
	if (keycode == 78)
	{
		mlx_clear_window(fdf->mlx, fdf->win);
		if (fdf->zoom > 0)
			fdf->zoom -= 0.4;
	}
	while (fdf->tab2[y] != NULL)
	{
		while (fdf->tab2[y][x] != NULL)
		{
			mlx_pixel_put(fdf->mlx, fdf->win, (cos(45) * X - sin(45) * Y) * fdf->zoom + fdf->pos, (-sin(45) * sin(35.26) * X -cos(45) * sin(35.26) * Y + cos(35.26) * ft_atoi(fdf->tab2[y][x])) * fdf->zoom + fdf->pos , 0xFFFFFF);
				x++;
		}
		x = 0;
		y++;
	}
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
//	int i2;

//	i2 = 0;
	i = 0;
	argc = 1;
	if ((fdf = (t_fdf*)malloc(sizeof(t_fdf))) == NULL)
		error("ERROR : malloc.");
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, 1000, 1000, "fdf");
	fdf->tab = init_tab(NULL, argv, fdf);
	split_tab(fdf);
	fdf->zoom = 1.5;
	fdf->pos = 500;
	fdf->line_max = ft_tablen(fdf->tab2);
	analyze_tab(0, fdf);
//	while (fdf->tab[i] != NULL)
//	{
//		ft_putendl(fdf->tab[i]);
//		i++;
//	}
//	i = 0;
//	while (fdf->tab2[i] != NULL)
//	{
//		ft_putchar('t');
//		while (fdf->tab2[i][i2] != NULL)
//		{
//			ft_putchar('l');
//			ft_putstr(fdf->tab2[i][i2]);
//			if (ft_strlen(fdf->tab2[i][i2]) == 1)
//				ft_putstr("  ");
//			else
//				ft_putchar(' ');
//			i2++;
//		}
//		ft_putchar('\n');
//		i2 = 0;
//		i++;
//	}
	ft_putchar('r');
	mlx_hook(fdf->win, KeyPress, KeyPressMask, analyze_tab, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
