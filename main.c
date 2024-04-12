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

# include "fdf.h"

void	init_data(int argc, char **argv, t_vars *vars)
{
	char	*s;
	char	*read;
	int 	fd;
	int		total;

	s = 0;
	if (argc != 2)
	{
		printf("Nothing turned in.. Exiting program.\n");
		exit(0);
	}
	fd = open(argv[1], O_RDONLY);
	vars->image.row = 0;
	int i = 0;
	// printf("111111111111111111111\n");
	while (1)
	{
		read = get_next_line(fd);
		if (!read)
			break ;
		printf("%d: %s", i++, read);
		if (read[ft_strlen(read) - 1] == '\n')
			read[ft_strlen(read) - 1] = ' ';
		s = ft_strjoin(s, read);
		vars->image.row++;
		free(read);
		// sleep(1);
	}
	// printf("3333333333333333333333333333\n");
	close(fd);
	// printf("s: %s", s);
	// printf("s: %s");
	vars->image.read = ft_split(s, ' ');
	total = 0;
	while (vars->image.read[total])
		total++;
	// printf("row, total: %d, %d\n", vars->image.row, total);
	vars->image.col = total / vars->image.row;
	// printf("444444444444444444444444444444\n");
	// printf("\nrow, col, total: %d, %d, %d\n", row, col, total);
}

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

// int	mouse_hook(int keycode, t_vars *vars)
// {
// 	// printf("keycode1: %d\n", keycode);
// 	return (0);
// }

// int	expose_hook(int keycode, t_vars *vars)
// {
// 	printf("keycode2: %d\n", keycode);
// 	return (0);
// }

int	close_mlx(int keycode, t_vars *vars)
{
	printf("keycode: %d\n", keycode);
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

void	init_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "FDF");
	vars->image.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT); // 이미지 객체 생성
	vars->image.addr = mlx_get_data_addr(vars->image.img, &vars->image.bits_per_pixel, \
						&vars->image.line_length, &vars->image.endian);
	vars->image.x = WIDTH / 2 + 25 * (vars->image.row - vars->image.col) * (sqrt(3) / 4);
	vars->image.y = HEIGHT / 2 - 25 * (vars->image.col + vars->image.row) / 4;
}

void	draw_z(t_vars *vars, double x, double y, int z)
{
	int	color;
	
	for (int k = 0; k <= 10 * z; k++)
	{
		double r = (double)(WIDTH - x) / (WIDTH - 1);
		double g = (double)(y-k) / (HEIGHT - 1);
		double b = 1;
		color = ((int)(255.999 * r) << 16) + ((int)(255.999 * g) << 8) + ((int)(255.999 * b));
		my_mlx_pixel_put(&vars->image, x, y - k, color);
	}
}

void	draw_top(t_vars *vars, double x, double y)
{
	int		color;
	double	xx;
	double	yy;
	
	xx = x;
	yy = y;
	for (int k = 0; k <= 25; k++)
	{
		double r = (double)(WIDTH - xx) / (WIDTH - 1);
		double g = (double)(yy) / (HEIGHT - 1);
		double b = 1;
		color = ((int)(255.999 * r) << 16) + ((int)(255.999 * g) << 8) + ((int)(255.999 * b));
		my_mlx_pixel_put(&vars->image, xx, yy, color);
		xx += sqrt(3) / 2;
		yy += 0.5;
	}
	for (int k = 0; k <= 25; k++)
	{
		double r = (double)(WIDTH - xx) / (WIDTH - 1);
		double g = (double)(yy) / (HEIGHT - 1);
		double b = 1;
		color = ((int)(255.999 * r) << 16) + ((int)(255.999 * g) << 8) + ((int)(255.999 * b));
		my_mlx_pixel_put(&vars->image, xx, yy, color);
		xx -= sqrt(3) / 2;
		yy += 0.5;
	}
	for (int k = 0; k <= 25; k++)
	{
		double r = (double)(WIDTH - xx) / (WIDTH - 1);
		double g = (double)(yy) / (HEIGHT - 1);
		double b = 1;
		color = ((int)(255.999 * r) << 16) + ((int)(255.999 * g) << 8) + ((int)(255.999 * b));
		my_mlx_pixel_put(&vars->image, xx, yy, color);
		xx -= sqrt(3) / 2;
		yy -= 0.5;
	}
	for (int k = 0; k <= 25; k++)
	{
		double r = (double)(WIDTH - xx) / (WIDTH - 1);
		double g = (double)(yy) / (HEIGHT - 1);
		double b = 1;
		color = ((int)(255.999 * r) << 16) + ((int)(255.999 * g) << 8) + ((int)(255.999 * b));
		my_mlx_pixel_put(&vars->image, xx, yy, color);
		xx += sqrt(3) / 2;
		yy -= 0.5;
	}
}

void	draw(t_vars *vars, double x, double y, int z)
{
	if (!z)
		return ;
	// printf("x, y, z: %f, %f, %d\n", x, y, z);
	draw_z(vars, x, y, z);
	draw_z(vars, x + 25 * sqrt(3) / 2, y + 25 / 2, z);
	draw_z(vars, x - 25 * sqrt(3) / 2, y + 25 / 2, z);
	draw_z(vars, x, y + 25, z);
	draw_top(vars, x, y - 10 * z);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	int color;
	init_data(argc, argv, &vars);
	// sleep(1);
	init_mlx(&vars);
	// i: height, j: width
	// printf("x, y: %d, %d\n", vars.image.x, vars.image.y);
	// printf("row, col: %d, %d\n", vars.image.row, vars.image.col);
	int i = vars.image.y;
	for (int j = 0; j <= 25 * vars.image.col; j++)
	{
		double r = (double)(WIDTH - j) / (WIDTH - 1);
		double g = (double)(i) / (HEIGHT - 1);
		double b = 1;
		color = ((int)(255.999 * r) << 16) + ((int)(255.999 * g) << 8) + ((int)(255.999 * b));
		double diag = j;
		double x = diag * cos(getRadian(30)) + vars.image.x;
		double y = diag * sin(getRadian(30)) + vars.image.y; // 30도
		// if (j == 150 || j == WIDTH - 240)
		// 	printf("x, y: %f %f\n", x, y);
		my_mlx_pixel_put(&vars.image, x, y, color);
		if (j % 25 == 0)
		{
			for (int k = 0; k <= 25 * vars.image.row; k++)
			{
				double diag1 = k;
				double x1 = x + diag1 * cos(getRadian(150));
				double y1 = y + diag1 * sin(getRadian(150));
				my_mlx_pixel_put(&vars.image, x1, y1, color);
				if (j == 0 && k % 25 == 0)
				{
					for (int l = 0; l <= 25 * vars.image.col; l++)
					{
						double diag2 = l;
						double x2 = x1 + diag2 * cos(getRadian(30));
						double y2 = y1 + diag2 * sin(getRadian(30)); 
						my_mlx_pixel_put(&vars.image, x2, y2, color);
					}
				}
			}
		}
	}

	int idx = 0;
	for (int i = 0; i < vars.image.row; i++)
	{
		double x = vars.image.x - 25 * (sqrt(3) / 2) * i;
		double y = vars.image.y + 25 * 0.5 * i;
		for (int j = 0; j < vars.image.col; j++)
		{
			// printf("i, j : %d %d\n", i, j);
			x += 25 * (sqrt(3) / 2);
			y += 25 * 0.5;
			draw(&vars, x, y, ft_atoi(vars.image.read[idx++]));
		}
	}
	mlx_put_image_to_window(vars.mlx, vars.win, vars.image.img, 0, 0);
	mlx_hook(vars.win, 17, 1L<<0, close_mlx, &vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	// mlx_mouse_hook(vars.win, mouse_hook, &vars);
	// mlx_expose_hook(vars.win, expose_hook, &vars);
	// printf("55555555555555555555555555555\n");
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