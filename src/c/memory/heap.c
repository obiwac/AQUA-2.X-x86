
#include "heap.h"

static uint8_t heap_space[MAX_HEAP_SPACE];
static uint8_t frames[MAX_FRAMES];

static frame_t frame_buffer;
static frame_set_t frame_set_buffer;

static uint32_t free_buffer;

void init_heap(void) {
	int f;
	for (f = 0; f < MAX_FRAMES; f++) {
		frames[f] = 0;
		
	}
	
}

frame_t heap_first_available_frame(void) {
	int s;
	int p;
	
	for (s = 0; s < MAX_FRAMES; s++) {
		for (p = 0; p < 8; p++) {
			if (!(frames[s] >> p & 1)) {
				frame_buffer.num = s * 8 + p;
				frame_buffer.set = s;
				frame_buffer.pos = p;
				
				return frame_buffer;
				
			}
			
		}
		
	}
	
	printf_warn("WARNING the heap ran out of memory.\n");
	
}

frame_set_t heap_first_available_frame_set(uint32_t len) {
	uint32_t num_frames = 0;
	
	int s;
	int p;
	
	for (s = 0; s < MAX_FRAMES; s++) {
		for (p = 0; p < 8; p++) {
			if (!(frames[s] >> p & 1)) {
				if (num_frames == 0) {
					frame_buffer.num = s * 8 + p;
					frame_buffer.set = s;
					frame_buffer.pos = p;
					
				}
				
				num_frames++;
				
			} else {
				num_frames = 0;
				
			}
			
			if (num_frames == len) {
				frame_set_buffer.start = frame_buffer;
				frame_set_buffer.len = num_frames;
				
				return frame_set_buffer;
				
			}
			
		}
		
	}
	
	printf_error("ERROR the heap doesn't have enough consecutive frames to fit a variable.\n");
	printf_minor("\tVariable size: ~0x%x bytes.\n", len * 16);
	
	while (1);
	
}

frame_t heap_get_frame(uint32_t id) {
	frame_t frame = {
		.num = id,
		.set = id / 8,
		.pos = id % 8,
		
	};
	
	return frame;
	
}

frame_t heap_falloc(void) {
	heap_first_available_frame();
	frames[frame_buffer.set] = frames[frame_buffer.set] | (1 << frame_buffer.pos);
	
	frame_t frame = {
		.num = frame_buffer.num,
		.set = frame_buffer.set,
		.pos = frame_buffer.pos,
		
	};
	
	return frame;
	
}

void heap_ffree(frame_t frame) {
	frames[frame.set] &= ~(1 << frame.pos);
	
}

frame_set_t heap_fsalloc(uint32_t len) {
	heap_first_available_frame_set(len);
	frame_t buffer;
	
	int f;
	for (f = 0; f < frame_set_buffer.len; f++) {
		buffer = heap_get_frame(f + frame_set_buffer.start.num);
		frames[buffer.set] |= 1 << buffer.pos;
		
	}
	
	frame_set_t frame_set = {
		.start = heap_get_frame(frame_set_buffer.start.num),
		.len = len,
		
	};
	
	return frame_set;
	
}

void* kmalloc(uint32_t len) {
	frame_set_buffer = heap_fsalloc(len / 0x10 + 1);
	return &heap_space[frame_set_buffer.start.num * 0x10];
	
}

void kfree(void* ptr, uint32_t len) {
	free_buffer = (uint32_t) ptr - (uint32_t) &heap_space;
	free_buffer /= 0x10;
	
	int b;
	for (b = 0; b < len / 0x10 + 1; b++) {
		frame_buffer = heap_get_frame(b + free_buffer);
		heap_ffree(frame_buffer);
		
	}
	
}
