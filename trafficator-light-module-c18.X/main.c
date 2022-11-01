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

#include "user.h"          /* User funct/params, such as InitApp */
#include "ok-sound.h"

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/
int _direction;

void main()
{
    while(1)
    {
    InitApp();
    R_ch_out = 0;
    L_ch_out = 0;
    _49A_out = 0;
    int _49A_in_value = 0;
    int Reverse_in_value = 0;

    
    _49A_in_value = GetADCValue(_AN2);   // check if toggler is turned left or right
    Reverse_in_value = GetADCValue(_AN6);// check if rear speed is enabled
   
    if (Reverse_in_value > 600)
    {
    ReversOn();                                 //--Turn reverse lights on--//
    return;
    }
    else   
        if (_49A_in_value < 15)   
        {
            Turn_49A();
            return;
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
            Reverse_in_value = 0;
            _49A_in_value = 0;
            _direction = 0;
            }
}
}



//#pragma interrupt_level 2
void __interrupt() hi_isr()
{
    // a simple wait flag to wait for the time to feed the next sample into the PWM modulator
    // kinda like the sampling period.
	if(TMR2IF)
	{
		if(wait) wait--;

		TMR2IF = 0;
	}
}