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
# define WH 0xffffff
# define GY 0xbebebe
// # define AB 0xfffff0
# define AB 0x191970
# define BK 0x0
# define ANG_1				0.01745329
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
	int		angle_x;
	int		angle_y;
	int		angle_z;
	double	z_scale;
	double	vector_x[2];
	double	vector_y[2];
	double	vector_z[2];
	int		alpha;
	int		beta;
	int		gamma;
}		t_data;

typedef struct	s_vars {
	void			*mlx;
	void			*win;
	struct s_data	image;
}				t_vars;

void	reset_img(t_vars *vars);
void	print_vector(t_data *image);
void	translate_x_pos(t_data *image);
void	translate_x_neg(t_data *image);
void	translate_y_pos(t_data *image);
void	translate_y_neg(t_data *image);
void	translate_z_pos(t_data *image);
void	translate_z_neg(t_data *image);
void	rotate_z_pos(t_data *image);
void	rotate_z_neg(t_data *image);
void	rotate_x_pos(t_data *image);
void	rotate_x_neg(t_data *image);
void	rotate_y_pos(t_data *image);
void	rotate_y_neg(t_data *image);
void	set_vector(t_data *image);
void	draw(t_vars *vars);

#endif