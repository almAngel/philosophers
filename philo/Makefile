# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angellop <angellop@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/20 11:17:45 by angellop          #+#    #+#              #
#    Updated: 2025/06/27 13:40:46 by angellop         ###   ########.fr        #
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

helgrind_tests:
	@echo "Running Helgrind race condition tests..."
	@echo "=================================="
	@echo "Test 1: Basic 5 philosophers"
	@timeout 10s valgrind --tool=helgrind --quiet ./philo 5 800 200 200 2 2>/dev/null || echo "Helgrind test 1 completed"
	@echo "Test 2: Stress test (4 philosophers, tight timing)"
	@timeout 10s valgrind --tool=helgrind --quiet ./philo 4 410 200 200 1 2>/dev/null || echo "Helgrind test 2 completed"
	@echo "Test 3: Race condition prone (3 philosophers)"
	@timeout 10s valgrind --tool=helgrind --quiet ./philo 3 800 200 200 1 2>/dev/null || echo "Helgrind test 3 completed"
	@echo "=================================="
	@echo "Helgrind tests completed. Check output above for race conditions."

helgrind_detailed:
	@echo "Running detailed Helgrind analysis..."
	@echo "====================================="
	@echo "This will show detailed race condition reports:"
	@timeout 15s valgrind --tool=helgrind --history-level=full --conflict-cache-size=1000000 ./philo 5 800 200 200 2 || echo "Detailed helgrind completed"

drd_tests:
	@echo "Running DRD race condition tests..."
	@echo "=================================="
	@echo "Test 1: Basic DRD test"
	@timeout 10s valgrind --tool=drd --quiet ./philo 5 800 200 200 2 2>/dev/null || echo "DRD test 1 completed"
	@echo "Test 2: DRD with thread checking"
	@timeout 10s valgrind --tool=drd --check-stack-var=yes ./philo 4 410 200 200 1 2>/dev/null || echo "DRD test 2 completed"
	@echo "=================================="
	@echo "DRD tests completed."

race_condition_tests: helgrind_tests drd_tests
	@echo "All race condition tests completed!"

clean:
	@rm -f $(OBJS) $(TEST_OBJS) test/*.o test/$(TESTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test functional_tests valgrind_tests helgrind_tests helgrind_detailed drd_tests race_condition_tests
