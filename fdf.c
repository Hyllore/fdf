/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 17:12:46 by droly             #+#    #+#             */
/*   Updated: 2016/05/02 18:56:18 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error(char *str)
{
	ft_putendl(str);
	exit(0);
}

char	**init_tab(char *tab, char **argv)
{
	int i;
	char **tab2;
	int fd;

	fd = open(argv[1], 0, O_RDONLY);
	tab2 = NULL;
	i = 0;
	while (get_next_line(fd, &tab) == 1)
		i++;
	if ((tab2 = (char**)malloc(sizeof(char*) * (i + 1))) == NULL)
		error("ERROR : malloc.");
	fd = open(argv[1], 0, O_RDONLY);
	i = 0;
	while (get_next_line(fd, &tab2[i]) == 1)
	{
		i++;
	}
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
	fdf->win = mlx_new_window(fdf->mlx, 1000, 1000, "fdf");
	fdf->tab = init_tab(NULL, argv);
	while (fdf->tab[i] != NULL)
	{
		ft_putendl(fdf->tab[i]);
		i++;
	}
//	mlx_key_hook(mlx[1], putcolor, mlx);
//	mlx_loop(mlx[0]);
}
