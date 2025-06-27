# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angellop <angellop@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/20 11:17:45 by angellop          #+#    #+#              #
#    Updated: 2025/06/27 12:13:04 by angellop         ###   ########.fr        #
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
				actions.c \
				fork_utils.c \
				philo_routine.c
				
OBJS		= $(SRCS:.c=.o)

TEST_SRCS	= test/test_validate_args.c test/test_init.c test/test_start_simulation.c test/test_simulation_stress.c test/test_simulation_detailed.c
TESTS		= test_validate_args test_init test_start_simulation test_simulation_stress test_simulation_detailed
TEST_OBJS	= $(TEST_SRCS:.c=.o)
COMMON_OBJS = philosophers.o utils.o init.o actions.o monitor.o fork_utils.o philo_routine.o

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

test/%.o: test/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

test/%: test/%.o $(COMMON_OBJS) includes/minunit.h
	@$(CC) $(CFLAGS) $< $(COMMON_OBJS) -o $@ -lpthread

$(TESTS):
	@$(MAKE) test/$@

test: $(TESTS)
	@for t in $(TESTS); do ./test/$$t; done

functional_tests:
	@echo "Running all functional tests..."
	@for t in functional_tests/*.sh; do \
		echo "$$t"; \
		bash "$$t" || exit 1; \
	done

valgrind_tests:
	@echo "Running valgrind memory tests..."
	@bash test/test_valgrind.sh

clean:
	@rm -f $(OBJS) $(TEST_OBJS) test/*.o test/$(TESTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test functional_tests valgrind_tests
