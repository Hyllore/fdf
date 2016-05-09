/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inittab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 14:05:13 by droly             #+#    #+#             */
/*   Updated: 2016/05/09 18:04:56 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		error(char *str)
{
	ft_putendl(str);
	exit(0);
}

void		split_tab(t_fdf *fdf)
{
	int		i;

	i = 0;
	if ((fdf->tab2 = (char***)malloc(sizeof(char**) * (fdf->count + 1))) ==
			NULL)
		error("ERROR : Malloc.");
	while (i < fdf->count)
	{
		fdf->tab2[i] = ft_strsplit(fdf->tab[i], ' ');
		i++;
	}
	fdf->tab2[i] = NULL;
}

int			ft_tablen(char ***tab)
{
	int		i;
	int		i2;
	int		count;

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

void		check_file(char *tab)
{
	int i;

	i = 0;
	while (tab[i] != '\0')
	{
		if ((tab[i] >= '0' && tab[i] <= '9') || tab[i] == ' ' || tab[i] == '-')
			i++;
		else
		{
			ft_printf("error : '%c'\n", tab[i]);
			error("ERROR : Not a valid file.");
		}
	}
}

char		**init_tab(char *tab, char **argv, t_fdf *fdf)
{
	int		i;
	char	**tab2;
	int		fd;

	if ((fd = open(argv[1], O_RDONLY)) == -1)
		error("ERROR : not a valid file.");
	i = 0;
	tab2 = NULL;
	fdf->count = 0;
	while (get_next_line(fd, &tab) == 1)
	{
		check_file(tab);
		fdf->count++;
	}
	if ((tab2 = (char**)malloc(sizeof(char*) * (fdf->count + 1))) == NULL)
		error("ERROR : malloc.");
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &tab2[i]) == 1)
		i++;
	tab2[i] = NULL;
	return (tab2);
}
