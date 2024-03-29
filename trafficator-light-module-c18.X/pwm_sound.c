/* ***********************************************************************
 *
 * This function will enable a PIC to play sounds using PWM
 *
 * Sound is encoded in PCM with 8 bits per sample and a sampling 
 * frequency between 8000Hz and 31250Hz. Above 31,25KHz the resolution of the 
 * PWM will decrease.
 *
 * As is this program will include ok-sound.h containing the voice of
 * someone saying "OK".
 * 
 * To use this program with other sounds it is necessary to create an header
 * file (.h) with the desired sound, formatted as a const char samples[].
 * 
 * To create a new header file do the following:
 *   Save the sound to a WAV file with the correct formar (ie: 8bits, 8000Hz, mono)
 *   Strip the wave header from the WAV file using mplayer
 *     (ie: mplayer yoursound.wav -ao pcm:nowaveheader:file=yoursound.pcm)
 *   Create the new header file (yoursound.h) from yoursound.pcm using 'pcm2h'
 *     (ie: pcm2h yoursound.pcm yoursound.h)
 *   On this file change the include from ok-sound.h to yoursound.h:
 *     #include "ok-sound.h"
 *     #include "yoursound.h"
 *   On this file change the play(okay, 5399); line to match the name of the array
 *   inside yoursound.h file and its length.
 *
 *   Finally, recompile and load to the PIC flash memory.
 * 
 * ***********************************************************************/
 
 
/* 
 *
 * This PIC sound player will play an "OK" sound sample.
 *
 * The original file can be found on the CDROM named 
 * "CD MIDI & WAVE WORKSHOP" from PowerSource.
 *
 */

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
/******************************************************************************/
/* pwm_sound Functions                                                             */
/******************************************************************************/

volatile int wait;



void setPWM(unsigned char sample)
{
    // set the bits into the modulator registers
	CCPR1L = sample >> 2;
	DC1B1 = (sample&0x02)>>1;
	DC1B0 = (sample&0x01);
}
void play(const char *sound, int size)
{
	InitInterrupt();
    int i;
	for(i=0; i<size; i++)
	{
        // feed next sound sample to the PWM modulator
		setPWM(sound[i]);
		
        // wait for time to feed next sound sample to the PWM modulator
        wait=1;
		while(wait);
	}
    PEIE = 0;			// Disable Low Priority Interrupts
	GIE=0;				// Disable High Priority Interrupts
    TMR2IF = 0;		// Clear the interrupt flag
	TMR2IE = 0;		// Disable timer 2 interrupt (not necessary for the PWM)
	TMR2ON = 0;		// Stop the timer and the PWM modulation!
}
		
/*void pause(int cycles)
{
	setPWM(0);
	wait=cycles;
	while(wait);
}*/

// --------------------------------------------------------------------------
//
