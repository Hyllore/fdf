/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 14:17:39 by droly             #+#    #+#             */
/*   Updated: 2016/05/06 17:59:41 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define X (x - (fdf->line_max / 2))
# define Y (y - (fdf->count / 2))
# define X1 (c1[1] - (fdf->line_max / 2))
# define Y1 (c1[0] - (fdf->count / 2))
# define X2 (c2[1] - (fdf->line_max / 2))
# define Y2 (c2[0] - (fdf->count / 2))
# define SIZE 1000
# include <mlx.h>
# include <math.h>
# include "X.h"
# include "libft/libft.h"

typedef struct	s_fdf
{
//	int			high;
	double		zoom;
	int			pos;
	int			bpp;
	int			sizeline;
	int			bidon;
	int			line_max;
	int			count;
	char		*adr_img;
	void		*img;
	void		*mlx;
	void		*win;
	char		**tab;
	char		***tab2;
	double		rotate;
	double		rotateup;
}				t_fdf;

void			error(char *str);
void			split_tab(t_fdf *fdf);
int				ft_tablen(char ***tab);
int				analyze_tab(int keycode, t_fdf *fdf);
char			**init_tab(char *tab, char **argv, t_fdf *fdf);
void			clear_img(t_fdf *fdf);
void			ft_keycode(int keycode, t_fdf *fdf);
void			pixlput(t_fdf *fdf, int x, int y, int tmp_t);
void			prelineput(int c1[2], int c2[2], t_fdf *fdf);

#endif
