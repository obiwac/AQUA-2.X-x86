
#include "trig.h"

float cos(float x) {
	x = fabs(x);
	x = fmod(x, 360.0f);
	
	int flx = floor(x);
	
	float c1 = table_cos[flx];
	float c2 = table_cos[flx + 1];
	
	return c1 + ((c2 - c1) * (x - flx));
	
}

float sin(float x) {
	x = fabs(x);
	x = fmod(x, 360.0f);
	
	int flx = floor(x);
	
	float c1 = table_sin[flx];
	float c2 = table_sin[flx + 1];
	
	return c1 + ((c2 - c1) * (x - flx));
	
}

float tan(float x) {
	x = fabs(x);
	x = fmod(x, 360.0f);
	
	int flx = floor(x);
	
	float c1 = table_tan[flx];
	float c2 = table_tan[flx + 1];
	
	return c1 + ((c2 - c1) * (x - flx));
	
}
