/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 17:12:46 by droly             #+#    #+#             */
/*   Updated: 2016/05/09 16:50:14 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		add_free_all(t_fdf *fdf, int i, int i2)
{
	if (fdf->tab)
	{
		while (fdf->tab[i] != NULL)
		{
			free(fdf->tab[i]);
			i++;
		}    
		free(fdf->tab);
	}
	i = 0;
	if (fdf->tab2)
	{
		while (fdf->tab2[i] != NULL)
		{
			while (fdf->tab2[i][i2] != NULL)
			{
				free(fdf->tab2[i][i2]);
				i2++;
			}
			i2 = 0;
			free(fdf->tab2[i]);
			i++;
		}
		free(fdf->tab2);
	}
}

void		free_all(t_fdf *fdf)
{
	if (fdf->adr_img)
		free(fdf->adr_img);
	if (fdf->img)
		free(fdf->img);
	if (fdf->mlx)
		free(fdf->mlx);
	if (fdf->win)
		free(fdf->win);
	add_free_all(fdf, 0, 0);
	free(fdf);
}

void		init_struct(t_fdf *fdf, char **argv)
{
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, SIZE, SIZE, "fdf");
	fdf->tab = init_tab(NULL, argv, fdf);
	split_tab(fdf);
	fdf->zoom = 25;
	fdf->pos = SIZE / 2;
	fdf->rotate = 0;
	fdf->rotateup = 0;
	fdf->line_max = ft_tablen(fdf->tab2);
	fdf->img = mlx_new_image(fdf->mlx, SIZE, SIZE);
	fdf->adr_img = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->sizeline,
			&fdf->bidon);
	fdf->bpp /= 8;
}

int			main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc != 2)
		error("ERROR : more or less than 1 file passed to FDF.");
	if ((fdf = (t_fdf*)malloc(sizeof(t_fdf))) == NULL)
		error("ERROR : malloc.");
	init_struct(fdf, argv);
	analyze_tab(0, fdf);
	mlx_hook(fdf->win, KeyPress, KeyPressMask, analyze_tab, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
