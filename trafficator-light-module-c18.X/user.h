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

    #define V_in        PORTAbits.AN0
    #define V_out       PORTAbits.AN1
    #define R_ch_in     PORTAbits.AN2
    #define L_ch_in     PORTAbits.AN3
    #define _49A_in     PORTBbits.AN4
    #define Reverse_in  PORTBbits.AN5

    #define R_ch_out    PORTAbits.RA4
    #define L_ch_out    PORTBbits.RB4
    #define _49A_out    PORTAbits.RA6
    #define PWM_Pin     PORTAbits.RA7


extern bool wasTurningRight;
extern bool wasTurningLeft;

extern int V_in_value;
extern int V_out_value;
extern int _49A_in_value;
extern int Reverse_in_value;
extern int R_ch_in_value0; 
extern int L_ch_in_value;

