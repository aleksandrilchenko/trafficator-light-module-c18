/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

#define AN0 1<<0 // 0b00000000
#define AN1 1<<1 // 0b00000010
#define AN2 1<<2 // 0b00000100
#define AN3 3<<3 // 0b00011000


   #define R_ch_in PORTAbits.AN0
   #define L_ch_in PORTAbits.AN1
   #define R_ch_out PORTAbits.RA4
   #define L_ch_out PORTBbits.RB0
   //#define _49A RA_bit
   #define Reverse PORTBbits.RB1
   #define PWM_Pin PORTBbits.RB2


/* TODO User level functions prototypes (i.e. InitApp) go here */


unsigned char wasTurningRight; // extern
unsigned char wasTurningLeft; // extern
unsigned char hazardIsOn; // extern
unsigned char PWM; // extern
unsigned char Channel;

int ADC2_value; // extern
int ADC3_value; // extern

// Function declarations
//void InitPWM(void);
void StartBip(void);
void StopBip(void);
void InitADC(unsigned char);         /* I/O and Peripheral Initialization */

//int GetADCValue(unsigned char);
//int GetCurrentValue(void);

//void InitInterrupt (void);
//void interrupt ISR(void);

//unsigned char TurnRight(void);
//unsigned char TurnLeft(void);
//unsigned char AddRightBlinks(void);
//unsigned char AddLeftBlinks(void);
//void ReversOn(void);
//unsigned char Turn_Hazard(void);