
#include "scan.h"

void basic_scan(char* buffer) {
	char buff;
	
	uint8_t i = 0;
	uint8_t reading = 1;
	
	while (reading) {
		if (inportb(0x64) & 0x1)	{
			switch (inportb(0x60)) {
				case 2: {
					printf("1");
					buffer[i++] = '1';
					
					break;
					
				} case 3: {
					printf("2");
					buffer[i++] = '2';
					
					break;
					
				} case 4: {
					printf("3");
					buffer[i++] = '3';
					
					break;
					
				} case 5: {
					printf("4");
					buffer[i++] = '4';
					
					break;
					
				} case 6: {
					printf("5");
					buffer[i++] = '5';
					
					break;
					
				} case 7: {
					printf("6");
					buffer[i++] = '6';
					
					break;
					
				} case 8: {
					printf("7");
					buffer[i++] = '7';
					
					break;
					
				} case 9: {
					printf("8");
					buffer[i++] = '8';
					
					break;
					
				} case 10: {
					printf("9");
					buffer[i++] = '9';
					
					break;
					
				} case 11: {
					printf("0");
					buffer[i++] = '0';
					
					break;
					
				} case 12: {
					printf("-");
					buffer[i++] = '-';
					
					break;
					
				} case 13: {
					printf("=");
					buffer[i++] = '=';
					
					break;
					
				} case 14: {
					if (i > 0) {
						printf("\b");
						buffer[--i] = '\0';
						
					}
					
					break;
					
			   } case 15: {
					printf("\t");
					buffer[i++] = '\t';
					
					break;
					
				} case 16: {
					printf("q");
					buffer[i++] = 'q';
					
					break;
					
				} case 17: {
					printf("w");
					buffer[i++] = 'w';
					
					break;
					
				} case 18: {
					printf("e");
					buffer[i++] = 'e';
					
					break;
					
				} case 19: {
					printf("r");
					buffer[i++] = 'r';
					
					break;
					
				} case 20: {
					printf("t");
					buffer[i++] = 't';
					
					break;
					
				} case 21: {
					printf("y");
					buffer[i++] = 'y';
					
					break;
					
				} case 22: {
					printf("u");
					buffer[i++] = 'u';
					
					break;
					
				} case 23: {
					printf("i");
					buffer[i++] = 'i';
					
					break;
					
				} case 24: {
					printf("o");
					buffer[i++] = 'o';
					
					break;
					
				} case 25: {
					printf("p");
					buffer[i++] = 'p';
					
					break;
					
				} case 26: {
					printf("[");
					buffer[i++] = '[';
					
					break;
					
				} case 27: {
					printf("]");
					buffer[i++] = ']';
					
					break;
					
				} case 28: {
					reading = 0;
					break;
					
				} case 30: {
					printf("a");
					buffer[i++] = 'a';
					
					break;
					
				} case 31: {
					printf("s");
					buffer[i++] = 's';
					
					break;
					
				} case 32: {
					printf("d");
					buffer[i++] = 'd';
					
					break;
					
				} case 33: {
					printf("f");
					buffer[i++] = 'f';
					
					break;
					
				} case 34: {
					printf("g");
					buffer[i++] = 'g';
					
					break;
					
				} case 35: {
					printf("h");
					buffer[i++] = 'h';
					
					break;
					
				} case 36: {
					printf("j");
					buffer[i++] = 'j';
					
					break;
					
				} case 37: {
					printf("k");
					buffer[i++] = 'k';
					
					break;
					
				} case 38: {
					printf("l");
					buffer[i++] = 'l';
					
					break;
					
				} case 39: {
					printf(";");
					buffer[i++] = ';';
					
					break;
					
				} case 40: {
					printf("'");
					buffer[i++] = '\'';
					
					break;
					
				} case 41: {
					printf("`");
					buffer[i++] = '`';
					
					break;
				
				} case 43: {
					printf("%c", (char) 92);
					buffer[i++] = 'q';
					
					break;
					
				} case 44: {
					printf("z");
					buffer[i++] = 'z';
					
					break;
					
				} case 45: {
					printf("x");
					buffer[i++] = 'x';
					
					break;
					
				} case 46: {
					printf("c");
					buffer[i++] = 'c';
					
					break;
					
				} case 47: {
					printf("v");
					buffer[i++] = 'v';
					
					break;				
				} case 48: {
					printf("b");
					buffer[i++] = 'b';
					
					break;			   
				} case 49: {
					printf("n");
					buffer[i++] = 'n';
					
					break;				
				} case 50: {
					printf("m");
					buffer[i++] = 'm';
					
					break;			   
				} case 51: {
					printf(",");
					buffer[i++] = ',';
					
					break;				
				} case 52: {
					printf(".");
					buffer[i++] = '.';
					
					break;			
				} case 53: {
					printf("/");
					buffer[i++] = '/';
					
					break;			
				} case 54: {
					printf(".");
					buffer[i++] = '.';
					
					break;			
				} case 55: {
					printf("/");
					buffer[i++] = '/';
					
					break;
					
				} case 57: {
					printf(" ");
					buffer[i++] = ' ';
					
					break;
					
				}
				
			}
			
		}
		
	}
	
	buffer[i++] = '\0';
	
}
