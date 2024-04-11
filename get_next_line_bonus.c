/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:45:47 by ksuh              #+#    #+#             */
/*   Updated: 2024/03/23 13:05:12 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	backup[MAX_SIZE][BUFFER_SIZE];
	char		*buffer;
	int			is_end;

	is_end = 0;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (backup[fd][0] == '\0' && read(fd, backup[fd], BUFFER_SIZE) <= 0)
		return (NULL);
	buffer = NULL;
	while (!is_end)
		buffer = read_buffer(fd, backup[fd], buffer, &is_end);
	return (buffer);
}
