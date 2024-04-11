#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line_bonus.h"

int	main(int argc, char **argv)
{
	char	*s;
	char	*read;
	int 	fd;
	char	**sp;
	int		row;
	int		total;

	s = 0;
	row = 0;
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
	{
		printf("Nothing turned in.. Exiting program.\n");
		exit(0);
	}
	while (1)
	{
		read = get_next_line(fd);
		if (!read)
			break ;
		read[ft_strlen(read) - 1] = ' ';
		s = ft_strjoin(s, read);
		row++;
		free(read);
	}
	// printf("s: \n%s", s);
	sp = ft_split(s, ' ');
	total = 0;
	// printf("row: %d\n", row);
	while (sp[total])
		printf("%s ", sp[total++]);
	printf("row, col, total: %d, %d, %d\n", row, total / row, total);
	return (0);
}

// -lm