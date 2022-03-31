#include <stdint.h>
#include "gpio.h"

#define UART0 ((NRF_UART_REG*)0x40002000) //uart base adress

typedef struct {
	volatile uint32_t TASKS_STARTRX; //0X000
	volatile uint32_t TASKS_STOPRX; //0X004
	volatile uint32_t TASKS_STARTTX; //0X008
	volatile uint32_t TASKS_STOPTX; //0X00C
    volatile uint32_t RESERVED1[3]; 
	volatile uint32_t TASKS_SUSPEND; //0x01C
    volatile uint32_t RESERVED2[56]; 
	volatile uint32_t EVENTS_CTS; //0x100
	volatile uint32_t EVENTS_NCTS; //0x104
	volatile uint32_t EVENTS_RXDRDY; //0x108
    volatile uint32_t RESERVED3[4]; 
	volatile uint32_t EVENTS_TXDRDY; //0x11C 
    volatile uint32_t RESERVED4[1]; 
	volatile uint32_t EVENTS_ERROR; //0x124
    volatile uint32_t RESERVED5[7]; 
    volatile uint32_t EVENTS_RXTO; //0x144
    volatile uint32_t RESERVED6[46]; 
    volatile uint32_t SHORTS; // 0x200 
    volatile uint32_t RESERVED7[64]; 
    volatile uint32_t INTENSET; // 0x304
    volatile uint32_t INTENCLR; // 0x308 
    volatile uint32_t RESERVED8[93]; 
    volatile uint32_t ERRORSRC; // 0x480 
    volatile uint32_t RESERVED9[31]; 
    volatile uint32_t ENABLE; // 0x500
    volatile uint32_t RESERVED10[1];  
    volatile uint32_t PSEL_RTS; // 0x508 
    volatile uint32_t PSEL_TXD; // 0x50C 
    volatile uint32_t PSEL_CTS; // 0x510 
    volatile uint32_t PSEL_RXD; // 0x514 
    volatile uint32_t RXD; // 0x518 
    volatile uint32_t TXD; // 0x51C 
    volatile uint32_t RESERVED11[1]; 
    volatile uint32_t BAUDRATE; // 0x524 
    volatile uint32_t RESERVED12[17]; 
    volatile uint32_t CONFIG; // 0x56C
} NRF_UART_REG;

void uart_init(){
    // config in and output
    GPIO1->PIN_CNF[8] = 1; // TX output
	GPIO0->PIN_CNF[6] = 0; // RX input

    // select pins for transmission
    UART0->PSEL_TXD = 0x28; //28
    UART0->PSEL_RXD = 0x6;

    // set transmission baudrate to 9600
    UART0->BAUDRATE = 0x00275000;

    // deenable CTS and RTS
    UART0->EVENTS_NCTS = 1;
    UART0->PSEL_CTS = 0x10000000;
    UART0->PSEL_RTS = 0x10000000;
    // enable UART
    UART0->ENABLE = 0x4;
    UART0->TASKS_STARTRX = 1; // har det noe å si om vi bruker hex eller decimal når vi setter ting

}

void uart_send(char letter){
    UART0->TASKS_STARTTX = 1;
    UART0->TXD = letter;
    while(!(UART0->EVENTS_TXDRDY)){

    }
    UART0->EVENTS_TXDRDY = 0;
    UART0->TASKS_STOPTX = 1;
}

char uart_read(){
    UART0->TASKS_STARTRX = 1;
    char letter;
    while(UART0->EVENTS_RXDRDY == 0){}
    if(UART0->RXD == 0){
        return '\0';
    }
    else{
        letter = UART0->RXD;
        return letter;
    }
}













