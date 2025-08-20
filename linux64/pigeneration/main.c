#include <stdio.h>
#include <mpfr.h>

int main(void) {
    // set precision high enough to capture the input and true pi
    mpfr_prec_t prec = 512; // ~150 decimal digits
    mpfr_t input_pi, true_pi, diff;
    mpfr_inits2(prec, input_pi, true_pi, diff, NULL);

    // set true pi
    mpfr_const_pi(true_pi, MPFR_RNDN);

    // parse the provided string
    const char *s = "3.14159265358979395560412584131881885696202516555786132812500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    if (mpfr_set_str(input_pi, s, 10, MPFR_RNDN) != 0) {
        fprintf(stderr, "Failed to parse input string.\n");
        return 1;
    }

    // diff = input_pi - true_pi
    mpfr_sub(diff, input_pi, true_pi, MPFR_RNDN);

    // print both and the error
    mpfr_printf("Provided value  = %.200Rf\n", input_pi);
    mpfr_printf("True pi         = %.200Rf\n", true_pi);
    mpfr_printf("Difference (in decimal) = %.200Re\n", diff); // scientific notation
    mpfr_clears(input_pi, true_pi, diff, NULL);
    return 0;
}

