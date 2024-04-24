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

	s = NULL;
	if (argc != 2)
	{
		printf("Nothing turned in.. Exiting program.\n");
		exit(0);
	}
	fd = open(argv[1], O_RDONLY);
	vars->image.row = 0;
	while (1)
	{
		read = get_next_line(fd);
		if (!read)
			break ;
		if (read[ft_strlen(read) - 1] == '\n')
			read[ft_strlen(read) - 1] = ' ';
		s = ft_strjoin(&s, read);
		vars->image.row++;
		free(read);
	}
	close(fd);
	if (!s)
		exit(0);
	vars->image.read = ft_split(s, ' ', &vars->image.total);
	free(s);
	s = NULL;
	// printf("total: %d\n", vars->image.total);
	vars->image.col = vars->image.total / vars->image.row;
	printf("row, col, total: %d, %d, %d\n", vars->image.row, vars->image.col, vars->image.total);
}

void	reset_canvas(t_data *canvas)
{
	char	*dst;
	int		size;

	dst = canvas->addr;
	size = WIDTH * HEIGHT;
	while (size--)
	{
		*(unsigned int*)dst = BK;
		dst += 4;
	}
}

int	key_hook(int keycode, t_vars *vars)
{
	printf("keycode: %d\n", keycode);
	if (keycode == 65307)
		((t_xvar *)vars->mlx)->end_loop = 1;
	else if (keycode == 97)
	{
		rotate_x_pos(&vars->image);
		reset_img(vars);
	}
	else if (keycode == 100)
	{
		rotate_x_neg(&vars->image);
		reset_img(vars);
	}
	else if (keycode == 115)
	{
		rotate_y_pos(&vars->image);
		reset_img(vars);
	}
	else if (keycode == 119)
	{
		rotate_y_neg(&vars->image);
		reset_img(vars);
	}
	else if (keycode == 122)
	{
		rotate_z_pos(&vars->image);
		reset_img(vars);
	}
	else if (keycode == 99)
	{
		rotate_z_neg(&vars->image);
		reset_img(vars);
	}
	else if (keycode == 114)
	{
		vars->image.size = vars->image.default_size;
		vars->image.z_size = vars->image.default_z_size;
		set_vector(&vars->image);
		reset_img(vars);
	}
	else if (keycode == 65431)
	{
		translate_y_pos(&vars->image);
		mlx_destroy_image(vars->mlx, vars->image.img);
		vars->image.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
		vars->image.addr = mlx_get_data_addr(vars->image.img, &vars->image.bits_per_pixel, \
						&vars->image.line_length, &vars->image.endian);
		draw(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, 0, 0);
	}
	else if (keycode == 65433)
	{
		translate_y_neg(&vars->image);
		mlx_destroy_image(vars->mlx, vars->image.img);
		vars->image.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
		vars->image.addr = mlx_get_data_addr(vars->image.img, &vars->image.bits_per_pixel, \
						&vars->image.line_length, &vars->image.endian);
		draw(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, 0, 0);
	}
	else if (keycode == 65430)
	{
		translate_x_pos(&vars->image);
		mlx_destroy_image(vars->mlx, vars->image.img);
		vars->image.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
		vars->image.addr = mlx_get_data_addr(vars->image.img, &vars->image.bits_per_pixel, \
						&vars->image.line_length, &vars->image.endian);
		draw(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, 0, 0);
	}
	else if (keycode == 65432)
	{
		translate_x_neg(&vars->image);
		mlx_destroy_image(vars->mlx, vars->image.img);
		vars->image.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
		vars->image.addr = mlx_get_data_addr(vars->image.img, &vars->image.bits_per_pixel, \
						&vars->image.line_length, &vars->image.endian);
		draw(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, 0, 0);
	}
	else if (keycode == 65434)
	{
		translate_z_pos(&vars->image);
		mlx_destroy_image(vars->mlx, vars->image.img);
		vars->image.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
		vars->image.addr = mlx_get_data_addr(vars->image.img, &vars->image.bits_per_pixel, \
						&vars->image.line_length, &vars->image.endian);
		draw(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, 0, 0);
	}
	else if (keycode == 65436)
	{
		translate_z_neg(&vars->image);
		mlx_destroy_image(vars->mlx, vars->image.img);
		vars->image.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
		vars->image.addr = mlx_get_data_addr(vars->image.img, &vars->image.bits_per_pixel, \
						&vars->image.line_length, &vars->image.endian);
		draw(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, 0, 0);
	}
	else if (keycode == 111)
		orthogonal(vars);
	return (0);
}

int	close_mlx(t_vars *vars)
{
	key_hook(65307, vars);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
		return;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

double	getRadian(int _num)
{
	return _num * (M_PI / 180);
}

void	calculate_size(t_vars *vars)
{
	double	size;
	double	l;
	double	range_max;

	size = 25;
	range_max = 500;
	if (vars->image.row == vars->image.col)
	{
		l = ft_max(vars->image.row, vars->image.col);
		if (l * sqrt(3) >= (WIDTH - 200))
		{
			printf("Error\n");
			exit(1);
		}
		range_max = ft_min(range_max, (WIDTH - 200) / sqrt(3));
	}
	else
	{
		l = 2 * ((WIDTH - 200) / sqrt(3) - vars->image.col) / (vars->image.col - vars->image.row);
		if (l > 0)
			range_max = ft_min(range_max, l);
	}
	l = 2 * (HEIGHT - 200) / (vars->image.row + vars->image.col);
	range_max = ft_min(range_max, l);
	if (range_max < 25)
		vars->image.size = range_max;
	else
		vars->image.size = ft_min(25 + range_max / 3, range_max);
	vars->image.default_size = vars->image.size;
	vars->image.range_max = vars->image.size * (3 + 0.05 * (range_max - vars->image.size));
	vars->image.range_min = ft_max(vars->image.size / 10, 1);
	vars->image.z_size = 0;
	vars->image.z_scale = 1;
	// printf("range_max: %f\n", range_max);
	// printf("size: %d\n", vars->image.size);
	// printf("range: %d, %d\n", vars->image.range_max, vars->image.range_min);
}

void	print_vector(t_data *image)
{
	printf("x, y, z: %d, %d, %d\n", image->angle_x, image->angle_y, image->angle_z);
	printf("vector_x: %f, %f\n", image->vector_x[0], image->vector_x[1]);
	printf("vector_y: %f, %f\n", image->vector_y[0], image->vector_y[1]);
	printf("vector_z: %f, %f\n", image->vector_z[0], image->vector_z[1]);
}

void	translate_x_pos(t_data *image)
{
	image->x -= 5;
}

void	translate_x_neg(t_data *image)
{
	image->x += 5;
}

void	translate_y_pos(t_data *image)
{
	image->y -= 5;
}

void	translate_y_neg(t_data *image)
{
	image->y += 5;
}

void	translate_z_pos(t_data *image)
{
	if (image->z_scale < 5)
		image->z_scale += 0.5;
}

void	translate_z_neg(t_data *image)
{
	if (image->z_scale > -5)
		image->z_scale -= 0.5;
}

void	rotate_z_pos(t_data *image)
{
	double	x;
	double	y;

	x = image->vector_x[0];
	y = image->vector_y[0];
	image->vector_x[0] = image->vector_x[0] * cos(ANG_1 * 5) - image->vector_x[1] * sin(ANG_1 * 5);
	image->vector_x[1] = x * sin(ANG_1 * 5) + image->vector_x[1] * cos(ANG_1 * 5);
	image->vector_y[0] = image->vector_y[0] * cos(ANG_1 * 5) - image->vector_y[1] * sin(ANG_1 * 5);
	image->vector_y[1] = y * sin(ANG_1 * 5) + image->vector_y[1] * cos(ANG_1 * 5);
	// image->angle_x = (image->angle_x + 5) % 360;
	// image->angle_y = (image->angle_y + 5) % 360;
	// image->vector_x[0] = cos(getRadian(image->angle_x));
	// image->vector_x[1] = sin(getRadian(image->angle_x));
	// image->vector_y[0] = cos(getRadian(image->angle_y));
	// image->vector_y[1] = sin(getRadian(image->angle_y));
	// image->angle_z = (image->angle_z + 5) % 360;
	// image->vector_x[0] = image->vector_x[0] * cos(getRadian((image->angle_z + 90) % 360)) - image->vector_x[1] * sin(getRadian((image->angle_z + 90) % 360));
	// image->vector_x[1] = image->vector_x[0] * sin(getRadian((image->angle_z + 90) % 360)) + image->vector_x[1] * cos(getRadian((image->angle_z + 90) % 360));
	// image->vector_y[0] = image->vector_y[0] * cos(getRadian((image->angle_z + 90) % 360)) - image->vector_y[1] * sin(getRadian((image->angle_z + 90) % 360));
	// image->vector_y[1] = image->vector_y[0] * sin(getRadian((image->angle_z + 90) % 360)) + image->vector_y[1] * cos(getRadian((image->angle_z + 90) % 360));
}

void	rotate_z_neg(t_data *image)
{	
	double	x;
	double	y;

	x = image->vector_x[0];
	y = image->vector_y[0];
	image->vector_x[0] = image->vector_x[0] * cos(-ANG_1 * 5) - image->vector_x[1] * sin(-ANG_1 * 5);
	image->vector_x[1] = x * sin(-ANG_1 * 5) + image->vector_x[1] * cos(-ANG_1 * 5);
	image->vector_y[0] = image->vector_y[0] * cos(-ANG_1 * 5) - image->vector_y[1] * sin(-ANG_1 * 5);
	image->vector_y[1] = y * sin(-ANG_1 * 5) + image->vector_y[1] * cos(-ANG_1 * 5);
	// image->angle_x = (image->angle_x + 355) % 360;
	// image->angle_y = (image->angle_y + 355) % 360;
	// image->vector_x[0] = cos(getRadian(image->angle_x));
	// image->vector_x[1] = sin(getRadian(image->angle_x));
	// image->vector_y[0] = cos(getRadian(image->angle_y));
	// image->vector_y[1] = sin(getRadian(image->angle_y));
	// image->angle_z = (image->angle_z + 355) % 360;
	// image->vector_x[0] = -image->vector_x[0] * cos(getRadian((image->angle_z + 90) % 360)) + image->vector_x[1] * sin(getRadian((image->angle_z + 90) % 360));
	// image->vector_x[1] = -image->vector_x[0] * sin(getRadian((image->angle_z + 90) % 360)) - image->vector_x[1] * cos(getRadian((image->angle_z + 90) % 360));
	// image->vector_y[0] = -image->vector_y[0] * cos(getRadian((image->angle_z + 90) % 360)) + image->vector_y[1] * sin(getRadian((image->angle_z + 90) % 360));
	// image->vector_y[1] = -image->vector_y[0] * sin(getRadian((image->angle_z + 90) % 360)) - image->vector_y[1] * cos(getRadian((image->angle_z + 90) % 360));
}

void	rotate_x_pos(t_data *image)
{
	double	y;
	double	z;
	double	adjust;
	double	product;

	y = image->vector_y[0];
	z = image->vector_z[0];
	product = image->vector_x[0] * image->vector_y[0] + image->vector_x[1] * image->vector_y[1];
	if (product > -sqrt(2)/2 && product < sqrt(2)/2)
		adjust = -2.5;
	else
		adjust = 2.5;
	image->vector_z[0] = image->vector_z[0] * cos(ANG_1 * (5 + adjust)) - image->vector_z[1] * sin(ANG_1 * (5 + adjust));
	image->vector_z[1] = z * sin(ANG_1 * (5 + adjust)) + image->vector_z[1] * cos(ANG_1 * (5 + adjust));
	image->vector_y[0] = image->vector_y[0] * cos(ANG_1 * 5) - image->vector_y[1] * sin(ANG_1 * 5);
	image->vector_y[1] = y * sin(ANG_1 * 5) + image->vector_y[1] * cos(ANG_1 * 5);
}

void	rotate_x_neg(t_data *image)
{
	double	y;
	double	z;
	double	adjust;
	double	product;

	y = image->vector_y[0];
	z = image->vector_z[0];
	product = image->vector_x[0] * image->vector_y[0] + image->vector_x[1] * image->vector_y[1];
	if (product > -sqrt(2)/2 && product < sqrt(2)/2)
		adjust = 2.5;
	else
		adjust = -2.5;
	image->vector_z[0] = image->vector_z[0] * cos(-ANG_1 * (5 + adjust)) - image->vector_z[1] * sin(-ANG_1 * (5 + adjust));
	image->vector_z[1] = z * sin(-ANG_1 * (5 + adjust)) + image->vector_z[1] * cos(-ANG_1 * (5 + adjust));
	image->vector_y[0] = image->vector_y[0] * cos(-ANG_1 * 5) - image->vector_y[1] * sin(-ANG_1 * 5);
	image->vector_y[1] = y * sin(-ANG_1 * 5) + image->vector_y[1] * cos(-ANG_1 * 5);
}

void	rotate_y_pos(t_data *image)
{
	double	x;
	double	z;
	double	adjust;
	double	product;

	x = image->vector_x[0];
	z = image->vector_z[0];
	product = image->vector_x[0] * image->vector_y[0] + image->vector_x[1] * image->vector_y[1];
	if (product > -sqrt(2)/2 && product < sqrt(2)/2)
		adjust = 2.5;
	else
		adjust = -2.5;
	image->vector_x[0] = image->vector_x[0] * cos(ANG_1 * 5) - image->vector_x[1] * sin(ANG_1 * 5);
	image->vector_x[1] = x * sin(ANG_1 * 5) + image->vector_x[1] * cos(ANG_1 * 5);
	image->vector_z[0] = image->vector_z[0] * cos(ANG_1 * (5 + adjust)) - image->vector_z[1] * sin(ANG_1 * (5 + adjust));
	image->vector_z[1] = z * sin(ANG_1 * (5 + adjust)) + image->vector_z[1] * cos(ANG_1 * (5 + adjust));
}

void	rotate_y_neg(t_data *image)
{
	double	x;
	double	z;
	double	adjust;
	double	product;

	x = image->vector_x[0];
	z = image->vector_z[0];
	product = image->vector_x[0] * image->vector_y[0] + image->vector_x[1] * image->vector_y[1];
	if (product > -sqrt(2)/2 && product < sqrt(2)/2)
		adjust = 2.5;
	else
		adjust = -2.5;
	image->vector_x[0] = image->vector_x[0] * cos(-ANG_1 * 5) - image->vector_x[1] * sin(-ANG_1 * 5);
	image->vector_x[1] = x * sin(-ANG_1 * 5) + image->vector_x[1] * cos(-ANG_1 * 5);
	image->vector_z[0] = image->vector_z[0] * cos(-ANG_1 * (5 + adjust)) - image->vector_z[1] * sin(-ANG_1 * (5 + adjust));
	image->vector_z[1] = z * sin(-ANG_1 * (5 + adjust)) + image->vector_z[1] * cos(-ANG_1 * (5 + adjust));
}

void	set_vector(t_data *image)
{
	image->vector_x[0] = cos(getRadian(30));
	image->vector_x[1] = sin(getRadian(30));
	image->vector_y[0] = cos(getRadian(150));
	image->vector_y[1] = sin(getRadian(150));
	image->vector_z[0] = cos(getRadian(270));
	image->vector_z[1] = sin(getRadian(270));
	image->angle_x = 30;
	image->angle_y = 150;
	image->angle_z = 270;
}

void	init_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "FDF");
	vars->image.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->image.addr = mlx_get_data_addr(vars->image.img, &vars->image.bits_per_pixel, \
						&vars->image.line_length, &vars->image.endian);
	calculate_size(vars);
	vars->image.x = WIDTH / 2 + vars->image.size * (vars->image.row - vars->image.col) * (sqrt(3) / 4);
	vars->image.y = HEIGHT / 2 - vars->image.size * (vars->image.col + vars->image.row) / 4;
	int	idx = 0;
	int	t;

	for (int i = 0; i < vars->image.row; i++)
	{
		double y = vars->image.y + i * 0.5 * vars->image.size;
		for (int j = 0; j < vars->image.col; j++)
		{
			int k = vars->image.read[idx++];
			if (k != 0)
			{
				if (k < 0)
					t = (HEIGHT - y - vars->image.size) / abs(k);
				else
					t = y / k;
				if (vars->image.z_size == 0)
					vars->image.z_size = t;
				else
					vars->image.z_size = ft_min(vars->image.z_size, t);
			}
			y += vars->image.size * 0.5;
		}
	}
	if (vars->image.z_size > 30)
		vars->image.z_size = 30;
	else if (vars->image.z_size > 10)
		vars->image.z_size *= 0.7;
	vars->image.default_z_size = vars->image.z_size;
	set_vector(&vars->image);
}

void	connect_points(t_vars *vars, double x, double y, double t_x, double t_y)
{
	double	v_x;
	double	v_y;
	double	size;

	size = sqrt((t_x - x) * (t_x - x) + (t_y - y) * (t_y - y));
	if (size == 0)
		return ;
	v_x = (t_x - x) / size;
	v_y = (t_y - y) / size;
	for (int i = 0; i < (int)size; i++)
	{
		my_mlx_pixel_put(&vars->image, x, y, GY);
		x += v_x;
		y += v_y;
	}
}

void	draw(t_vars *vars)
{
	int	size;

	size = vars->image.size;
	int idx = 0;
	for (int i = 0; i < vars->image.row; i++)
	{
		double x = vars->image.x + size * vars->image.vector_y[0] * i;
		double y = vars->image.y + size * vars->image.vector_y[1] * i;
		for (int j = 0; j < vars->image.col; j++)
		{
			double	v1 = vars->image.read[idx] * vars->image.z_scale;
			double	v2;
			if (j < vars->image.col - 1)
			{
				v2 = vars->image.read[idx + 1] * vars->image.z_scale;
				connect_points(vars, x + vars->image.z_size * v1 * vars->image.vector_z[0], y + vars->image.z_size * v1 * vars->image.vector_z[1],\
								x + size * vars->image.vector_x[0] + vars->image.z_size * v2 * vars->image.vector_z[0], y + size * vars->image.vector_x[1] + vars->image.z_size * v2 * vars->image.vector_z[1]);
			}
			if (i < vars->image.row - 1)
			{
				v2 = vars->image.read[idx + vars->image.col] * vars->image.z_scale;
				connect_points(vars, x + vars->image.z_size * v1 * vars->image.vector_z[0], y + vars->image.z_size * v1 * vars->image.vector_z[1],\
							x + size * vars->image.vector_y[0] + vars->image.z_size * v2 * vars->image.vector_z[0], y + size * vars->image.vector_y[1] + vars->image.z_size * v2 * vars->image.vector_z[1]);
			}
			x += size * vars->image.vector_x[0];
			y += size * vars->image.vector_x[1];
			idx++;
		}
	}
}

// 회전을 어떻게 구현??
// 

void	reset_img(t_vars *vars)
{
	vars->image.x = WIDTH / 2 + vars->image.size * (vars->image.row - vars->image.col) * (sqrt(3) / 4);
	vars->image.y = HEIGHT / 2 - vars->image.size * (vars->image.col + vars->image.row) / 4;
	reset_canvas(&vars->image);
	// mlx_destroy_image(vars->mlx, vars->image.img);
	// vars->image.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	// vars->image.addr = mlx_get_data_addr(vars->image.img, &vars->image.bits_per_pixel, \
					&vars->image.line_length, &vars->image.endian);
	draw(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, 0, 0);
}

void	zoom_io(t_vars *vars, int keycode)
{
	int		size;
	char	*dst;

	size = vars->image.size;
	if (keycode == 4)
	{
		vars->image.size = ft_min(vars->image.size * 1.3, vars->image.range_max);
		if (vars->image.size != vars->image.range_max && vars->image.size == size)
			vars->image.size *= 2;
	}
	else if (keycode == 5)
		vars->image.size = ft_max(vars->image.size * 0.7, vars->image.range_min);
	if (size == vars->image.size)
		return ;
	if (keycode == 4)
	{
		if (vars->image.z_size >= 5)
			vars->image.z_size *= 1.3;
		else
			vars->image.z_size++;
	}
	else
	{
		if (vars->image.z_size >= 5)
			vars->image.z_size *= 0.7;
		else if (vars->image.z_size > 1)
			vars->image.z_size--;
	}
	reset_img(vars);
}

int	mouse_hook(int keycode, int x, int y, t_vars *vars)
{
	if (keycode == 4 || keycode == 5)
		zoom_io(vars, keycode);
	return (0);
}

void	orthogonal(t_vars *vars)
{
	vars->image.vector_x[0] = cos(getRadian(30));
	vars->image.vector_x[1] = sin(getRadian(30));
	vars->image.vector_y[0] = cos(getRadian(120));
	vars->image.vector_y[1] = sin(getRadian(120));
	vars->image.vector_z[0] = cos(getRadian(270));
	vars->image.vector_z[1] = sin(getRadian(270));
	reset_img(vars);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	init_data(argc, argv, &vars);
	init_mlx(&vars);
	draw(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.image.img, 0, 0);
	mlx_hook(vars.win, 17, 1L<<0, close_mlx, &vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_loop(vars.mlx);
	free(vars.image.read);
	mlx_destroy_image(vars.mlx, vars.image.img);
	mlx_destroy_window(vars.mlx, vars.win);
	mlx_destroy_display(vars.mlx);
	free(vars.mlx);
	return 0;
}

// cc main.c -Lminilibx-linux -lmlx -L./minilibx-linux -Iminilibx-linux -lXext -lX11 -lm -lz
// %o: %.c
//		$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@
// $(NAME): $(OBJ)
//		$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)