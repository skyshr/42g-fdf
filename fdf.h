/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 22:19:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/04/09 22:19:49 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include "get_next_line_bonus.h"
# include <stdio.h>
# include <fcntl.h>
// # define __USE_MISC
// #define __USE_XOPEN
# include "math.h"
# define WIDTH 1200
# define HEIGHT 800

typedef struct s_data
{
	void 	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	**read;
	int		row;
	int		col;
	int		x;
	int		y;
}		t_data;

typedef struct	s_vars {
	void			*mlx;
	void			*win;
	struct s_data	image;
}				t_vars;

#endif