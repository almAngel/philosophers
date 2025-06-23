#include "../includes/philo.h"
#include "../includes/minunit.h"

int tests_run = 0;

// Test válido: solo argumentos requeridos
MU_TEST(test_valid_required_args) {
	char *ok[] = {"./philo", "5", "800", "200", "200"};
	mu_assert("Valid required args failed", validate_args(5, ok) == 1);
	return 0;
}

// Test válido: argumentos requeridos + opcional num_meals
MU_TEST(test_valid_with_optional) {
	char *ok[] = {"./philo", "5", "800", "200", "200", "7"};
	mu_assert("Valid with optional arg failed", validate_args(6, ok) == 1);
	return 0;
}

// Test inválido: menos de los argumentos requeridos
MU_TEST(test_too_few_args) {
	char *fail[] = {"./philo", "5", "800", "200"};
	mu_assert("Too few args not detected", validate_args(4, fail) == 0);
	return 0;
}

// Test inválido: demasiados argumentos
MU_TEST(test_too_many_args) {
	char *fail[] = {"./philo", "5", "800", "200", "200", "7", "extra"};
	mu_assert("Too many args not detected", validate_args(7, fail) == 0);
	return 0;
}

// Test inválido: argumento requerido no positivo
MU_TEST(test_zero_philosophers) {
	char *fail[] = {"./philo", "0", "800", "200", "200"};
	mu_assert("Zero philosophers not detected", validate_args(5, fail) == 0);
	return 0;
}

// Test inválido: argumento requerido negativo
MU_TEST(test_negative_time_to_die) {
	char *fail[] = {"./philo", "-1", "800", "200", "200"};
	mu_assert("Negative time_to_die not detected", validate_args(5, fail) == 0);
	return 0;
}

// Test inválido: argumento requerido cero
MU_TEST(test_zero_time_to_eat) {
	char *fail[] = {"./philo", "5", "800", "0", "200"};
	mu_assert("Zero time_to_eat not detected", validate_args(5, fail) == 0);
	return 0;
}

// Test inválido: opcional negativo
MU_TEST(test_negative_num_meals) {
	char *fail[] = {"./philo", "5", "800", "200", "200", "-3"};
	mu_assert("Negative num_meals not detected", validate_args(6, fail) == 0);
	return 0;
}

// Test inválido: argumento no numérico
MU_TEST(test_non_numeric_arg) {
	char *fail[] = {"./philo", "cinco", "800", "200", "200"};
	mu_assert("Non-numeric arg not detected", validate_args(5, fail) == 0);
	return 0;
}

// Test inválido: argumento con espacios
MU_TEST(test_arg_with_spaces) {
	char *fail[] = {"./philo", " 5", "800", "200", "200"};
	mu_assert("Arg with leading space not detected", validate_args(5, fail) == 0);
	return 0;
}

// Test válido: argumento con signo más (si tu ft_atoi lo permite)
MU_TEST(test_arg_with_plus) {
	char *ok[] = {"./philo", "+5", "800", "200", "200"};
	mu_assert("Arg with plus sign failed", validate_args(5, ok) == 1);
	return 0;
}

// Test inválido: argumento overflow
MU_TEST(test_arg_overflow) {
	char *fail[] = {"./philo", "999999999999999999999", "800", "200", "200"};
	mu_assert("Overflow arg not detected", validate_args(5, fail) == 0);
	return 0;
}

// Test inválido: argumento vacío
MU_TEST(test_empty_arg) {
	char *fail[] = {"./philo", "", "800", "200", "200"};
	mu_assert("Empty arg not detected", validate_args(5, fail) == 0);
	return 0;
}

// Test inválido: argumento con caracteres especiales
MU_TEST(test_arg_special_char) {
	char *fail[] = {"./philo", "5!", "800", "200", "200"};
	mu_assert("Special char arg not detected", validate_args(5, fail) == 0);
	return 0;
}

// Test inválido: argumento con punto decimal
MU_TEST(test_arg_decimal) {
	char *fail[] = {"./philo", "8.0", "800", "200", "200"};
	mu_assert("Decimal arg not detected", validate_args(5, fail) == 0);
	return 0;
}

// Test inválido: argumento con notación científica
MU_TEST(test_arg_scientific) {
	char *fail[] = {"./philo", "2e3", "800", "200", "200"};
	mu_assert("Scientific arg not detected", validate_args(5, fail) == 0);
	return 0;
}

// Test inválido: doble signo
MU_TEST(test_arg_double_sign) {
	char *fail[] = {"./philo", "--5", "800", "200", "200"};
	mu_assert("Double sign arg not detected", validate_args(5, fail) == 0);
	return 0;
}

// Test inválido: solo signo
MU_TEST(test_arg_only_sign) {
	char *fail[] = {"./philo", "+", "800", "200", "200"};
	mu_assert("Only sign arg not detected", validate_args(5, fail) == 0);
	return 0;
}

// Test válido: ceros a la izquierda
MU_TEST(test_arg_leading_zeros) {
	char *ok[] = {"./philo", "005", "800", "200", "200"};
	mu_assert("Leading zeros arg failed", validate_args(5, ok) == 1);
	return 0;
}

// Test inválido: espacios al final
MU_TEST(test_arg_trailing_space) {
	char *fail[] = {"./philo", "5 ", "800", "200", "200"};
	mu_assert("Trailing space arg not detected", validate_args(5, fail) == 0);
	return 0;
}

MU_TEST_SUITE(test_suite) {
	MU_RUN_TEST(test_valid_required_args);
	MU_RUN_TEST(test_valid_with_optional);
	MU_RUN_TEST(test_too_few_args);
	MU_RUN_TEST(test_too_many_args);
	MU_RUN_TEST(test_zero_philosophers);
	MU_RUN_TEST(test_negative_time_to_die);
	MU_RUN_TEST(test_zero_time_to_eat);
	MU_RUN_TEST(test_negative_num_meals);
	MU_RUN_TEST(test_non_numeric_arg);
	MU_RUN_TEST(test_arg_with_spaces);
	MU_RUN_TEST(test_arg_with_plus);
	MU_RUN_TEST(test_arg_overflow);
	MU_RUN_TEST(test_empty_arg);
	MU_RUN_TEST(test_arg_special_char);
	MU_RUN_TEST(test_arg_decimal);
	MU_RUN_TEST(test_arg_scientific);
	MU_RUN_TEST(test_arg_double_sign);
	MU_RUN_TEST(test_arg_only_sign);
	MU_RUN_TEST(test_arg_leading_zeros);
	MU_RUN_TEST(test_arg_trailing_space);
}

int main(void) {
	MU_RUN_SUITE(test_suite);
	MU_REPORT();
	return 0;
}
