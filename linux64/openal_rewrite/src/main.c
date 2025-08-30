/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * main.c — supershitden calc
 * Copyright (c) 2025 GarethTacos
 */

#include <stdio.h>
#include "misc.h"
#include <string.h>
#include <math.h>
#include <gmp.h>
#include "audio.h"
#include "dr_flac.h"
#include <stdlib.h>
#include <pthread.h>
// pthread is back so when loading audio, block won't occur
#define PI 3.1415926535897932384626433832795
// current state of project
// cpp port cancelled because cmake is disgusting
// now working on json parsing and updating
// fhs soln possibly needed
// OPENAL REWRITE BABEY!!!!!!
// also cleaner interfacing.
shitaudio bgm;
// non block
pthread_t audioload;
pthread_mutex_t aumtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t aucond = PTHREAD_COND_INITIALIZER;
int audload = 0;
int joined = 0;
void* setup_audio(){
	// init function
	// init OpenAL
	audload = 0;
	pthread_mutex_lock(&aumtx);
	shitaudio_init(&bgm);
	bgm.buffer = 0;
	bgm.source = 0;
	bgm.duration = 0.0f;
	if (shitaudio_opus_genpcm(&bgm,"cuso4.ogg") == 0){
		shitaudio_gensource(&bgm);
		shitaudio_reverb(&bgm);
	}
	audload = 1;
	pthread_mutex_unlock(&aumtx);
	return NULL;
}
void chk_lock(){
	if (!joined){
	pthread_mutex_lock(&aumtx);
	while (!audload) pthread_cond_wait(&aucond,&aumtx);
	pthread_mutex_unlock(&aumtx);
	pthread_join(audioload, NULL);
	joined = 1;
	}
}
void tinput(char *buffer, size_t size) {
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);

        // If last char isn't newline, input was longer than buffer
        if (len > 0 && buffer[len - 1] != '\n') {
            int c;
            // flush the rest of the line
            while ((c = getchar()) != '\n' && c != EOF);
        } else if (len > 0 && buffer[len - 1] == '\n') {
            // strip newline
            buffer[len - 1] = '\0';
        }
    } else {
        // Handle EOF or error
        buffer[0] = '\0';
    }
}
void in3_clear(mpz_t *a, mpz_t *b, mpz_t *result){
		mpz_clear(*a);
		mpz_clear(*b);
		mpz_clear(*result);
}
void fl3_clear(mpf_t *a, mpf_t *b, mpf_t *result){
		mpf_clear(*a);
		mpf_clear(*b);
		mpf_clear(*result);
}
int in2_o1_init(mpz_t *a, mpz_t *b, mpz_t *result){
	 	// init
	mpz_init(*a);
	mpz_init(*b);
	mpz_init(*result);
	//set
	char astr[1000];
	char bstr[1000];
	printf("enter first integer: ");
	tinput(astr,sizeof(astr));
	printf("enter second integer: ");
	tinput(bstr,sizeof(bstr));
	if (mpz_set_str(*a, astr, 10) == -1) {
		// Error handling if conversion fails
		printf("error: Invalid number format.\n");
		return -1;
	} 
	if (mpz_set_str(*b, bstr, 10) == -1) {
		// Error handling if conversion fails
		printf("error: Invalid number format.\n");
		return -1;
	}
	return 0;
}
int fl2_o1_init(mpf_t *a, mpf_t *b, mpf_t *result){
	 	// init
		mpf_init(*a);
		mpf_init(*b);
		mpf_init(*result);
		//set
		char astr[1000];
		char bstr[1000];
		printf("enter first float: ");
		tinput(astr,sizeof(astr));
		printf("enter second float: ");
		tinput(bstr,sizeof(bstr));
		if (mpf_set_str(*a, astr, 10) == -1) {
			// Error handling if conversion fails
			printf("error: Invalid number format.\n");
			return -1;
		} 
		if (mpf_set_str(*b, bstr, 10) == -1) {
			// Error handling if conversion fails
			printf("error: Invalid number format.\n");
			return -1;
		}
		return 0;
}
void opselect(){
	char skibidi[64] = "";
	while (strcmp(skibidi, "exit") != 0){
	printf("select an operation for shitden to calculate or type 'help' for a list ");
	fflush(stdout);
	tinput(skibidi,sizeof(skibidi));
	//printf("You entered: %s\n", skibidi);
	// add func
	if (strcmp(skibidi, "+") == 0){
		mpz_t a, b, result;
		// check if valid
		if (in2_o1_init(&a,&b,&result) == 0){
			mpz_add(result,a,b);
			gmp_printf("the sum of %Zd and %Zd is: %Zd\n", a,b,result);
		};
		//free
		in3_clear(&a,&b,&result);
	}
	// sub func
	if (strcmp(skibidi, "-") == 0){
		mpz_t a, b, result;
		// check if valid
		if (in2_o1_init(&a,&b,&result) == 0){
			mpz_sub(result,a,b);
			gmp_printf("the difference of %Zd and %Zd is: %Zd\n", a,b,result);
		};
		//free
		in3_clear(&a,&b,&result);
	}
	// div func
	if (strcmp(skibidi, "/") == 0){
		mpf_t a, b, result;
		if (fl2_o1_init(&a,&b,&result) == 0){
				//div
				mpf_div(result,a,b);
				gmp_printf("%.2Ff divided by %.2Ff is: %.15Ff\n", a,b,result);
		}
		fl3_clear(&a,&b,&result);
	}
	// mul func
	if (strcmp(skibidi, "*") == 0){
		mpf_t a, b, result;
		if (fl2_o1_init(&a,&b,&result) == 0){
				mpf_mul(result,a,b);
				gmp_printf("%.2Ff multiplied by %.2Ff is: %.15Ff\n", a,b,result);
		}
		fl3_clear(&a,&b,&result);
		}
	// trigoooo sin
	if (strcmp(skibidi, "sin") == 0){
	    // Angle in degrees
	    double angle_degrees = 90.0;
	    // Convert degrees to radians
	    double angle_radians = angle_degrees * (PI / 180.0);
	    // Calculate the sine of the angle in radians
	    double result = sin(angle_radians);
	    // Print the result
	    printf("Sine of %g degrees (%g radians) is: %g\n", angle_degrees, angle_radians, result);
	}
	if(strcmp(skibidi, "bgm ff") == 0){
		// get duration to skip to
		fflush(stdout);
		printf("warn: this function is very skibidi\n");
		if (bgm.duration != 0.0f) printf("duration: %f\n",bgm.duration);
		printf("where do you want to skip to? ");
		tinput(skibidi,sizeof(skibidi));
		float skip = atof(skibidi);
		shitaudio_seek(&bgm,skip);
	}
	if (strcmp(skibidi, "exit") == 0){
	    // break loop and exit
	    chk_lock();
	    shitaudio_fxdie(&bgm);
	    shitaudio_stop(&bgm);
	    shitaudio_destroy(&bgm);
	}
	// problem was solved
	// turns out it was a buffer issue
	// bgm start pushed [10] to its limit which caused weird behaviour
	// now skibidi is [64] so more headroom
	if(strcmp(skibidi, "bgm start") == 0){
		chk_lock();
		shitaudio_cheap_replay(&bgm);
	}
	if(strcmp(skibidi, "bgm stop") == 0){
		// won't destroy things like stop
		chk_lock();
		shitaudio_pause(&bgm);
	}
	if (strcmp(skibidi, "hmlala") == 0){
		printf("\033[H\033[J");
		printf("hamalala mode activated. will now amath.\n");
	}
	if (strcmp(skibidi, "clear") == 0){
	    // clear screen ANSI code
	    // won't work on old DOS type shit
	    // only new terminals like Kitty prob
	    printf("\033[H\033[J");
	}
	if (strcmp(skibidi, "help") == 0){
	    // print help
	    printf("%s",help());
	}
	}
}


int main(){
	// no more thread tomfoolery because dangerous
	pthread_create(&audioload,NULL,setup_audio,NULL);
	printf("%s\n", title());
	// name change?!?!?!
	printf("welcome to totally awesum no3calc\n");
	printf("version forgor\n");
	printf("WITH ARBITRARY-PRECISION ARITHMETIC\n");
	printf("the best calculator ever because yes. (totally not nom)\n");
	opselect();
	return 0;
}

