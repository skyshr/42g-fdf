/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuh <ksuh@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:45:43 by ksuh              #+#    #+#             */
/*   Updated: 2024/03/18 13:10:15 by ksuh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

# define MAX_SIZE 1025

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

size_t	get_read_bytes(char *lst, int *is_end);
char	*read_buffer(int fd, char *lst, char *buffer, int *is_end);
char	*strjoin(char *src1, char *src2, size_t bytesize);
size_t	ft_strlen1(char *str);
char	*get_next_line(int fd);
void	reset(char *lst, size_t readbytes);

#endif
