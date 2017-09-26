
#ifndef __AQUA__FS_FS_H
	#define __AQUA__FS_FS_H
	
	#include "../string/string.h"
	#include "../platforms/compat_wrapper.h"
	
	#define FS_INT_SIZE 4
	#define FS_TIMESTAMP_SIZE FS_INT_SIZE * 2
	#define SECTOR_SIZE 512
	#define MAX_FILES 512
	
	#define FS_TEXT 0
	#define FS_APP 1
	#define FS_IMAGE 2
	#define FS_AUDIO 3
	#define FS_VIDEO 4
	#define FS_LINK 5
	
	#define FS_SYSTEM_DATA_SIZE 1
	#define FS_SYSTEM_DATA_SIG "!!AQUA FS 1.0 COMPATIBLE WITH AQUA VERSIONS 2.01.0 ( b ) AND ABOVE. DO NOT MODIFY AT THE RISK OF CORRUPTING ENTIRE FILE SYSTEM!!"
	#define FS_SYSTEM_DATA_SIG_SIZE 128
	#define FS_SYSTEM_DATA_LAST_POWEROFF_TIMESTAMP_SIZE FS_TIMESTAMP_SIZE
	#define FS_SYSTEM_DATA_SUCCESSFUL_POWEROFF_SIZE 1
	#define FS_SYSTEM_DATA_FILES_SIZE FS_INT_SIZE
	#define FS_SYSTEM_DATA_RESERVED_SIZE SECTOR_SIZE - FS_SYSTEM_DATA_SIG_SIZE - FS_SYSTEM_DATA_LAST_POWEROFF_TIMESTAMP_SIZE - FS_SYSTEM_DATA_SUCCESSFUL_POWEROFF_SIZE - FS_SYSTEM_DATA_FILES_SIZE
	
	#define FAT_SIZE MAX_FILES
	#define FAT_NAME_SIZE 128
	#define FAT_TYPE_SIZE 2
	#define FAT_HIDDEN_SIZE 1
	#define FAT_START_SECTOR_SIZE FS_INT_SIZE
	#define FAT_RESERVED_SIZE SECTOR_SIZE - FAT_NAME_SIZE - FAT_TYPE_SIZE - FAT_HIDDEN_SIZE - FAT_START_SECTOR_SIZE
	
	#define FS_DATA_USED_SIG_SIZE FS_INT_SIZE
	#define FS_DATA_USED_SIG "USED"
	#define FS_DATA_NEXT_SECTOR_SIZE FS_INT_SIZE
	#define FS_DATA_DATA_SIZE 512 - FS_DATA_USED_SIG_SIZE - FS_DATA_NEXT_SECTOR_SIZE
	#define FS_DATA_NULL_SECTOR 0x00000000
	
	typedef struct {
		unsigned char bytes[SECTOR_SIZE];
		
	} fs_sector_t;
	
	typedef struct {
		unsigned char signature[FS_SYSTEM_DATA_SIG_SIZE + 1];
		unsigned long long last_poweroff_timestamp;
		unsigned char successful_poweroff;
		unsigned int files;
		//unsigned char reserved[FS_SYSTEM_DATA_RESERVED_SIZE];
		
	} fs_system_data_sector_t;
	
	typedef struct {
		unsigned char name[FAT_NAME_SIZE + 1];
		unsigned short type;
		unsigned char hidden;
		unsigned int starting_sector;
		//unsigned char reserved[FAT_RESERVED_SIZE];
		
	} fs_file_allocation_table_sector_t;
	
	typedef struct {
		unsigned char signature[FS_DATA_USED_SIG_SIZE + 1];
		unsigned int next_sector;
		unsigned char data[FS_DATA_DATA_SIZE];
		
	} fs_data_sector_t;
	
	typedef struct {
		fs_system_data_sector_t system_data;
		fs_file_allocation_table_sector_t file_allocation_table[FAT_SIZE];
		fs_data_sector_t* data;
		
	} fs_file_system_t;
	
	void fs_strcpy(char* a, const char* b, unsigned int start, unsigned int length) {
		int j = 0;
		
		int i;
		for (i = start; i < start + length; i++) {
			a[j] = b[i];
			j++;
			
		}
		
		a[length] = '\0';
		
	}
	
	unsigned int fs_get_uint32(unsigned char a, unsigned char b, unsigned char c, unsigned char d) { return (a << 24) + (b << 16) + (c << 8) + d; }
	unsigned int fs_get_uint16(unsigned char a, unsigned char b) { return (a << 8) + b; }
	
	char* fs_new_disk(unsigned int length) {
		char* new_disk = (char*) malloc(length);
		
		fs_strcpy(new_disk, FS_SYSTEM_DATA_SIG, 0, FS_SYSTEM_DATA_SIG_SIZE);
		
		return new_disk;
		
	}
	
	fs_file_system_t new_fs(char* data, unsigned int length) {
		fs_file_system_t file_system;
		int index = 0;
		
		fs_strcpy(file_system.system_data.signature, data, index, FS_SYSTEM_DATA_SIG_SIZE);
		index += FS_SYSTEM_DATA_SIG_SIZE;
		index += FS_SYSTEM_DATA_LAST_POWEROFF_TIMESTAMP_SIZE;
		
		file_system.system_data.successful_poweroff = data[index];
		index += FS_SYSTEM_DATA_SUCCESSFUL_POWEROFF_SIZE;
		
		file_system.system_data.files = fs_get_uint32(data[index], data[index + 1], data[index + 2], data[index + 3]);
		index += FS_SYSTEM_DATA_FILES_SIZE;
		index += FS_SYSTEM_DATA_RESERVED_SIZE;
		
		int i;
		for (i = 0; i < file_system.system_data.files; i++) {
			fs_strcpy(file_system.file_allocation_table[i].name, data, index, FAT_NAME_SIZE);
			index += FAT_NAME_SIZE;
			
			file_system.file_allocation_table[i].type = fs_get_uint16(data[index], data[index + 1]);
			index += FAT_TYPE_SIZE;
			
			file_system.file_allocation_table[i].hidden = data[index];
			index += FAT_HIDDEN_SIZE;
			
			file_system.file_allocation_table[i].starting_sector = fs_get_uint32(data[index], data[index + 1], data[index + 2], data[index + 3]);
			index += FAT_START_SECTOR_SIZE;
			index += FAT_RESERVED_SIZE;
			
		}
		
		return file_system;
		
	}
	
	unsigned int fs_find_next_sector(void) {
		char* buffer = (char*) malloc(SECTOR_SIZE);
		
		int i;
		for (i = FS_SYSTEM_DATA_SIZE + FAT_SIZE;; i++) {
			if (!(strcmp(buffer, FS_DATA_USED_SIG) == 0)) {
				break;
				
			}
			
		}
		
		mfree(buffer, SECTOR_SIZE);
		return i;
		
	}
	
	fs_file_system_t fs_new_file(fs_file_system_t fs, char* file_name, unsigned short file_type, char* file_data) {
		char sector_template[SECTOR_SIZE];
		fs_strcpy(sector_template, FS_DATA_USED_SIG, 0, FS_DATA_USED_SIG_SIZE);
		
		int i;
		for (i = 0; i < strlen(file_data); i++) {
			unsigned int next_sector = fs_find_next_sector(read_disk);
			printf("%d\n");
			//fs_strcpy(sector_template, *** next sector ***, FS_DATA_USED_SIG_SIZE, FS_DATA_NEXT_SECTOR_SIZE);
			
		}
		
	}
	
#endif
