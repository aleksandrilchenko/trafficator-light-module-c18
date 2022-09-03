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

#include    <pic18.h>
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */
#include "ok-sound.h"

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/



// CONFIG1H
#pragma config OSC = ECIO       // Oscillator Selection bits (EC oscillator, port function on RA6)
#pragma config FSCM = OFF       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bit (Brown-out Reset disabled)
// BORV = No Setting

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config MCLRE = OFF      // MCLR Pin Enable bit (RA5 input pin enabled, MCLR disabled)

// CONFIG4L
#pragma config STVR = ON        // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Low-Voltage ICSP Enable bit (Low-Voltage ICSP disabled)

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (00200-000FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (001000-001FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot Block (000000-0001FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (00200-000FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (001000-001FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0001FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (00200-000FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (001000-001FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0001FFh) not protected from table reads executed in other blocks)

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
    int _direction;


void main()
{
    InitApp();
    
    //int _49A_in_value = 0;
    int Reverse_in_value = 0;
    int R_ch_in_value = 0; 
    int L_ch_in_value = 0;
    
    
    //T0IF = 0;   // Clear the interrupt
    
    while(1)
    {  
    R_ch_out = 0;
    L_ch_out = 0;
    _49A_out = 0;
    //_49A_in_value = GetADCValue(AN4);
    Reverse_in_value = GetADCValue(AN6);
   
    
    if (Reverse_in_value > 100)
    {
    ReversOn();                                 //--Turn reverse lights on--//
    return;
    }
    else   
        if (_49A_in == 0)   
        {
            Turn_49A();
            //return;
        }
    else    if (_direction == 1)
            {
            AddRightBlinks();                     // Add 3 blinks to the right channel if left switch has been off//
            }
    else    if (_direction == 2)
            {
            AddLeftBlinks();                       // Add 3 blinks to the left channel if right switch has been off//
            }
    else    {
            R_ch_out = 0;
            L_ch_out = 0;
            _49A_out = 0;
            L_ch_in_value = 0; 
            R_ch_in_value = 0;
            Reverse_in_value = 0;
            _direction = 0;
            }
}
}

