/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */

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

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

#define AN0 0b00000000
#define AN1 0b00000010
#define AN2 0b00000100
#define AN3 0b00011000
#define AN4 0b00101000 // chnge its value!!!!
#define AN5 0b00110000 // chnge its value!!!!
#define AN6 0b00111000 // chnge its value!!!!


/*bit 4-2 CHS<2:0>:Analog Channel Select bits
                                    000= Channel 0 (AN0) 
                                    001= Channel 1 (AN1) 
                                    010= Channel 2 (AN2) 
                                    011= Channel 3 (AN3) 
                                    100= Channel 4 (AN4) 
                                    101= Channel 5 (AN5) 
                                    110= Channel 6 (AN6)
                                    111= Unimplemented  
 
        case AN0:   ADCON0 |= 0b00000000; break; // set bit 4-2 to 000
        case AN1:   ADCON0 |= 0b00000100; break; // set bit 4-2 to 001
        case AN2:   ADCON0 |= 0b00001000; break; // set bit 4-2 to 010
        case AN3:   ADCON0 |= 0b00001100; break; // set bit 4-2 to 011
        case AN4:   ADCON0 |= 0b00010000; break; // set bit 4-2 to 100
        case AN5:   ADCON0 |= 0b00010100; break; // set bit 4-2 to 101
        case AN6:   ADCON0 |= 0b00011000; break; // set bit 4-2 to 110
 */


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
// extern unsigned char PWM;

extern int V_in_value;
extern int V_out_value;
extern int _49A_in_value;
extern int Reverse_in_value;
extern int R_ch_in_value0; 
extern int L_ch_in_value;

