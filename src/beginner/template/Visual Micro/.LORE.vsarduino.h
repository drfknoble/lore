#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
//Board = Arduino Uno
#define __AVR_ATmega328p__
#define __AVR_ATmega328P__
#define ARDUINO 101
#define ARDUINO_MAIN
#define __AVR__
#define __avr__
#define F_CPU 16000000L
#define __cplusplus
#define __inline__
#define __asm__(x)
#define __extension__
#define __ATTR_PURE__
#define __ATTR_CONST__
#define __inline__
#define __asm__ 
#define __volatile__

#define __builtin_va_list
#define __builtin_va_start
#define __builtin_va_end
#define __DOXYGEN__
#define __attribute__(x)
#define NOINLINE __attribute__((noinline))
#define prog_void
#define PGM_VOID_P int
            
typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {;}

//
//
bool drive(int direction);
bool readButton(int button, int &buttonState, int &buttonPrevState, long &debounceTime);
bool readSensor(int sensor, long &distance);

#include "D:\dev\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "D:\dev\Arduino\hardware\arduino\variants\standard\pins_arduino.h" 
#include "C:\Users\FKNoble\SkyDrive\LORE\1.1\Program\Beginner\LORE\LORE.ino"
#endif
