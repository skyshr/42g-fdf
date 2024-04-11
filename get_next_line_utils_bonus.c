/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:45:47 by ksuh              #+#    #+#             */
/*   Updated: 2024/03/18 13:09:44 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	reset(char *backup, size_t readbytes)
{
	size_t	idx;
	size_t	copyidx;

	if (readbytes == 0)
		return ;
	idx = 0;
	copyidx = readbytes;
	while (copyidx < BUFFER_SIZE && backup[copyidx])
		backup[idx++] = backup[copyidx++];
	while (idx < BUFFER_SIZE && backup[idx])
		backup[idx++] = '\0';
}

size_t	get_read_bytes(char *backup, int *is_end)
{
	size_t	readbytes;

	readbytes = 0;
	while (readbytes < BUFFER_SIZE)
	{
		if (backup[readbytes] == '\n')
		{
			(*is_end) = 2;
			return (readbytes + 1);
		}
		else if (backup[readbytes] == '\0')
		{
			(*is_end) = 1;
			return (readbytes);
		}
		readbytes++;
	}
	return (readbytes);
}

char	*read_buffer(int fd, char *backup, char *buffer, int *is_end)
{
	size_t	readbytes;

	readbytes = get_read_bytes(backup, is_end);
	buffer = strjoin(buffer, backup, readbytes);
	if (buffer == NULL)
	{
		(*is_end) = 1;
		return (0);
	}
	reset(backup, readbytes);
	if ((*is_end) == 1)
	{
		read(fd, backup, BUFFER_SIZE);
		if (backup[0] != '\0')
			(*is_end) = 0;
	}
	return (buffer);
}

size_t	ft_strlen1(char *str)
{
	size_t	size;

	if (!str)
		return (0);
	size = 0;
	while (str[size])
		size++;
	return (size);
}

char	*strjoin(char *src1, char *src2, size_t bytesize)
{
	char	*dest;
	size_t	destidx;
	size_t	srcidx;

	dest = (char *)malloc((ft_strlen1(src1) + bytesize + 1) * sizeof(char));
	if (!dest)
		return (0);
	destidx = 0;
	srcidx = 0;
	while (src1 && src1[destidx])
	{
		dest[destidx] = src1[destidx];
		destidx++;
	}
	while (srcidx < bytesize)
		dest[destidx++] = src2[srcidx++];
	dest[destidx] = '\0';
	if (src1)
		free(src1);
	return (dest);
}
