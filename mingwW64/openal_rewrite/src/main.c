/* SPDX-License-Identifier: GPL-3.0-or-later */
/*
 * main.c — supershitden calc
 * Copyright (c) 2025 GarethTacos
 */
// To download:
// OpenAL Docs
// Opusfile Docs
// GMP docs
// MPFR docs
// pthread docs
// other funni stuff docs
// general C programming book
// also cascadia code font instead of mononoki
// need tem ligatures
#include <stdio.h>
#include "misc.h"
#include <string.h>
#include <math.h>
#include <gmp.h>
// exclude because not using yet #include <mpfr.h>
#include "audio.h"
#include <stdlib.h>
#include <assert.h>
//#include <pthread.h>
// no pthreads dis time because mingw hates me
// so expect blocking audio
// and a shit ton of dlls
// tongue is killing me bcos oral thrush or wounds idk
// bored so im writing about it.
// pthread is back so when loading audio, block won't occur
#define PI 3.1415926535897932384626433832795
// current state of project
// cpp port maybe because cmake is tolerable
// now working on cleaner functions
// OPENAL REWRITE BABEY!!!!!!
// also cleaner interfacing.
// rewritten init functions to be indefinite and more dynamic
shitaudio bgm;
// booleans lol (lazy to import stdbool)
// ok maybe should import stdbool so my foot stays intact
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
void ina_clear(mpz_ptr arr[], int len){
	for (int i=0; i < len; i++){
		mpz_clear(arr[i]);
	}
}

void ina_init(mpz_ptr arr[], int len){
	for (int i=0; i < len; i++){
		mpz_init(arr[i]);
	}
}

void rta_clear(mpq_ptr arr[], int len){
	for (int i=0; i < len; i++){
		mpq_clear(arr[i]);
	}
}

void rta_init(mpq_ptr arr[], int len){
	for (int i=0; i < len; i++){
		mpq_init(arr[i]);
	}
}
void fla_clear(mpf_ptr arr[], int len){
	for (int i = 0; i < len; i++){
		mpf_clear(arr[i]);
	}
}

void fla_init(mpf_ptr arr[], int len){
	for (int i = 0; i < len; i++){
		mpf_init(arr[i]);
	}
}
int fla_tofl(mpf_ptr afl[], char *astr[], int len){
	for (int i = 0; i < len; i++){
		if (mpf_set_str(afl[i],astr[i],10) == -1){
			printf("error: invalid number format.\n");
			return -1;
		}
	}
	return 0;
}

int ina_toin(mpz_ptr ain[], char *astr[], int len){
	for (int i = 0; i < len; i++){
		if (mpz_set_str(ain[i],astr[i],10) == -1){
			printf("error: invalid number format.\n");
			return -1;
		}
	}
	return 0;
}

int rta_tort(mpq_ptr art[], char *astr[], int len){
	for (int i = 0; i < len; i++){
		if (mpq_set_str(art[i],astr[i],10) == -1){
			printf("error: invalid number format.\n");
			return -1;
		}
	}
	return 0;
}

// to change to ptr array so can shove as many variables inside
// for in3 and fl3 clear
// also to change to ptr array

// PTR ARR AGAIN!!!!
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
	char skibidi[64] = ""; // usr input name
	while (strcmp(skibidi, "exit") != 0){
	printf("select an operation for shitden to calculate or type 'help' for a list ");
	fflush(stdout);
	tinput(skibidi,sizeof(skibidi));
	//printf("You entered: %s\n", skibidi);
	// add func
	if (strcmp(skibidi, "+") == 0){
		// vars and arrs
		mpz_t a, b, result;
		mpz_ptr arr[] = {a,b,result};
		ina_init(arr,3); // init so no weird shit happens
		// user input
		char astr[1000];
		char bstr[1000];
		printf("enter first integer: ");
		tinput(astr,sizeof(astr));
		printf("enter second integer: ");
		tinput(bstr,sizeof(bstr));
		// str arr for easy passing
		char *str_arr[] = {astr,bstr};
		// check if valid
		if(ina_toin(arr,str_arr,2) == 0){
			mpz_add(result,a,b);
			gmp_printf("the sum of %Zd and %Zd is: %Zd\n", a,b,result);
		};
		//free
		//don't fix what alr works, changed this to mpz_t and err'd badly lol
		ina_clear(arr,3);
	}
	// sub func
	if (strcmp(skibidi, "-") == 0){
		// make vars and arrs
		mpz_t a, b, result;
		mpz_ptr arr[] = {a,b,result};
		// init so weird shit don't happen like last time
		ina_init(arr,3);
		// get usr input
		char astr[1000];
		char bstr[1000];
		printf("enter first integer: ");
		tinput(astr,sizeof(astr));
		printf("enter second integer: ");
		tinput(bstr,sizeof(bstr));
		// make an array for easier passing
		char *str_arr[] = {astr,bstr};
		// check if valid
		if(ina_toin(arr,str_arr,2) == 0){
			mpz_sub(result,a,b);
			gmp_printf("the difference of %Zd and %Zd is: %Zd\n", a,b,result);
		};
		//free
		ina_clear(arr,3);
	}
	// div func
	if (strcmp(skibidi, "/") == 0){
		mpq_t a, b, result;
		mpq_ptr arr[] = {a,b,result};
		rta_init(arr,3);
		// user input
		char astr[1000];
		char bstr[1000];
		printf("enter first float: ");
		tinput(astr,sizeof(astr));
		printf("enter second float: ");
		tinput(bstr,sizeof(bstr));
		// str arr for easy passing
		char *str_arr[] = {astr,bstr};		
		if (rta_tort(arr,str_arr,2) == 0){
				//div
				mpq_div(result,a,b);
				// make temporary float
				mpf_t f;
				mpf_init(f);
				mpf_set_q(f, result);
				gmp_printf("%Qd divided by %Qd is: %.Ff\n", a,b,f);
				mpf_clear(f);
		}
		rta_clear(arr,3);
	}
	// mul func
	if (strcmp(skibidi, "*") == 0){
		mpf_t a, b, result;
		mpf_ptr arr[] = {a,b,result};
		fla_init(arr,3);
		// user input
		char astr[1000];
		char bstr[1000];
		printf("enter first float: ");
		tinput(astr,sizeof(astr));
		printf("enter second float: ");
		tinput(bstr,sizeof(bstr));
		// str arr for easy passing
		char *str_arr[] = {astr,bstr};		
		if (fla_tofl(arr,str_arr,2) == 0){
				mpf_mul(result,a,b);
				gmp_printf("%.Ff multiplied by %.Ff is: %.Ff\n", a,b,result);
		}
		fla_clear(arr,3);
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
		printf("%swarn:%s this function is very skibidi\n",ANSI_COLOR_YELLOW,ANSI_RESET);
		if (bgm.duration != 0.0f) printf("duration: %f\n",bgm.duration);
		printf("where do you want to skip to? ");
		tinput(skibidi,sizeof(skibidi));
		float skip = atof(skibidi);
		shitaudio_seek(&bgm,skip);
	}
	if (strcmp(skibidi, "exit") == 0){
	    // break loop and exit
	    shitaudio_fxdie(&bgm);
	    shitaudio_stop(&bgm);
	    shitaudio_destroy(&bgm);
	}
	// problem was solved
	// turns out it was a buffer issue
	// bgm start pushed [10] to its limit which caused weird behaviour
	// now skibidi is [64] so more headroom
	if(strcmp(skibidi, "bgm start") == 0){
		shitaudio_cheap_replay(&bgm);
	}
	if(strcmp(skibidi, "bgm stop") == 0){
		// won't destroy things like stop
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
	shitaudio_init(&bgm);
	bgm.buffer = 0;
	bgm.source = 0;
	bgm.duration = 0.0f;
	if (shitaudio_opus_genpcm(&bgm,"hachi2hoshimi.ogg") == 0){
		shitaudio_gensource(&bgm);
		shitaudio_reverb(&bgm);
	}
	printf("%s\n", title());
	// name change?!?!?!
	printf("welcome to totally awesum no3calc\n");
	printf("version forgor\n");
	printf("WITH ARBITRARY-PRECISION ARITHMETIC\n");
	printf("the best calculator ever because yes. (totally not nom)\n");
	opselect();
	return 0;
}

