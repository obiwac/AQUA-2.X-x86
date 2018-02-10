
#include "pow.h"

float pow(float x, float y) {
	int i;
	for (i = 0; i < y; i++) {
		x *= x;
		
	}
	
	return x;
	
}

int ipow(int x, int y) {
	int i;
	for (i = 0; i < y; i++) {
		x *= x;
		
	}
	
	return x;
	
}
