#include <pic12f1572.h>
#include <stdint.h>

static __code uint16_t __at (_CONFIG1) configword1 = _FOSC_INTOSC & _WDTE_OFF & _MCLRE_ON & _CP_OFF & _PWRTE_OFF & _BOREN_OFF & _CLKOUTEN_OFF;
static __code uint16_t __at (_CONFIG2) configword2 = _WRT_OFF & _PLLEN_OFF & _PLLEN_OFF & _STVREN_ON & _DEBUG_OFF & _LVP_ON;

void init() {
  INTCON  = 0;    // Clear interrupt flag bits
  GIE     = 1;    // Global irq enable
  IOCIE   = 1;    // interrupt on change enable
  IOCAN2  = 1;    // irq on negative edge (RA2/pin5)

  // switch off analog
  ANSELA  = 0;
  ADCON0  = 0;
  ADCON1  = 0;
  ADCON2  = 0;
  CM1CON0 = 0;
  CM1CON1 = 0;

  TRISA5 = 0;     // output for red led     - pin2
  TRISA2 = 1;     // input  for ir receiver - pin5
}

void isr (void) __interrupt (1){
  GIE = 0;
  if(IOCIF){      // IOC?
    if(IOCAN2){   // switch edge direction
      IOCAN2 = 0; // disable falling edge detection
      IOCAP2 = 1; // enable rising edge detection
      LATA5 =  0; // just debuging
    }else{
      IOCAN2 = 1; // enable falling edge detection
      IOCAP2 = 0; // disable rising edge detection
      LATA5 =  1; // just debugging
    }
  }
  IOCAF = 0;
  GIE = 1;
}

void main() {
  init();

  while(1);
}
