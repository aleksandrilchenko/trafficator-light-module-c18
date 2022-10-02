/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>         /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>        /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>    /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#endif

#include "user.h"
#include "ok-sound.h"
#include    <pic18.h>
/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/


#define FOSC	8000000UL
#define T2_FREQ	(11000)		// Between 8000Hz and 11025Hz (same as the WAV file)
#define K_TMR2	 (FOSC/4)/(T2_FREQ) 

    int R_ch_in_value = 0; 
    int L_ch_in_value = 0;
    int V_in_value = 0;
    int V_out_value = 0;
    
    

void InitApp(void)
{
    INTCON = 0b00000000; // disable all ints
    /* TODO Initialize User Ports/Peripherals/Project here */
    /* Setup analog functionality and port direction */
    ADCON1 = 0b00010100;        // AN0,AN1,AN3,AN5,AN6 are analog inputs
                                // bit 7 unimplemented, read as 0
                                /*1= Pin configured as a digital port
                                  0= Pin configured as an analog channel - digital input disabled and reads - 0*/
    TRISA = 0b11111011;
    TRISB = 0b10110010;
    ADCON2 = 0b00001111;        /*bit 7 ADFM:A/D Result Format Select bit
                                        1= Right justified 
                                        0= Left justified 
                                  bit 6 Unimplemented: Read as ?0?
                                  bit 5-3 ACQT<2:0>: A/D Acquisition Time Select bits
                                        001= 2 TAD
                                  bit 2-0 ADCS<2:0>:A/D Conversion Clock Select bits
                                        111= FRC(clock derived from A/D RC oscillator)*/
    
    /* Initialize peripherals */

    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */

    /* Enable interrupts */
}

void InitInterrupt(void)
    {
	//OSCCON = 0xF2; // 0b11110010		// Master OSC at 8MHz RC INT with IDLE MODE

	
	// Timer 2: no interrupt (base period for the PWM on CCP)
	T2CON = 0x00;	// Timer 2 off, FOSC/4, pre 1:1, post 1:1
	PR2  = K_TMR2;	// Load comparator value (PWM period)
    
    // test code
    //PR2= 0xFF;
    //T2CKPS1 = 1; //TIMER2 prescaler 1:16
    //T2CKPS0 = 0;
    //TMR2ON = 1; //TIMER2 ON
    // test code
	TMR2IF = 0;		// Clear the interrupt flag
	TMR2IE = 1;		// Enable timer 2 interrupt (not necessary for the PWM)
	TMR2ON = 1;		// Start the timer and the PWM modulation!

	/* CCP to turn off the sound
	 * P1M1=  0
	 * P1M0=  0  //single output P1A for PWM mode
	 * DC1B1= 0
	 * DC1B0= 0  //lsb of pwm duty cycle
	 * CCP1M3=1
	 * CCP1M2=1
	 * CCP1M1=0
	 * CCP1M0=0  //PWM mode all active high
	 */
	 
	CCP1CON = 0x0C; //0b1100

	// Initial PWM value (no sound)
	CCPR1L=0;	// 8 higher bits
	DC1B1=0;
	DC1B0=0;	// 2 lower bits
	
	PEIE = 1;			// Enable Low Priority Interrupts
	GIE=1;				// Enable High Priority Interrupts
     
}

// Gets the ADC value from AN0-AN6 , returns it as unsigned int 0-1023

int GetADCValue(unsigned char Channel)
{
    int temp_1 =0;
    int temp_2 =0;
    
    ADCON0 = 0b00000000;      // Clear Channel selection bits
    switch(Channel)
    {
        case AN0:   ADCON0 |= 0b00000001; break; // set bit 4-2 to 000
        case AN1:   ADCON0 |= 0b00000101; break; // set bit 4-2 to 001
        case AN2:   ADCON0 |= 0b00001001; break; // set bit 4-2 to 010
        case AN3:   ADCON0 |= 0b00001101; break; // set bit 4-2 to 011
        case AN4:   ADCON0 |= 0b00010001; break; // set bit 4-2 to 100
        case AN5:   ADCON0 |= 0b00010101; break; // set bit 4-2 to 101
        case AN6:   ADCON0 |= 0b00011001; break; // set bit 4-2 to 110

        default: return 0;
    }
    __delay_ms(10);      // Time for Acqusition capacitor to charge up and show correct value
	GO_nDONE  = 1;		  // Enable Go/Done
	while(GO_nDONE)       // wait for conversion completion
    
    //return ((ADRESH<<8)+ADRESL);   // Return 10 bit ADC value
    
    temp_1 = ((ADRESH<<8)+ADRESL); // measure adc (in first time)
    
    __delay_ms(20);      // Time for Acqusition capacitor to charge up and show correct value
	GO_nDONE  = 1;		  // Enable Go/Done
	while(GO_nDONE)       // wait for conversion completion
    ; 
    
    temp_2 = ((ADRESH<<8)+ADRESL); // measure adc (in second time)
    
    return ((temp_1 + temp_2)/2);   // Return 10 bit ADC value (an average value))
}   



/*Get the current value using AN0 and AN1 (GetADCValue(AN0) - GetADCValue (AN1))*/

int GetCurrentValue(void)  // the value is in ADC code
    {               
    int V_in_value = GetADCValue(AN1);
    int V_out_value = GetADCValue(AN0);
    return (V_in_value - V_out_value);    //reverse this logic  
    }

/*Get the direction using AN2 and AN3*/

int GetDirection(void)  // the value is in ADC code
    {
    R_ch_in_value = 0;
    L_ch_in_value = 0;
    
    R_ch_in_value = GetADCValue(AN3);
    L_ch_in_value = GetADCValue(AN5);
    
    if (R_ch_in_value > 100 && L_ch_in_value < 5)
        {
        return _direction = 1; //1 - right; 2 - left; 0 - else
        } 
    else if (L_ch_in_value > 100 && R_ch_in_value < 5)
        {
        return _direction = 2; //1 - right; 2 - left; 0 - else
        }
    else
    {return _direction = 0; //1 - right; 2 - left; 0 - else;
    } 
    }


  /*========  Turn On 49A  ==========*/    
 int Turn_49A()
{
        _49A_out = 1;
        play (okay, 5399);
        __delay_ms(100);
        
        int Current_value = GetCurrentValue();
 
        if (Current_value < 400)       // Increase the frequency if one lamp is broken                 
                {
                _49A_out = 1; 
                __delay_ms(10);
                //play (okay, 5399);
                GetDirection();
                __delay_ms(10);
                _49A_out = 0;                         
                __delay_ms(100);
                return (_direction);
               }       
        else 
                {
                _49A_out = 1;
                __delay_ms(100);
                //play (okay, 5399);
                GetDirection();
                __delay_ms(100);
                _49A_out = 0;
                __delay_ms(400);
                return (_direction); 
                }
    } 

    
    /*========  Turn On Right lamps 3 times  ==========*/
   void AddRightBlinks(void)
            {
            _49A_out = 0;
            L_ch_out = 0;    // latch the Left out to off state
            R_ch_out = 1;
            //play (okay, 5399);
            __delay_ms(300);
            R_ch_out = 0; 
            __delay_ms(500);
            if (_49A_in == 0)
            return;
            R_ch_out = 1;
            //play (okay, 5399);
            __delay_ms(300);
            R_ch_out = 0; 
            __delay_ms(500);
            if (_49A_in == 0)
            return;
            R_ch_out = 1;
            //play (okay, 5399);
            __delay_ms(300);
            R_ch_out = 0;
            L_ch_out = 0;
            __delay_ms(100);
            _direction = 0;
            }
    
    
     /*========  Turn On Left lamps 3 times  ==========*/
    void AddLeftBlinks(void)
            {
            _49A_out = 0;
            R_ch_out = 0;    // latch the Right out to off state
            L_ch_out = 1; 
            //play (okay, 5399);
            __delay_ms(300);
            L_ch_out = 0; 
            __delay_ms(500);
            if (_49A_in == 0)
            return;
            L_ch_out = 1;
            //play (okay, 5399);
            __delay_ms(300);
            L_ch_out = 0; 
            __delay_ms(500);
            if (_49A_in == 0)
            return;
            L_ch_out = 1; 
            //play (okay, 5399);
            __delay_ms(300);
            L_ch_out = 0; 
            R_ch_out = 0;    
            __delay_ms(100);
            _direction = 0;
            }
    
     /*========  Turn On Reverse (Left and Right channels blink simultaneously)  ==========*/ 
    
   void ReversOn(void)
            {
            L_ch_out = 1; 
            R_ch_out = 1;
            //play (okay, 5399);
            __delay_ms(120);
            L_ch_out = 0; R_ch_out = 0;
            __delay_ms(500);        
            }
 