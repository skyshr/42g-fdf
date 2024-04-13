#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
// #include "get_next_line_bonus.h"
#include "fdf.h"

int	main(int argc, char **argv)
{
	char	*s;
	char	*read;
	int 	fd;
	char	**sp;
	int		row;
	int		col;
	int		total;

	s = 0;
	row = 0;
	if (argc != 2)
	{
		printf("Nothing turned in.. Exiting program.\n");
		exit(0);
	}
	fd = open(argv[1], O_RDONLY);
	while (1)
	{
		read = get_next_line(fd);
		if (!read)
			break ;
		if (read[ft_strlen(read) - 1] == '\n')
			read[ft_strlen(read) - 1] = ' ';
		s = ft_strjoin(s, read);
		row++;
		free(read);
	}
	// printf("s: \n%s", s);
	close(fd);
	sp = ft_split(s, ' ');
	total = 0;
	while (sp[total])
		total++;
	col = total / row;
	printf("\nrow, col, total: %d, %d, %d\n", row, col, total);
	double l1 = 2 * (row - WIDTH / sqrt(3)) / (col - row);
	double l2 = 2 * (WIDTH / sqrt(3) - col) / (col - row);
	double l3 = 2 * HEIGHT / (row + col);
	double l4 = 2 * (row + col - HEIGHT) / (row + col);
	printf("l1, l2, l3, l4: %lf, %lf, %lf, %lf\n", l1, l2, l3, l4);
	return (0);
}

// -lm
