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

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

#define _XTAL_FREQ 4000000  // 4MHZ internal crystal
    int R_ch_in_value = 0; 
    int L_ch_in_value = 0;
    int V_in_value = 0;
    int V_out_value = 0;
    
    

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */

    /* Initialize peripherals */

    /* Configure the IPEN bit (1=on) in RCON to turn on/off int priorities */

    /* Enable interrupts */
}

void InitADC(unsigned char Channel)
{
    /* ADC Initialisation*/
    
    ADCON1 = 0b00000000;        // all inputs are analog inputs
                                // bit 7 unimplemented, read as 0
                                /*1= Pin configured as a digital port
                                  0= Pin configured as an analog channel - digital input disabled and reads - 0*/
    ADCON1 |= Channel;         // 0b0[xxxxxxx] Select Pin as AN0-AN6 depends on algorithm
    
    TRISA = 0b00001011;      // CHANGE IT!!!Gp0, Gp1, Gp3 are always as inputs; Gp5 is always output; Gp2, Gp4 are as outputs for now
    TRISA |= Channel;        // CHANGE IT!!!0b000[x]1[x]11 Select Pin as AN0-AN3 depends on algorithm
   
    ADCON0 = 0b00000001;        //set Ref voltages as Vdd/Vss  (bit 7-6 as 00)
                                // bit 5 unimplemented, read as 0
                                /*bit 4-2 CHS<2:0>:Analog Channel Select bits
                                    000= Channel 0 (AN0) 
                                    001= Channel 1 (AN1) 
                                    010= Channel 2 (AN2) 
                                    011= Channel 3 (AN3) 
                                    100= Channel 4 (AN4) 
                                    101= Channel 5 (AN5) 
                                    110= Channel 6 (AN6)
                                    111= Unimplemented  
                                 bit 1 GO/DONE: A/D Conversion Status bit
                                    When ADON = 1:
                                    1= A/D conversion in progress
                                    0= A/D Idle 
                                 bit 0 ADON:A/D On bit
                                    1= A/D converter module is enabled 
                                    0= A/D converter module is disabled*/
    
    ADCON2 = 0b00000111;        /*bit 7 ADFM:A/D Result Format Select bit
                                        1= Right justified 
                                        0= Left justified 
                                  bit 6 Unimplemented: Read as ?0?
                                  bit 5-3 ACQT<2:0>: A/D Acquisition Time Select bits
                                        000= 0 TAD
                                  bit 2-0 ADCS<2:0>:A/D Conversion Clock Select bits
                                        111= FRC(clock derived from A/D RC oscillator)*/
    
/*
    ANSEL = 0b00010000;       // 0x10 Clear Pin selection bits - AN2-AN3 are digital I/O for now
    ANSEL |= Channel;         // 0b0001[xxxx] Select Pin as AN0-AN3 depends on algorithm
    TRISIO = 0b00001011;      // Gp0, Gp1, Gp3 are always as inputs; Gp5 is always output; Gp2, Gp4 are as outputs for now
    TRISIO |= Channel;        // 0b000[x]1[x]11 Select Pin as AN0-AN3 depends on algorithm
    ADCON0 = 0b10000001;      //0x81 // Turn on the A/D Converter ADFM and ADON
 */ 


}
 
  

/*void InitInterrupt (void)    // is not using now
{
        // TIMER0 Initialisation//
    
    OPTION_REG	=	0b10000111;	//set timer pre-scaler to 64/pre-scaler assigned to timer module 
		//	nGPPU = 1;		// internal pull-ups disabled
		//	INTEDG = 0;		// falling edge trigger the interrupt__don't care
		//	T0CS = 0;		// timer transition on cycle clock
		//	T0SE = 0		// increment on low to high transition of GP2
		//	PSA = 0			// pre-scaler is set to the TIMER0 module
		//  ps>>101, or 64 / 111, or 256
    
    //INTERRUPTS Initialisation//
    
	INTCON	= 0b10100000;
		//GIE = 1 	//enable global interrupts
		//PEIE = 0 	//disable peripheral interrupts
		//T0IE = 1	//enable TMR0 interrupts
		//INTE = 0	//disable GP2 interrupt
		//GPIE = 0	//disable GPIO port change interrupt
		//T0IF = 0	//timer0 overflow flag
		//INTF = 0	//GP2 interrupt flag
		//GPIF = 0	//ext pin change interrupt
	T1CON	=	0x00; //clear unused timer
	PIE1	=	0x00;	//nothing here is needed
}*/


  /* GetADCValue:
 * Gets the ADC value from AN0-AN5 , returns it as unsigned int 0-1023
 */
int GetADCValue(unsigned char Channel)
{
    int temp_1 =0;
    int temp_2 =0;
    
    ADCON0 &= 0b11100011;      // Clear Channel selection bits
    switch(Channel)
    {
        case AN0:   ADCON0 |= 0b00000000; break; // set bit 4-2 to 000
        case AN1:   ADCON0 |= 0b00000100; break; // set bit 4-2 to 001
        case AN2:   ADCON0 |= 0b00001000; break; // set bit 4-2 to 010
        case AN3:   ADCON0 |= 0b00001100; break; // set bit 4-2 to 011
        case AN4:   ADCON0 |= 0b00010000; break; // set bit 4-2 to 100
        case AN5:   ADCON0 |= 0b00010100; break; // set bit 4-2 to 101
        case AN6:   ADCON0 |= 0b00011000; break; // set bit 4-2 to 110

        default: return 0;
    }
    __delay_ms(10);      // Time for Acqusition capacitor to charge up and show correct value
	GO_nDONE  = 1;		  // Enable Go/Done
	while(GO_nDONE)       // wait for conversion completion
    ; 
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
    InitADC(AN0|AN1);
    int V_in_value = GetADCValue(AN0);
    int V_out_value = GetADCValue(AN1);
    return (V_in_value - V_out_value);    //reverse this logic  
    }

/*Get the direction using AN2 and AN3*/

bool GetDirection(void)  // the value is in ADC code
    {
    InitADC(AN2|AN3);               //--Set up AN2 and AN3 --//
    R_ch_in_value = GetADCValue(AN2);
    L_ch_in_value = GetADCValue(AN3);
    
    if (R_ch_in_value > 10 && R_ch_in_value < 10)
        {return 
                wasTurningRight = 1;
                wasTurningLeft = 0;}
    else if (R_ch_in_value < 10 && R_ch_in_value > 10)
        {return 
                wasTurningLeft = 1;
                wasTurningRight = 0;}
    else
    {return 
                wasTurningLeft = 0;
                wasTurningRight = 0;
    }
    }


  /*========  Turn On 49A  ==========*/    
bool Turn_49A()
{
        //TRISIO = 0b00001011;
        _49A_out = 1; 
        __delay_ms(100);
        
        int Current_value = GetCurrentValue();
 
        if (Current_value < 5)       // Increase the frequency if one lamp is broken                 
                {
                _49A_out = 1; 
                //Bip();
                GetDirection();
                __delay_ms(50);
                _49A_out = 0;                         
                __delay_ms(200);
                Current_value = 0;
                return (wasTurningLeft & wasTurningRight);
               }
                
        else 
                {
                _49A_out = 1;
                //Bip();
                GetDirection();
                __delay_ms(100);
                _49A_out = 0;
                __delay_ms(400);
                Current_value = 0;
                return (wasTurningLeft & wasTurningRight);           
                }
    } 

    
    /*========  Turn On Right lamps 3 times  ==========*/
   bool AddRightBlinks(void)
            {
            //TRISIO = 0b00001011;
            //L_ch = 0;    // latch the Left out to off state
            R_ch_out = 1;
            //Bip();
            __delay_ms(300);
            R_ch_out = 0; 
            __delay_ms(500);
            R_ch_out = 1;
            //Bip();
            __delay_ms(300);
            R_ch_out = 0; 
            __delay_ms(500);
            R_ch_out = 1;
            //Bip();
            __delay_ms(300);
            R_ch_out = 0; 
            __delay_ms(100);
            return wasTurningRight = 0;
            }
    
    
     /*========  Turn On Left lamps 3 times  ==========*/
    bool AddLeftBlinks(void)
            {
            //TRISIO = 0b00001011;
            //R_ch = 0;    // latch the Right out to off state
            L_ch_out = 1; 
            //Bip();
            __delay_ms(300);
            L_ch_out = 0; 
            __delay_ms(500);
            L_ch_out = 1;
            //Bip();
            __delay_ms(300);
            L_ch_out = 0; 
            __delay_ms(500);
            L_ch_out = 1; 
            //Bip();
            __delay_ms(300);
            L_ch_out = 0; 
            __delay_ms(100);
            return wasTurningLeft = 0;
            }
    
     /*========  Turn On Reverse (Left and Right channels blink simultaneously)  ==========*/ 
    
   void ReversOn(void)
            {
            //TRISIO = 0b00001011;                    // Gp0, Gp1, Gp3 are always as inputs; Gp5 is always output; Gp2, Gp4 are as outputs for now 
                //Bip();
                //GPIO = 0b00010100; // L_ch = 1; R_ch = 1;
            __delay_ms(120);
                //GPIO = 0b00000000; // L_ch = 0; R_ch = 0;
            __delay_ms(500);        
            }
   

/*void interrupt ISR(void)
{
	if(T0IF)  //If Timer0 Interrupt
	{
		if(PWM_Pin)	// if PWM_Pin is high
		{
			PWM_Pin = 0;
			TMR0 = PWM;
		}
		else	     // if PWM_Pin is low
		{
			PWM_Pin = 1;
			TMR0 = 255 - PWM;
		}

		T0IF = 0;   // Clear the interrupt
	}
}

unsigned char PWM = 0;

void InitPWM(void)
{
	// Use timer0 for generatung PWM
    
    //OPTION_REG	=	0b10000111;	//set timer pre-scaler to 64/pre-scaler assigned to timer module 
		//	nGPPU = 1;		// internal pull-ups disabled
		//	INTEDG = 0;		// falling edge trigger the interrupt__don't care
		//	T0CS = 0;		// timer transition on cycle clock
		//	T0SE = 0		// increment on low to high transition of GP2
		//	PSA = 0			// pre-scaler is set to the TIMER0 module
		//  ps>>101, or 64 / 111, or 256; 110, or 128
	OPTION_REG &= 0xC0;     // or 0b11000000 Intialize timer0
	
	T0IE = 1;				// Enable Timer0 interrupt
	GIE = 1;				// Enable global interrupts
}

void StartBip(void)
{
    InitPWM();			 // Initialize PWM
    PWM = 250;
}

void StopBip(void)
{
    T0IE = 0;				// Disable Timer0 interrupt
    GIE = 0;				// Disable global interrupts
    PWM_Pin = 0;
}
*/