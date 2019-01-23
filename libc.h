/*
 * =====================================================================
 * NAME         : libc.h
 *
 * Descriptions : Definition of S3C2450 Library prototype
 *
 * IDE          : GCC-4.1.0
 *
 * Modification
 *	   
 * =====================================================================
 */
#ifndef __LIBC_H__
#define __LIBC_H__

// extern void MemFill(unsigned long ptr, unsigned long pattern, int size);
// extern void MemDump(unsigned long ptr, int size);

// Uart 관련 함수 
extern void Uart_Init(int baud);
extern void Uart_Printf(char *fmt,...);
extern void Uart_Send_String(char *pt);
extern void Uart_Send_Byte(int data);
extern char Uart_Get_Char();

// LED 관련 함수 
extern void Led_Init();
extern void Led_Display(int data);

// Timer 관련 함수 
extern void Timer_Init(void);
extern void Timer_Delay(int msec);

typedef struct {
    unsigned char bit1   : 4;
    unsigned char bit2   : 4;
    unsigned char bit3   : 8;
} GPIOG; 

typedef struct {
    unsigned char GPIO_PIN_0    : 1;
    unsigned char GPIO_PIN_1    : 1;
    unsigned char SWITCH        : 5;
    // unsigned char GPIO_PIN_2  : 1;
    // unsigned char GPIO_PIN_3  : 1;
    // unsigned char GPIO_PIN_4  : 1;
    // unsigned char GPIO_PIN_5  : 1;
    // unsigned char GPIO_PIN_6  : 1;
    unsigned char GPIO_PIN_7    : 1;
    unsigned char rem           : 8;
} GPIOF;

enum IO_MODE {
    INPUT = (0x00),
    OUTPUT = (0x01),
    EINT = (0x10),
    RESERVED = (0x11)
};

enum EXTI_MODE {
    LOW_LEVEL = (0x0),
    HIGH_LEVEL = (0x1),
    FALLING_EDGE = (0x2),
    RISING_EDGE = (0x4),
    BOTH_EDGE = (0x6)
};

typedef struct {
    unsigned char GP0   : 2;
    unsigned char GP1   : 2;
    unsigned char GP2   : 2;
    unsigned char GP3   : 2;
    unsigned char GP4   : 2;
    unsigned char GP5   : 2;
    unsigned char GP6   : 2;
    unsigned char GP7   : 2;
    unsigned char GP8   : 2;
    unsigned char GP9   : 2;
    unsigned char GP10  : 2;
    unsigned char GP11  : 2;
    unsigned char GP12  : 2;
    unsigned char GP13  : 2;
    unsigned char GP14  : 2;
    unsigned char GP15  : 2;
} GPCON;

#define GPGCON    (*(volatile GPCON *)0x56000060)
#define GPGDAT    (*(volatile GPIOG *)0x56000064)

#define GPFCON (*(volatile GPCON *)0x56000050)
#define GPFDAT (*(volatile GPIOF *)0x56000054)

#endif
