#include "uart.h"
#include "gpio.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int ubit_button_press_a(){
	return (!(GPIO0->IN & (1 << 14)));
}

int ubit_button_press_b(){
	return (!(GPIO0->IN & (1 << 23)));
}

ssize_t _write(int fd, const void *buf, size_t count){
            char * letter = (char *)(buf);
            for(int i = 0; i < count; i++){
                uart_send(*letter);
                letter++;
            }
            return count;
        }

int ligths_on = 0;

int main(){
    uart_init();
    while(1){
        if(ubit_button_press_a() == 1){
            uart_send('A');
        }

        if(ubit_button_press_b() == 1){
            uart_send('B');
        }

        if(uart_read() != '\0'){
            if(ligths_on == 0){
                gpio_lights_on();
                ligths_on = 1;
            }
            else{
                gpio_lights_off();
            }
        }
    }
}
