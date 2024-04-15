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
# include "math.h"
# define WIDTH 1500
# define HEIGHT 1000
# define WH 16777215
# define GY 0xbebebe
// # define AB 0xfffff0
# define AB 0x191970
// "ivory" , 0xfffff0

typedef struct s_data
{
	void 	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		*read;
	int		row;
	int		col;
	int		x;
	int		y;
	int		size;
	int		z_size;
	int		range_max;
	int		range_min;
	int		default_size;
	int		default_z_size;
	int		dir;
	int		total;
}		t_data;

typedef struct	s_vars {
	void			*mlx;
	void			*win;
	struct s_data	image;
}				t_vars;

void	reset_img(t_vars *vars);

#endif