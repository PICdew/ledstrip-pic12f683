#include <pic12f1572.h>
#include <stdint.h>

static __code uint16_t __at (_CONFIG1) configword1 = _FOSC_INTOSC & _WDTE_OFF & _MCLRE_ON & _CP_OFF & _PWRTE_OFF & _BOREN_OFF & _CLKOUTEN_OFF;
static __code uint16_t __at (_CONFIG2) configword2 = _WRT_OFF & _PLLEN_OFF & _PLLEN_OFF & _STVREN_ON & _DEBUG_OFF & _LVP_ON;
// _PLLEN_OFF : we are going to enable PLL on the fly in init

#define FOSC	32000000

void init() {
  OSCCON  = 0b11110000; // int osc: 8MHz x 4 (SPLLEN)
  PSA     = 1;          // no prescaler for timer0
  TMR0CS  = 0;          // Timer0 clock select: cpu clock

  INTCON  = 0;          // Clear interrupt flag bits
  GIE     = 0;          // Global irq disable
  T0IE    = 0;          // Timer0 irq disable
  TMR0    = 0;          // Clear timer0 register

  // switch off analog
  ANSELA  = 0;
  ADCON0  = 0;
  ADCON1  = 0;
  ADCON2  = 0;
  CM1CON0 = 0;
  CM1CON1 = 0;
}

void init_pwm() {
  PWM3CLKCON = 0b00000000; // no Prescale - FOSC
  PWM3PHL = 0;          // phase low
  PWM3PHH = 0;          // phase high
  PWM3DCL = 0xff;       // duty cycle low
  PWM3DCH = 0x7c;       // duty cycle high
                        // freq = FOSC / period = 32^6/64,00 = 500 Hz
  PWM3PRL = 0xff;       // period low
  PWM3PRH = 0xf9;       // period high
  PWM3CON = 0b11000000; // module enable, output enable, normal polarity, standard mode
}

void main() {
  init();

  // set PORTA5 & PORTA2 to output
  TRISA5 = 0;
  TRISA2 = 0;

  init_pwm();

  /* generates symetric 1 MHZ signal */
  while(1) {
    LATA5 = 1;
    LATA5 = 1;  // add 3 CPU cycles to generate symetric signal
    LATA5 = 1;  //
    LATA5 = 1;  //
    LATA5 = 0;
  }
}
