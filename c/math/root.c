
#include "root.h"

float root(float val, int root) {
	if (root == 0) {
		return 1.0f;
		
	} else if (root == 1) {
		return val;
		
	} else if (root == 2) {
		uint32_t i = *(uint32_t*) &val;
		i += 127 << 23;
		i >>= 1;
		
		return *(float*) &i;
		
	} else {
		return pow(val, 1.0 / (float) root);
		
	}
	
}

float sqrt(float x) { return root(x, 2); }
float cbrt(float x) { return root(x, 3); }
