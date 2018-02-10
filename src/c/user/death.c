
#include "death.h"

void die(char* message) {
	vga_set_mode(320, 200, 8);
	
	int x;
	int y;
	
	for (x = 0; x < 320; x++) {
		for (y = 0; y < 200; y++) {
			vga_put_pixel(x, y, 6);
			
		}
		
	}
	
	hang();
	
}
