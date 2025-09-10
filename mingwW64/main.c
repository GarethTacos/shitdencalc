#include <stdio.h>
#include <gmp.h>

int main() {
    // Declare GMP integers
    mpz_t a, b, sum;

    // Initialize the variables
    mpz_init(a);
    mpz_init(b);
    mpz_init(sum);

    // Set values for a and b
    mpz_set_str(a, "12", 10);
    mpz_set_str(b, "24", 10);

    // Perform addition
    mpz_add(sum, a, b);

    // Print the result
    gmp_printf("Sum: %Zd\n", sum);

    // Clear memory
    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(sum);

    return 0;
}

