
#ifndef __AQUA__FS_FS_H
	#define __AQUA__FS_FS_H
	
	#include "../types.h"
	#include "../drivers/ata/ata.h"
	
	void new_file(char* name, char* data);
	void new_dir(char* name);
	void edit_file(char* name, char* data);
	
	void change_dir(char* name);
	void back_dir(void);
	
	void del_file(char* name);
	void del_dir(char* name);
	
#endif
