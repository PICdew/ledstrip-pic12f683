#include <pic12f1572.h>
#include <stdint.h>

static __code uint16_t __at (_CONFIG1) configword1 = _FOSC_INTOSC & _WDTE_OFF & _MCLRE_ON & _CP_OFF & _PWRTE_OFF & _BOREN_OFF & _CLKOUTEN_OFF;
static __code uint16_t __at (_CONFIG2) configword2 = _WRT_OFF & _PLLEN_ON & _STVREN_ON & _DEBUG_OFF & _LVP_ON;

uint8_t  result_width_h = 0;
uint8_t  result_width_l = 0;
uint16_t resultier;

void init() {
  INTCON  = 0;    // Clear interrupt flag bits
  GIE     = 1;    // Global irq enable
  IOCIE   = 1;    // interrupt on change enable
  IOCAN2  = 1;    // irq on negative edge (RA2/pin5)
  IOCAP2  = 1;    // irq on positive edge (RA2/pin5)

  // switch off analog
  ANSELA  = 0;
  ADCON0  = 0;
  ADCON1  = 0;
  ADCON2  = 0;
  CM1CON0 = 0;
  CM1CON1 = 0;

  IRCF3   = 1;    // rc osc 8MHz
  IRCF2   = 1;    // "
  IRCF1   = 1;    // "
  IRCF0   = 0;    // "

  TRISA5  = 0;    // output for red led     - pin2
  TRISA2  = 1;    // input  for ir receiver - pin5

  TMR1CS0 = 0;    // timer 1 use internal clock
  TMR1CS1 = 0;    // "

  T1CKPS0 = 1;    // prescaler 1:8
  T1CKPS1 = 1;    // "

  TMR1ON  = 1;    // start to count
}

void isr (void) __interrupt (1){
  GIE = 0;
  if(IOCIF){                // IOC?
    result_width_h = TMR1H;
    result_width_l = TMR1L;
    TMR1H          = 0;     // reset timer 1
    TMR1L          = 0;     // "
  }
  IOCAF = 0;
  GIE = 1;
}

void main() {
  init();

  while(1){
//    if(result_width_h > 20 && result_width_h < 255){
    resultier=result_width_h <<8 | result_width_l;
    if (resultier > 500){
      if (resultier < 600){
      LATA5 =  1;// just debugging
      LATA5 =  1;// just debugging
      LATA5 =  1;// just debugging
      LATA5 =  0;// just debugging
      result_width_h = 0;
      result_width_l = 0;
      }
    }
  }
}
