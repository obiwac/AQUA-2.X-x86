
#ifndef __AQUA__DEFS_H
	#define __AQUA__DEFS_H
	
	#define __AQUA__CURRENT_YEAR 2017
	
	#define __AQUA__EVENT_QUIT 0
	
	#define __AQUA__EVENT_TYPE_WINDOW 0
	#define __AQUA__EVENT_TYPE_KEYBOARD 1
	#define __AQUA__EVENT_TYPE_MOUSE 2
	#define __AQUA__EVENT_TYPE_JOYSTICK 3
	
	#define __AQUA__KEY_CAPS 58
	#define __AQUA__KEY_NUM 69
	#define __AQUA__KEY_SCROLL 70
	
	#define __AQUA__KEY_LSHIFT 42
	#define __AQUA__KEY_LCTRL 29
	#define __AQUA__KEY_LALT 56
	
	#define __AQUA__KEY_RSHIFT 54
	#define __AQUA__KEY_RCTRL 29
	#define __AQUA__KEY_RALT 56
	
	#define __AQUA__KEY_RETURN 28
	#define __AQUA__KEY_SPACE 57
	#define __AQUA__KEY_BACK 14
	#define __AQUA__KEY_TAB 15
	#define __AQUA__KEY_DEL 83
	#define __AQUA__KEY_INS 82
	#define __AQUA__KEY_ESC 1
	#define __AQUA__KEY_WIN 0 /// TODO
	
	#define __AQUA__GREY 53
	#define __AQUA__GREY_MINUS 74
	#define __AQUA__GREY_PLUS 78
	
	#define __AQUA__KEY_PGUP 73
	#define __AQUA__KEY_PGDN 81
	
	#define __AQUA__KEY_UP 72
	#define __AQUA__KEY_DOWN 80
	#define __AQUA__KEY_CENTER 76
	#define __AQUA__KEY_LEFT 75
	#define __AQUA__KEY_RIGHT 77
	
	#define __AQUA__LEFT_CLICK 1
	#define __AQUA__MIDDLE_CLICK 3
	#define __AQUA__RIGHT_CLICK 2
	#define __AQUA__X1_CLICK 4
	#define __AQUA__X2_CLICK 5
	
	#define __AQUA__EVENT_MAX_EVENTS 256
	
	typedef struct { /// TODO the joystick struct and event handler + haptic feedback
		char type;
		char window_type;
		
		char button; // or key in the case of a keyboard
		unsigned char released;
		
		unsigned int x;
		unsigned int y;
		
		unsigned int timestamp;
		unsigned char clicks;
		
	} event_t;
	
	typedef struct {
		event_t events[__AQUA__EVENT_MAX_EVENTS];
		int event_count;
		
	} event_list_t;
	
	void event_init(void);
	event_list_t event_update(void);
	
#endif
