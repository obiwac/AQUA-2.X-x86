
#include "key_map.h"

static char* layout = "qwerty";

static char qwerty_map[] = "``1234567890-=\b\tqwertyuiop[]\n`asdfghjkl;'`#\\zxcvbnm,./";
static char shift_qwerty_map[] = "``!\"#$%^&*()_+\b\tQWERTYUIOP{}\n`ASDFGHJKL:@~~|ZXCVBNM<>?";

static char azerty_map[] = "@@&|\"'($\\!<>)-\b\tazertyuiop^$\n`qsdfghjklm%`#<wxcvbn,;:=";
static char shift_azerty_map[] = "##1234567890'_\b\tAZERTYUIOP:*\n`QSDFGHJKLM%`#>WXCVBN?./+";

void set_layout(char* _layout) {
	layout = _layout;
	
}

char* get_layout(void) {
	return layout;
	
}

char get_letter_from_map(char stroke, uint8_t shift) {
	if (shift) {
		if (stroke == 57) {
			return ' ';
			
		}
		
		if (strcmp(layout, "azerty") == 0) return shift_azerty_map[stroke];
		return shift_qwerty_map[stroke];
		
	} else {
		if (stroke == 57) {
			return ' ';
			
		}
		
		if (strcmp(layout, "azerty") == 0) return azerty_map[stroke];
		return qwerty_map[stroke];
		
	}
	
}
