/*
todo
  repeat code
  timeout is 65535us (t1 ovf). Detect timing violations asap.
  detect timing violations on all edges
  ir_code_bit++ one time is enough
  ir_code_bit -> ir_code_bit_num
*/

#include <pic12f1572.h>
#include <stdint.h>

static __code uint16_t __at (_CONFIG1) configword1 = _FOSC_INTOSC & _WDTE_OFF & _MCLRE_ON & _CP_OFF & _PWRTE_OFF & _BOREN_OFF & _CLKOUTEN_OFF;
static __code uint16_t __at (_CONFIG2) configword2 = _WRT_OFF & _PLLEN_OFF & _STVREN_ON & _DEBUG_OFF & _LVP_ON;

volatile uint8_t  result_width_h      = 0;
volatile uint8_t  result_width_l      = 0;
volatile uint16_t result_width;
uint8_t           loop;
volatile uint8_t  state               = 0;
volatile uint8_t  ir_code_bit         = 255;
uint8_t           repeat              = 0;

typedef union {
  struct {
    uint8_t addr  : 8;
    uint8_t iaddr : 8;
    uint8_t cmd   : 8;
    uint8_t icmd  : 8;
  };
  uint32_t  b32;
}ir_code_t;

ir_code_t ir_code;

void init() {
  INTCON  = 0;    // Clear interrupt flag bits
  GIE     = 1;    // Global irq enable
  IOCIE   = 1;    // interrupt on change enable
  IOCAN2  = 1;    // irq on negative edge (RA2/pin5)
  //IOCAP2  = 1;    // irq on positive edge (RA2/pin5)
  PEIE    = 1;    // peripheral interrupt enable
  TMR1IE  = 1;    // irq on t1 overflow

  // switch off analog
  ANSELA  = 0;
  ADCON0  = 0;
  ADCON1  = 0;
  ADCON2  = 0;
  CM1CON0 = 0;
  CM1CON1 = 0;

  IRCF3   = 1;    // CPU 16MHz ( _PLLEN_OFF )
  IRCF2   = 1;    // "
  IRCF1   = 1;    // "
  IRCF0   = 1;    // "

  TRISA5  = 0;    // output for led / scope - pin2
  TRISA2  = 1;    // input  for ir receiver - pin5

  TMR1CS0 = 0;    // 4MHz (Fosc/4 -> 16MHz/4 ; timer 1 use internal clock)
  TMR1CS1 = 0;    // "

  T1CKPS0 = 1;    // prescaler 1:8
  T1CKPS1 = 1;    // "

  TMR1ON  = 1;    // start to count
}

void debug() { // just a pulse
  for(loop=0;loop<100;loop++) {
    LATA5 = 1;
  }
  LATA5 = 0;
}

void isr (void) __interrupt (1){
  GIE = 0;

  if(IOCAF2) { // interrupt on change on pin RA2 occured? (falling edge only / IOCAN2  = 1)
    result_width_h = TMR1H;
    result_width_l = TMR1L;
    TMR1H          = 0;     // reset timer 1
    TMR1L          = 0;     // "
    IOCAF2         = 0;     // reset irq flag
  }

  if(TMR1IF) { // timer1 ovf - illegal timing found
    state  = 0; // wait for trailer
    ir_code_bit = 255; // reset command register
    TMR1IF = 0; // reset irq flag
  }
  GIE = 1;
}


void main() {
  ir_code.b32 = 0;
  init();

  while(1){
  /*
    measured timings (32MHz CPU):
    header 13000 - 14000
    zero    1000 -  1200
    one     2200 -  2300

    devived timings (16MHz CPU):
    header  6500 -  7000
    zero     500 -   600
    one     1100 -  1150
    repeat 49000 - 59000
  */

    result_width = result_width_h << 8 | result_width_l;
    if(state == 0 && result_width > 6500 && result_width < 7000){ // state = 0 means headerfield
      state = 1; // set state to bitfield
    }
    if(state == 1 && result_width > 500 && result_width < 1150){ // state = 1 means bitfield
      if(result_width < 600){ // "0" found
        ir_code.b32 >>= 1;  // 3h of brain aking - it was ir_code.b32 >> 1 before ;-)
        ir_code_bit++;
      }
      if(result_width > 1100){ // "1" found
        ir_code.b32 >>= 1;
        ir_code.b32 |= 0x80000000;
        ir_code_bit++;
      }
      result_width_h = 0; // avoid multiple matches / don't use old measures
      result_width_l = 0; // "

      if(ir_code_bit == 31) { // last bit decoded / state = 2 means trailerfield
        state = 2; // set state to trailerfield
      }
    }
    if(state == 2 && result_width > 50000 && result_width < 60000) { // state = 2 means trailerfield
      // trailerpuls found
      state = 3; // set state to repeat
      debug();///////////////////
    }
    if(state == 3 && result_width > 49000 && result_width < 59000) { // state = 3 means waiting for repeat
      // repeat found
      repeat++;
    }
    if(state == 0){ // T1 ovf - no repeats anymore or error
      repeat = 0;
    }
    if(ir_code_bit == 31) { 
      if( (ir_code.addr ^ ir_code.iaddr == 0xFF) && (ir_code.cmd ^ ir_code.icmd == 0xFF) ) { // error correction
        if(ir_code.addr == 0){ // my original led strip remote uses addr=0
          // some application
//          debug();
        }
      }
    }
  }
}
