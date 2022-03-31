#ifndef PPI_H
#define PPI_H
#include <stdint.h>

#define PPI ((NRF_PPI_REG*)0x4001F000)

typedef struct {
	uint32_t EN;
	uint32_t DIS;
} PPI_TASKS_TYPE;

typedef struct {
	uint32_t EEP;
	uint32_t TEP;
} PPI_CHANNEL_TYPE;

typedef struct {
	// Tasks
	volatile PPI_TASKS_TYPE PPI_TASKS[6]; // 0x000 - 0x02C
	// Registers
	volatile uint32_t RESERVED0[308];
	volatile uint32_t CHEN; // 0x500
	volatile uint32_t CHENSET; // 0x504
	volatile uint32_t CHENCLR; // 0x508
	volatile uint32_t RESERVED1[1];
	volatile PPI_CHANNEL_TYPE PPI_CH[20]; // 0x510 - 0x5AC
	volatile uint32_t RESERVED2[148];
	volatile uint32_t CHG[6]; // 0x800 - 0x814
	volatile uint32_t RESERVED3[62];
	volatile uint32_t FORK_TEP[32]; // 0x910 - 0x98C
} NRF_PPI_REG;

#endif

void init_PPI(); // 6.9.4.8 CONFIG[n] (n=0..7)
