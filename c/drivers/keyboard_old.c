
#include "keyboard_old.h"

uint8_t poll_key(void) {
	if (inportb(0x64) & 0x1) {
		return inportb(0x60);
		
	} else {
		return '\0';
		
	}
	
}

void read_str(char* buffer, char colour) {
	char buf;
	
	uint8_t i = 0;
	uint8_t reading = 1;
	uint8_t shift = 0;
	
	while (reading) {
		if (inportb(0x64) & 0x1) {
			char char_type = 'c';
			
			switch (inportb(0x60)) {
				case 1: {
					buf = (char) 27;
					break;
					
				} case 2: {
					buf = '1';
					break;
					
				} case 3: {
					buf = '2';
					break;
					
				} case 4: {
					buf = '3';
					break;
					
				} case 5: {
					buf = '4';
					break;
					
				} case 6: {
					buf = '5';
					break;
					
				} case 7: {
					buf = '6';
					break;
					
				} case 8: {
					buf = '7';
					break;
					
				} case 9: {
					buf = '8';
					break;
					
				} case 10: {
					buf = '9';
					break;
					
				} case 11: {
					buf = '0';
					break;
					
				} case 12: {
					buf = '-';
					break;
					
				} case 13: {
					buf = '=';
					break;
					
				} case 14: {
					print_char_vga_text('\b', colour);
					char_type = 'n';
					buffer[i] = 0;
					i--;
					
					break;
					
				} case 16: {
					buf = 'q';
					break;
					
				} case 17: {
					buf = 'w';
					break;
					
				} case 18: {
					buf = 'e';
					break;
					
				} case 19: {
					buf = 'r';
					break;
					
				} case 20: {
					buf = 't';
					break;
					
				} case 21: {
					buf = 'y';
					break;
					
				} case 22: {
					buf = 'u';
					break;
					
				} case 23: {
					buf = 'i';
					break;
					
				} case 24: {
					buf = 'o';
					break;
					
				} case 25: {
					buf = 'p';
					break;
					
				} case 26: {
					buf = '[';
					break;
					
				} case 27: {
					buf = ']';
					break;
					
				} case 28: {
					reading = 0;
					char_type = 'n';
					//i++;
					
					break;
					
				} case 30: {
					buf = 'a';
					break;
					
				} case 31: {
					buf = 's';
					break;
					
				} case 32: {
					buf = 'd';
					break;
					
				} case 33: {
					buf = 'f';
					break;
					
				} case 34: {
					buf = 'g';
					break;
					
				} case 35: {
					buf = 'h';
					break;
					
				} case 36: {
					buf = 'j';
					break;
					
				} case 37: {
					buf = 'k';
					break;
					
				} case 38: {
					buf = 'l';
					break;
					
				} case 39: {
					buf = ';';
					break;
					
				} case 40: {
					buf = (char) 44;
					break;
					
				} case 41: {
					buf = (char) 44;
					break;
					
				} case 42: {
					shift = 1;
					break;
					
				} case 44: {
					buf = 'z';
					break;
					
				} case 45: {
					buf = 'x';
					break;
					
				} case 46: {
					buf = 'c';
					break;
					
				} case 47: {
					buf = 'v';
					break;
					
				} case 48: {
					buf = 'b';
					break;
					
				} case 49: {
					buf = 'n';
					break;
					
				} case 50: {
					buf = 'm';
					break;
					
				} case 51: {
					buf = ',';
					break;
					
				} case 52: {
					buf = '.';
					break;
					
				} case 53: {
					buf = '/';
					break;
					
				} case 54: {
					buf = '.';
					break;
					
				} case 55: {
					buf = '/';
					break;
					
				} case 56: {
					shift = 1;
					break;
					
				} case 57: {
					buf = ' ';
					break;
					
				} default: {
					char_type = 'n';
					shift = 0;
					
					break;
					
				}
				
			}
			
			if (char_type == 'c') {
				print_char_vga_text(buf, colour);
				buffer[i] = buf;
				i++;
				
			}
			
		}
		
	}
	
	buffer[i] = '\0';
	
}
