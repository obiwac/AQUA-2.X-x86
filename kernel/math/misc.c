
#include "misc.h"

float exp(float x) {
	return pow(E, x);
	
}

float fmod(float x, float y) {
	if (x < y) return x;
	else return (x - y * floor(x / y));
	
}

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }
