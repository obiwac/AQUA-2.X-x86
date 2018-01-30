
#include "print.h"

unsigned char print_force_serial = 0;

static void print_char(char _char, colour_t colour) {
	if (VGA_TEXT) print_char_vga_text(_char, colour_compress_4bit(colour));
	if (print_force_serial) write_serial(_char);

}

void print_crude(char* string) {
	int i;
	for (i = 0; i < strlen(string); i++) {
		print_char(string[i], TEXT_COLOUR);
		
	}
	
}

void printf_colour(colour_t colour, const char* format, char** arg) {
	int _char;
	char* buffer = (char*) kmalloc(32);
	
	arg++;
	
	while ((_char = *format++) != 0) {
		if (_char != '%') {
			print_char(_char, colour);
			
		} else {
			char* ptr;
			_char = *format++;
			
			switch (_char) {
				case 'd':
				case 'u':
				case 'x': {
					kernel_itoa(buffer, _char, *((int*) arg++));
					ptr = buffer;
					goto string;
					
					break;
					
				} case 'f': {
					kernel_ftoa(buffer, 2, *((float*) arg++));
					ptr = buffer;
					goto string;
					
					break;
					
				} case 's': {
					ptr = *arg++;
					
					if (!ptr) {
						ptr = "(null)";
						
					}
					
					string: {
						while (*ptr) {
							print_char(*ptr++, colour);
							
						}
						
						break;
						
					}
				
				} default: {
					print_char(*((int*) arg++), colour);
					break;
					
				}
				
			}
			
		}
		
	}
	
	kfree(buffer, 32);
	
}

void printf(char* format, ...) {
	char** arg = (char**) &format;
	printf_colour(TEXT_COLOUR, format, arg);
	
}

void printf_minor(char* format, ...) {
	char** arg = (char**) &format;
	printf_colour(MINOR_COLOUR, format, arg);
	
}

void printf_error(char* format, ...) {
	char** arg = (char**) &format;
	printf_colour(ERROR_COLOUR, format, arg);
	
}

void printf_warn(char* format, ...) {
	char** arg = (char**) &format;
	printf_colour(WARNING_COLOUR, format, arg);
	
}
