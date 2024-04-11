# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksuh <ksuh@student.42gyeongsan.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 22:16:25 by ksuh              #+#    #+#              #
#    Updated: 2024/04/09 22:16:26 by ksuh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksuh <ksuh@student.42gyeongsan.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 17:37:11 by ksuh              #+#    #+#              #
#    Updated: 2024/04/07 15:09:43 by ksuh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_BASIC = 

SRCS_BONUS = 

OBJS_BASIC = $(SRCS_BASIC:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
NAME_BASIC = 
NAME_BONUS = 

ifndef bonus
OBJS = $(OBJS_BASIC)
NAME = $(NAME_BASIC)
else
OBJS = $(OBJS_BONUS)
NAME = $(NAME_BONUS)
endif

all : $(NAME) 

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c 
	$(CC) $(CFLAGS) -c $^

clean :	
	rm -rf $(OBJS_BASIC) 
	rm -rf $(OBJS_BONUS)

fclean : clean
	rm -rf $(NAME_BASIC)
	rm -rf $(NAME_BONUS)

re : fclean all

bonus :
	make bonus=1 all

.PHONY : all clean fclean re bonus

