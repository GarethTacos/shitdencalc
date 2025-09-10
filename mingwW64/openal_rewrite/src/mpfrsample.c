#include <stdio.h>
#include <gmp.h>  // GMP header
#include <mpfr.h> // MPFR header

int main() {
    // Variable Declarations
    mpfr_t result;
    mpfr_t user_input;
    
    // A buffer to hold the user's input as a string
    char input_string[1024];

    // Set a precision of 100 bits for our numbers.
    unsigned long int precision_bits = 100;
    
    // Initialize the MPFR variables with the specified precision
    mpfr_init2(result, precision_bits);
    mpfr_init2(user_input, precision_bits);
    
    // ----- MODIFICATION FOR USER INPUT -----
    // 1. Prompt the user to enter a number
    printf("Enter a number to calculate the sine of: ");

    // 2. Read the user's input as a string
    scanf("%s", input_string);

    // 3. Convert the string to the MPFR variable 'user_input'
    // The last argument (10) specifies the base (decimal).
    if (mpfr_set_str(user_input, input_string, 10, MPFR_RNDN) != 0) {
        printf("Error: Invalid number format. Please enter a valid number.\n");
        return 1;
    }

    // ---------------------------------------
    
    // Calculate the sine of the user's number and store it in result.
    // The function uses the precision set during initialization.
    mpfr_sin(result, user_input, MPFR_RNDN);
    
    // Print the result to the console.
    printf("The value of sine with %lu bits of precision is: \n", precision_bits);
    mpfr_out_str(stdout, 10, 60, result, MPFR_RNDN);
    printf("\n");

    // Clean up the memory used by the variables
    mpfr_clear(result);
    mpfr_clear(user_input);
    mpfr_free_cache();

    return 0;
}
