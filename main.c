/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 22:17:32 by ksuh              #+#    #+#             */
/*   Updated: 2024/04/09 22:17:34 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
#define __USE_XOPEN
# include "math.h"

typedef struct s_data
{
	void 	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_data;

typedef struct	s_vars {
	void			*mlx;
	void			*win;
	struct s_data	image;
}				t_vars;

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
		// ((t_xvar *)vars->mlx)->end_loop = 1;
		free(vars->image.img);
		free(vars->image.addr);
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	// printf("keycode: %d\n", keycode);
	return (0);
}

int	mouse_hook(int keycode, t_vars *vars)
{
	// printf("keycode1: %d\n", keycode);
	return (0);
}

int	expose_hook(int keycode, t_vars *vars)
{
	printf("keycode2: %d\n", keycode);
	return (0);
}

int	close_mlx(int keycode, t_vars *vars)
{
	free(vars->image.img);
	free(vars->image.addr);
	mlx_destroy_window(vars->mlx, vars->win);
	// ((t_xvar *)vars->mlx)->end_loop = 1;
	// free(vars->mlx);
	// free(vars->win);
	exit(0);
	// return (0);
}

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

double	getRadian(int _num)
{
	return _num * (M_PI / 180);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	int img_width = 640;
	int img_height = 480;
	int color;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 6400, 4800, "Hello world!");
	vars.image.img = mlx_new_image(vars.mlx, 6400, 4800); // 이미지 객체 생성
	vars.image.addr = mlx_get_data_addr(vars.image.img, &vars.image.bits_per_pixel, &vars.image.line_length, &vars.image.endian);
	// i: height, j: width
	// for (int i = 150 ; i < img_height - 150 ; i+=25)
	// {
		int i = 150;
		for (int j = 150; j <= img_width - 240; j++)
		{
			double r = (double)(img_width - j) / (img_width - 1);
			double g = (double)(i) / (img_height - 1);
			double b = 1;
			color = ((int)(255.999 * r) << 16) + ((int)(255.999 * g) << 8) + ((int)(255.999 * b));
			double diag = j - 150;
			double x = diag * cos(getRadian(45)) + 150;
			double y = diag * sin(getRadian(45)) + i; // 30도
			if (j == 150 || j == img_width - 240)
				printf("x, y: %f %f\n", x, y);
			// if (x > 490 || x < 0 || y > 330 || y < 0)
			// 	continue;
			my_mlx_pixel_put(&vars.image, x, y, color);
			if (j % 25 == 0)
			{
				for (int k = i; k < img_height - 150; k++)
				{
					double diag1 = k - 150;
					double x1 = x + diag1 * cos(getRadian(135));
					double y1 = y + diag1 * sin(getRadian(135));
					// 0.523599 = 30
					// 1.5708 = 90
					// 1.8326 = 105
					// 2.0944 = 120
					my_mlx_pixel_put(&vars.image, x1, y1, color);
					if (j == 150 && k % 25 == 0)
					{
						for (int l = 150; l <= img_width - 240; l++)
						{
							double diag2 = l - 150;
							double x2 = x1 + diag2 * cos(getRadian(45));
							double y2 = y1 + diag2 * sin(getRadian(45)); 
							my_mlx_pixel_put(&vars.image, x2, y2, color);
							if (x2 > 490 || x2 < 0 || y2 > 330 || y2 < 0)
								continue;
						}
					}
				}
			}
		}
	// }
	mlx_put_image_to_window(vars.mlx, vars.win, vars.image.img, 0, 0);
	mlx_hook(vars.win, 17, 1L<<0, close_mlx, &vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	// mlx_mouse_hook(vars.win, mouse_hook, &vars);
	// mlx_expose_hook(vars.win, expose_hook, &vars);
	mlx_loop(vars.mlx);
	// free(vars.mlx);
	// free(vars.win);
	// free(image.img);
	// free(image.addr);
	return 0;
}

// cc main.c -Lminilibx-linux -lmlx -L./minilibx-linux -Iminilibx-linux -lXext -lX11 -lm -lz
// %o: %.c
//		$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@
// $(NAME): $(OBJ)
//		$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)