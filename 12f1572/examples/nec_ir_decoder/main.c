#include <pic12f1572.h>
#include <stdint.h>

static __code uint16_t __at (_CONFIG1) configword1 = _FOSC_INTOSC & _WDTE_OFF & _MCLRE_ON & _CP_OFF & _PWRTE_OFF & _BOREN_OFF & _CLKOUTEN_OFF;
static __code uint16_t __at (_CONFIG2) configword2 = _WRT_OFF & _PLLEN_ON & _STVREN_ON & _DEBUG_OFF & _LVP_ON;

uint8_t  result_width_h = 0;
uint8_t  result_width_l = 0;
uint16_t resultier;
uint8_t  loop;
uint8_t  nec_first=0;
uint8_t  state=0;
uint32_t ir_code=0;
uint8_t  ir_code_bit=0;

void init() {
  INTCON  = 0;    // Clear interrupt flag bits
  GIE     = 1;    // Global irq enable
  IOCIE   = 1;    // interrupt on change enable
  IOCAN2  = 1;    // irq on negative edge (RA2/pin5)
  //IOCAP2  = 1;    // irq on positive edge (RA2/pin5)

  // switch off analog
  ANSELA  = 0;
  ADCON0  = 0;
  ADCON1  = 0;
  ADCON2  = 0;
  CM1CON0 = 0;
  CM1CON1 = 0;

  IRCF3   = 1;    // CPU 32MHz (rc osc 8MHz * 4 by PLL)
  IRCF2   = 1;    // "
  IRCF1   = 1;    // "
  IRCF0   = 0;    // "

  TRISA5  = 0;    // output for red led     - pin2
  TRISA2  = 1;    // input  for ir receiver - pin5

  TMR1CS0 = 0;    // 8MHz (Fosc/4 -> 32MHz/4 ; timer 1 use internal clock)
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
// verified timings:
// header 13000 - 14000
// zero    1000 -  1200
// one     2200 -  2300
//    if(result_width_h > 20 && result_width_h < 255){
    resultier=result_width_h <<8 | result_width_l;
    if(resultier > 13000 && resultier < 14000){ // header state = 0b1
      state = 0b1;
    }
    if(state == 0b1 && resultier > 1000 && resultier < 2300){ // bitfields state = 0b10
      state << 1;
      if(resultier < 1200){ // zero found
        ir_code << 1;
        ir_code_bit++;
      }
      if(resultier > 2200){ // one found
        ir_code << 1;
        ir_code |= 0x1;
        ir_code_bit++;
      }
    }else{
      state = 0;
    }
    if(state == 0b10 && ir_code_bit == 31){ // trailer state = 0b100
      state << 1;
      if(resultier > 1000 && resultier < 1200){
        state << 1; // successfully decoded -> state = 0b1000
      }
    }

// debug only
    if (state == 0b10 && ir_code_bit == 1){
      if(ir_code & 0b1){
        for(loop=0;loop<100;loop++) {
          LATA5 = 1;// just debugging
        }
        LATA5 = 0;// just debugging
        result_width_h = 0;
        result_width_l = 0;
        state = 0;
      }
    }
  }
}
