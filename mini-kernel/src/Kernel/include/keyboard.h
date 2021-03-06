#ifndef _KB_
#define _KB_

#include <stdint.h>

#define LEFT_SHIFT_MAKE   	(char)0x2A
#define RIGHT_SHIFT_MAKE    (char)0x36
#define CAPS_LOCK           (char)0x3A
#define LEFT_SHIFT_BREAK    (char)0xAA
#define RIGHT_SHIFT_BREAK   (char)0xB6
#define CONTROL_MAKE        260
#define CONTROL_R           (char)0x13
#define CONTROL_BREAK       0x9D

#define NOCHAR -1
#define NORMALCOLUMN 1
#define SHIFTEDCOLUMN 2
#define CAPSLOCKEDCOLUMN 3
//falta agregar esta columna
#define ALTEDCOLUMN 4

#define BUFFER_SIZE     256

typedef struct {
	unsigned int shifted;
	unsigned int alted;
	unsigned int capsLocked;
} STATES;

typedef struct {
	unsigned char buffer[BUFFER_SIZE];
	int enqueuePos;
	int dequeuePos;
	STATES state;
} KEYBOARD;

typedef enum {false, true} bool;

bool bufferIsEmpty(void);
bool bufferIsFull(void);
void initializeBuffer();
bool sendToBuffer(char key);
bool updateStates(char key);
int indexOfKey();
void keyboard_handler(uint64_t scancode);
int pop();
void clean_buffer();
void delete_from_buffer();

#endif
