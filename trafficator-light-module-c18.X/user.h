/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */

void hi_isr(void);
void Bip(const char *sound, int size);
void InitADC(unsigned char);         /* I/O and Peripheral Initialization */
int GetADCValue(unsigned char);
int GetCurrentValue(void);
bool GetDirection(void);
bool AddRightBlinks(void);
bool AddLeftBlinks(void);
bool Turn_49A(void);
void ReversOn(void);


extern unsigned char sample;
extern volatile int wait;


/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

#define AN0 0b00000001
#define AN1 0b00000010
#define AN2 0b00000100
#define AN3 0b00011000
#define AN4 0b00101000 // chnge its value!!!!
#define AN5 0b00110000 // chnge its value!!!!
#define AN6 0b00111000 // chnge its value!!!!

    #define V_in        PORTAbits.AN1
    #define V_out       PORTAbits.AN0
    #define R_ch_in     PORTAbits.AN3
    #define L_ch_in     PORTAbits.AN5
    #define Reverse_in  PORTBbits.AN6

    #define R_ch_out    PORTAbits.RA2
    #define L_ch_out    PORTBbits.RB0
    #define _49A_out    PORTBbits.RB3
    #define PWM_Pin     PORTBbits.RB6 //PWM P1C channel // RB5 must be input in Z-state
    #define _49A_in     PORTAbits.RA4 //discrete input


extern bool wasTurningRight;
extern bool wasTurningLeft;

extern int V_in_value;
extern int V_out_value;
extern int _49A_in_value;
extern int Reverse_in_value;
extern int R_ch_in_value0; 
extern int L_ch_in_value;

