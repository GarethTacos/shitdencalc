#include <stdio.h>
#include "misc.h"
#include <string.h>
#include <math.h>
#include <gmp.h>
#include "audio.h"
#include "dr_flac.h"
#include <pthread.h>
#include <stdlib.h>
#define PI 3.14159265358979323846
// current state of project
// cpp port cancelled because cmake is disgusting
// now working on json parsing and updating
// fhs soln possibly needed
void tinput(char* buffer, size_t size){
	if (fgets(buffer, size, stdin) != NULL){
		size_t len = strlen(buffer);
		// newline removal
		if (len > 0 && buffer[len - 1] == '\n'){
			buffer[len - 1] = '\0';
		}
	} else {
		// erro handling (input err or EOF)
		buffer[0] = '\0';
	}
}
void opselect(){
	while (2<5){
	printf("select an operation for shitden to calculate or type 'help' for a list ");
	char skibidi[10];
	tinput(skibidi,sizeof(skibidi));
	//printf("You entered: %s\n", skibidi);
	// add func
	if (strcmp(skibidi, "+") == 0){
		mpz_t a, b, result;
	 	// init
		mpz_init(a);
		mpz_init(b);
		mpz_init(result);
		//set
		char astr[1000];
		char bstr[1000];
		printf("enter first integer: ");
		tinput(astr,sizeof(astr));
		printf("enter second integer: ");
		tinput(bstr,sizeof(bstr));
		if (mpz_set_str(a, astr, 10) == -1) {
			// Error handling if conversion fails
			printf("error: Invalid number format.\n");
		} 
		if (mpz_set_str(b, bstr, 10) == -1) {
			// Error handling if conversion fails
			printf("error: Invalid number format.\n");
		}		
		//add
		mpz_add(result,a,b);
		//free
		gmp_printf("the sum of %Zd and %Zd is: %Zd\n", a,b,result);
		mpz_clear(a);
		mpz_clear(b);
		mpz_clear(result);
	}
	if (strcmp(skibidi, "-") == 0){
		mpz_t a, b, result;
	 	// init
		mpz_init(a);
		mpz_init(b);
		mpz_init(result);
		//set
		char astr[1000];
		char bstr[1000];
		printf("enter first integer: ");
		tinput(astr,sizeof(astr));
		printf("enter second integer: ");
		tinput(bstr,sizeof(bstr));
		if (mpz_set_str(a, astr, 10) == -1) {
			// Error handling if conversion fails
			printf("error: Invalid number format.\n");
		} 
		if (mpz_set_str(b, bstr, 10) == -1) {
			// Error handling if conversion fails
			printf("error: Invalid number format.\n");
		}		
		//sub
		mpz_sub(result,a,b);
		//free
		gmp_printf("the difference of %Zd and %Zd is: %Zd\n", a,b,result);
		mpz_clear(a);
		mpz_clear(b);
		mpz_clear(result);
	}
	if (strcmp(skibidi, "/") == 0){
		mpf_t a, b, result;
	 	// init
		mpf_init(a);
		mpf_init(b);
		mpf_init(result);
		//set
		char astr[1000];
		char bstr[1000];
		printf("enter first float: ");
		tinput(astr,sizeof(astr));
		printf("enter second float: ");
		tinput(bstr,sizeof(bstr));
		if (mpf_set_str(a, astr, 10) == -1) {
			// Error handling if conversion fails
			printf("error: Invalid number format.\n");
		} 
		if (mpf_set_str(b, bstr, 10) == -1) {
			// Error handling if conversion fails
			printf("error: Invalid number format.\n");
		}		
		//div
		mpf_div(result,a,b);
		//free
		gmp_printf("%.2Ff divided by %.2Ff is: %.15Ff\n", a,b,result);
		mpf_clear(a);
		mpf_clear(b);
		mpf_clear(result);
	}

	if (strcmp(skibidi, "*") == 0){
		mpf_t a, b, result;
	 	// init
		mpf_init(a);
		mpf_init(b);
		mpf_init(result);
		//set
		char astr[1000];
		char bstr[1000];
		printf("enter first float: ");
		tinput(astr,sizeof(astr));
		printf("enter second float: ");
		tinput(bstr,sizeof(bstr));
		if (mpf_set_str(a, astr, 10) == -1) {
			// Error handling if conversion fails
			printf("error: Invalid number format.\n");
		} 
		if (mpf_set_str(b, bstr, 10) == -1) {
			// Error handling if conversion fails
			printf("error: Invalid number format.\n");
		}		
		//mul
		mpf_mul(result,a,b);
		//free
		gmp_printf("%.2Ff multiplied by %.2Ff is: %.15Ff\n", a,b,result);
		mpf_clear(a);
		mpf_clear(b);
		mpf_clear(result);
	}
	if (strcmp(skibidi, "sin") == 0){
	    // Angle in degrees
    double angle_degrees = 90.0;

    // Convert degrees to radians
    double angle_radians = angle_degrees * (PI / 180.0);

    // Calculate the sine of the angle in radians
    double result = sin(angle_radians);

    // Print the result
    printf("Sine of %.2f degrees (%.2f radians) is: %.6f\n", angle_degrees, angle_radians, result);
	}
	if (strcmp(skibidi, "exit") == 0){
	    // break loop and exit
	    exit(1);
	}
	if (strcmp(skibidi, "hmlala") == 0){
		printf("\033[H\033[J");
		printf("hamalala mode activated. will now amath.\n");
	}
	if (strcmp(skibidi, "exit") == 0){
	    // break loop and exit
	    exit(1);
	}
	if (strcmp(skibidi, "clear") == 0){
	    // clear screen
	    printf("\033[H\033[J");
	}
	if (strcmp(skibidi, "help") == 0){
	    // clear screen
	    printf(help());
	}
	}
}

void* audio_thread() {
    // cubeb
    shitbgm();  // hypothetical function
    return NULL;
}

int main(){
	// init function
	// start bgm
	pthread_t thread;
	pthread_create(&thread, NULL, audio_thread, NULL);

	// Main thread can keep doing stuff
	// (or wait for audio to finish, etc.)
	printf("%s\n", title());
	printf("welcome to supershitden calc\n");
	printf("version 1.1.0-puffy-linux64\n");
	printf("NOW WITH ARBITRARY-PRECISION ARITHMETIC\n");
	printf("the best calculator ever because yes. (totally not ribbity)\n");
	opselect();
	pthread_join(thread, NULL);  // Wait for audio thread to finish
	return 0;
}

