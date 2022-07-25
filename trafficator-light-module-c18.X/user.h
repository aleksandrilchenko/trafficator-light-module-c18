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
#define AN4 4<<3 // chnge its value!!!
#define AN5 5<<3 // chnge its value!!!


    #define V_in        PORTAbits.AN0
    #define V_out       PORTAbits.AN1
    #define R_ch_in     PORTAbits.AN2
    #define L_ch_in     PORTAbits.AN3
    #define _49A_in     PORTBbits.AN4
    #define Reverse_in  PORTBbits.AN5

    #define R_ch_out    PORTAbits.RA4
    #define L_ch_out    PORTBbits.RB4
    #define _49A_out        PORTAbits.RA6
    #define PWM_Pin     PORTAbits.RA7


/* TODO User level functions prototypes (i.e. InitApp) go here */


extern bool wasTurningRight; // extern
extern bool wasTurningLeft; // extern
//unsigned char PWM; // extern
//extern unsigned char Channel;

extern int V_in_value;
extern int V_out_value;

// Function declarations
//void InitPWM(void);
//void Bip(void);
void InitADC(unsigned char);         /* I/O and Peripheral Initialization */
int GetADCValue(unsigned char);
int GetCurrentValue(void);
bool GetDirection(void);
bool AddRightBlinks(void);
bool AddLeftBlinks(void);
bool Turn_49A(void);
void ReversOn(void);

//void InitInterrupt (void);
//void interrupt ISR(void);