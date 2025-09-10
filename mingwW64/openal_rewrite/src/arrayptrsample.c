#include <stdio.h>
// technology of the future !!!

void arrayptrthing(int* a[], int len){
	for (int i = 0; i < len; i++) {
		*a[i] = 0- *a[i];
	}
}
int main(){
	int magick = 255;
	int magick2 = 8953;
	int magick3 = 124124;
	int magick4 = 289238934;
	int* array[] = {&magick,&magick2,&magick3,&magick4};
	int len = sizeof(array) / sizeof(array[0]);
	arrayptrthing(array,len);
	// ok forgor how to do arrays in C lol
	for (int i = 0; i < 4; i++){
		printf("modified %d: %d\n",i,*array[i]);
	}
	return 0;
}
