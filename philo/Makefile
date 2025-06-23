# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angellop <angellop@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/20 11:17:45 by angellop          #+#    #+#              #
#    Updated: 2025/06/15 14:13:30 by angellop         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDES	= -Iincludes

NAME		= philo

CC			= cc
CFLAGS		= -Wall -Wextra -Werror $(INCLUDES)

SRCS		=	main.c \
				philosophers.c \
				utils.c \
				init.c \
				monitor.c \
				actions.c
				
OBJS		= $(SRCS:.c=.o)

TEST_SRCS	= test/test_philosophers.c test/test_init.c test/test_simulation.c test/test_philo_routine.c
TESTS		= test_philosophers test_init test_simulation test_philo_routine
TEST_OBJS	= $(TEST_SRCS:.c=.o)
COMMON_OBJS = philosophers.o utils.o init.o actions.o monitor.o

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

test/%: test/%.o $(COMMON_OBJS) includes/minunit.h
	$(CC) $(CFLAGS) $^ -o $@ -lpthread

$(TESTS):
	$(MAKE) test/$@

test: $(TESTS)
	@for t in $(TESTS); do ./test/$$t; done

clean:
	rm -f $(OBJS) $(TEST_OBJS) test/*.o test/* $(TESTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test
