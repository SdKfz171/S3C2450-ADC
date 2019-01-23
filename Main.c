/*
 * =====================================================================
 * NAME         : Main.c
 *
 * Descriptions : Main routine for S3C2450
 *
 * IDE          : GCC-4.1.0
 *
 * Modification
 *    
 * =====================================================================
 */
#include <stdint.h>
#include <stdio.h>
#include "2450addr.h"
#include "libc.h"
#include "option.h"

#define FREQ 1000000

void ADC_Init(){
    uint8_t Prescaler = (PCLK / FREQ) - 1;
	rADCCON = (1 << 14) | (Prescaler << 6) | (1 << 3);
    //rADCCON = 0x4C48;
    rADCMUX = 0x0;
    rADCCON = 0x1;
}

uint16_t ADC_Read(){
    rADCCON = 0x4C49;
    while(!(rADCCON & 0x8000));
    return ((uint16_t)rADCDAT0 & 0xfff);
}

void timer0_init(){
    rTCFG0 = (rTCFG0 & ~0xFF) | (33 - 1);   // 66,000,000 / 33
    rTCFG1 = (rTCFG1 & ~0xF);               // 66,000,000 / 33 / 2
    rTCNTB0 =  (0xFFFF);                    // Max size of buffer 
    rTCON |= (0x02);                        // update TCNTB0
    rTCON = (rTCON & ~(0xf) | (1 << 3) | (1 << 0)); // auto reload & start timer0
}

void delay_us(int us){
    volatile unsigned long now, last, diff;
    now = rTCNTO0;
    while(us > 0){
        last = now;
        now = rTCNTO0;
        if(now > last){ // timer reloaded
            diff = last + (0xFFFF - now) + 1;
        } else {
            diff = last - now;
        }
        us -= diff;
    }
}

void delay_ms(int ms){
    delay_us(ms * 1000);
}

void Main(){
    Uart_Init(115200);
    ADC_Init();

    while(1){
        uint16_t result = ADC_Read();
        
        Uart_Printf("ADC_VAL : %d\r\n", result);
    }
}
