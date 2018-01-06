
#include "sprintf.h"

int sprintf(char* string, const char* format, ...) {
	char** arg = (char**) &format;
	char* buffer = (char*) kmalloc(32);
	
	int _char;
	int i = 0;
	
	arg++;
	
	while ((_char = *format++) != 0) {
		if (_char != '%') {
			string[i++] = _char;
			
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
					
				} case 's': {
					ptr = *arg++;
					
					if (!ptr) {
						ptr = "(null)";
						
					}
					
					string: {
						while (*ptr) {
							string[i++] = *ptr++;
							
						}
						
						break;
						
					}
					
				} default: {
					string[i++] = *((int*) arg++);
					break;
					
				}
				
			}
			
		}
		
	}
	
	kfree(buffer, 32);
	return 0;
	
}
