#include <pic12f1572.h>
#include <stdint.h>

static __code uint16_t __at (_CONFIG1) configword1 = _FOSC_INTOSC & _WDTE_OFF & _MCLRE_ON & _CP_OFF & _PWRTE_OFF & _BOREN_OFF & _CLKOUTEN_OFF;
static __code uint16_t __at (_CONFIG2) configword2 = _WRT_OFF & _PLLEN_OFF & _PLLEN_OFF & _STVREN_ON & _DEBUG_OFF & _LVP_ON;
// _PLLEN_OFF : we are going to enable PLL on the fly in init

#define FOSC	32000000

void init() {
  OSCCON = 0b11110000; // int osc: 8MHz x 4 (SPLLEN)
  PSA    = 1; // No prescaler for timer0
  T0CS   = 0; // Timer0 clock select: cpu clock

  INTCON = 0; // Clear interrupt flag bits
  GIE    = 0; // Global irq enable
  T0IE   = 0; // Timer0 irq enable
  TMR0   = 0; // Clear timer0 register

  // switch off analog
  ANSELA = 0;
  ADCON0 = 0;
  ADCON1 = 0;
  ADCON2 = 0;
  CM1CON0 = 0;
  CM1CON1 = 0;
}

void main() {
  init();

  // set PORTA5 to output
  TRISA5 = 0;

  while(1) {
    LATA5 = 1;
    LATA5 = 1;  // two CPU cycles more for the loop goto
    LATA5 = 1;
    LATA5 = 1;
    LATA5 = 0;
  }
}
