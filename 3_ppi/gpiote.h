#ifndef GPIOTE_H
#define GPIOTE_H
#include <stdint.h>

#define GPIOTE ((NRF_GPIOTE_REG*)0x40006000)

typedef struct {
	// Tasks
	volatile uint32_t TASKS_OUT[8]; // 0x000 - 0x01C
	volatile uint32_t RESERVED0[4];
	volatile uint32_t TASKS_SET[8]; // 0x030 - 0x04C
	volatile uint32_t RESERVED1[4];
	volatile uint32_t TASKS_CLR[8]; // 0x060 - 0x07C
	// Events
	volatile uint32_t RESERVED2[32];
	volatile uint32_t EVENTS_IN[8]; // 0x100 - 0x11C
	volatile uint32_t RESERVED3[23];
	volatile uint32_t EVENTS_PORT; // 0x17C
	// Registers
	volatile uint32_t RESERVED4[97];
	volatile uint32_t INTENSET; // 0x304
	volatile uint32_t INTENCLR; // 0x308
	volatile uint32_t RESERVED5[129];
	volatile uint32_t CONFIG[8]; // 0x510 - 0x52C
} NRF_GPIOTE_REG;



#endif






