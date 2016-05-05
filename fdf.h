/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 14:17:39 by droly             #+#    #+#             */
/*   Updated: 2016/05/05 17:50:37 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define X (x - (fdf->line_max / 2))
# define Y (y - (fdf->count / 2))
# define SIZE 1000
# include <mlx.h>
# include <math.h>
# include "X.h"
# include "libft/libft.h"

typedef struct		s_fdf
{
	int				high;
	double			zoom;
	int				pos;
	int				bpp;
	int				sizeline;
	int				bidon;
	int				line_max;
	int				count;
	char			*adr_img;
	void			*img;
	void			*mlx;
	void			*win;
	char			**tab;
	char			***tab2;
	double			rotate;
	double			rotateup;
}					t_fdf;

#endif
