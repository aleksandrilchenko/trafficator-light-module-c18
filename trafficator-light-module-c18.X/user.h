/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */
void InitInterrupt(void);
void play (const char *sound, int size);
//void InitADC(unsigned char);         /* I/O and Peripheral Initialization */
int GetADCValue(unsigned char);
int GetCurrentValue(void);
int GetDirection(void);
void AddRightBlinks(void);
void AddLeftBlinks(void);
int Turn_49A(void);
void ReversOn(void);

extern unsigned char sample;
extern volatile int wait;
void pause(int cycles);


/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

#define _XTAL_FREQ 8000000  // 8MHZ internal crystal

#define _AN0 0b00000001
#define _AN1 0b00000010
#define _AN2 0b00000100
#define _AN3 0b00011000
#define _AN4 0b00101000 // chnge its value!!!!
#define _AN5 0b00110000 // chnge its value!!!!
#define _AN6 0b00111000 // chnge its value!!!!


/*extern unsigned char _AN0;
extern unsigned char _AN1;
extern unsigned char _AN2;
extern unsigned char _AN3;
extern unsigned char _AN4;
extern unsigned char _AN5;
extern unsigned char _AN6;
*/


    //#define V_in        PORTAbits.AN1 // RA1
    //#define V_out       PORTAbits.AN0 // RA0
    //#define R_ch_in     PORTAbits.AN3 // RA3
    //#define L_ch_in     PORTAbits.AN5 // RB1
    //#define Reverse_in  PORTBbits.AN6 // RB4
    //#define _49A_in     PORTAbits.AN2 // RA2
                       // PORTBbits.AN4 // RB0


    #define R_ch_out    (LATAbits.LATA6)
    #define L_ch_out    (LATBbits.LATB0)
    #define _49A_out    (LATBbits.LATB2)
    //#define PWM_Pin     PORTBbits.RB3 //PWM P1C channel // RB5 must be input in Z-state



#define FOSC	8000000UL
#define T2_FREQ	(11000)		// Between 8000Hz and 11025Hz (same as the WAV file)
#define K_TMR2	 (FOSC/4)/(T2_FREQ) 
#define ON  1
#define OFF 0

extern int _direction;
//extern int V_in_value;
//extern int V_out_value;
//extern int _49A_in_value;
extern int Reverse_in_value;
//extern int R_ch_in_value; 
//extern int L_ch_in_value;
