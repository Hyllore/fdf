/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 14:17:39 by droly             #+#    #+#             */
/*   Updated: 2016/05/03 18:03:40 by droly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define X (x - (fdf->line_max / 2))
# define Y (y - (fdf->count / 2))
# include <mlx.h>
# include <math.h>
# include "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/Tk.framework/Versions/8.5/Headers/X11/X.h"
# include "libft/libft.h"

typedef struct		s_fdf
{
	double			zoom;
	int				pos;
	int				line_max;
	int				count;
	void			*mlx;
	void			*win;
	char			**tab;
	char			***tab2;
}					t_fdf;

#endif
