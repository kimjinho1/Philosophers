# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinhokim <jinhokim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/15 20:57:16 by jinhokim          #+#    #+#              #
#    Updated: 2022/10/17 08:15:18 by jinhokim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS = main.c \
		utils.c \
		init.c \
		philo.c \

CC = cc
FLAGS = -Wall -Wextra -Werror -g -fsanitize=thread
#FLAGS = -Wall -Wextra -Werror -g -fsanitize=address
#FLAGS = -Wall -Wextra -Werror
RM = rm -rf

OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

re: fclean all

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

.PHONY: all clean fclean re
