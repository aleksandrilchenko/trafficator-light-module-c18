/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "user.c"

// BEGIN CONFIG
/*#pragma config FOSC = INTOSC_EC // Oscillator Selection bits (internal oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF // Flash Program Memory Code Protection bit (Code protection off)
#pragma config MCLRE = OFF*/
//END CONFIG

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
unsigned char wasTurningRight;
unsigned char wasTurningLeft;  
unsigned char hazardIsOn;
//Reverse;



void main()
{
    int ADC2_value = 0; 
    int ADC3_value = 0;
    int ADC_sum_value = 0;
    
    //T0IF = 0;   // Clear the interrupt
    
    while(1)
    {  
    //ANSEL = 0b00010011;                     // 0b00010000 Clear Pin selection bits - AN0-AN3 are digital I/O for now
    //TRISIO = 0b00001011;                    // Gp0, Gp1, Gp3 are always as inputs; Gp5 is always output; Gp2, Gp4 are as outputs for now     
    R_ch_out = 0;
    
    L_ch_out = 0;
    
    if (Reverse == 1)
    {
     ReversOn();                                 //--Turn reverse lights on--//
    return;
    }
    //__delay_ms(2);
    else 
    {
    InitADC(AN2|AN3);               //--Set up AN2 and AN3 --//
    ADC2_value = GetADCValue(AN2);
    ADC3_value = GetADCValue(AN3); 
    }
        
          if (ADC3_value > 4 && ADC2_value > 4)    //--Turn hazard on--//
            {
            Turn_Hazard();    
            }
    else  if (ADC3_value > 5 && ADC2_value < 5)                       //--Turn Relay on if left switch is on--//
            {
            TurnLeft();
            }
    else  if (ADC2_value > 5 && ADC3_value < 5)                      //--Turn Relay on if right switch is on--//
            {
            TurnRight();
            }
    else  if (wasTurningRight == 1 && wasTurningLeft == 0 && hazardIsOn == 0)// && Reverse == 0)
            {
            AddRightBlinks();                     // Add 3 blinks to the right channel if left switch has been off//
            }
    else  if (wasTurningLeft == 1 && wasTurningRight == 0 && hazardIsOn == 0)// && Reverse == 0)
            {
            AddLeftBlinks();                       // Add 3 blinks to the left channel if right switch has been off//
            }
    else    {
            //TRISIO2 = 0; R_ch = 0;
            //TRISIO4 = 0; L_ch = 0;
            ADC2_value = 0; 
            ADC3_value = 0;
            ADC_sum_value = 0;
            wasTurningLeft = 0;
            wasTurningRight = 0;
            hazardIsOn = 0;
            //StopBip();
            }
}
}

