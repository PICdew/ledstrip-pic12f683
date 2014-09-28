/*
changelog
  version  date    description
  -------  ------  -----------------------------------
  0.1      140830  1st running pulse width measurement
  1.0      140906  decoded ir nec frame
  1.1      140913  key codes array ledstrip_keys
  1.2      140927  merged with pwm code
todo
  colour sequences
  gamma correction
  ir repeat codes
*/

#include <pic12f683.h>
#include "ir2.h"
#include "ir2.c"

#define red    GP5
#define green  GP4
#define blue   GP1
#define on     0
#define off    1 
#define dn     0
#define up     1

unsigned char period    = 0;  // time for full pwm cycle
// unsigned char periods   = 0;  // number of passed periods
unsigned char dc_red    = 0;  // duty cycle 0..255
unsigned char dc_green  = 0;  // "
unsigned char dc_blue   = 0;  // "
unsigned char dir_red   = up; // fading direction
unsigned char dir_green = up; // fading direction
unsigned char dir_blue  = up; // fading direction

unsigned char update;

unsigned char led_state = 0;

uint8_t nec_address;
uint8_t nec_command;

uint8_t ledstrip_keys[]={
  0b00001001, 0b00011101, 0b00011111, 0b00001101,
  0b00011001, 0b00011011, 0b00010001, 0b00010101,
  0b00010111, 0b00010010, 0b00010110, 0b01001101,
  0b01000000, 0b01001100, 0b00000100, 0b00000000,
  0b00001010, 0b00011110, 0b00001110, 0b00011010,
  0b00011100, 0b00010100, 0b00001111, 0b00001100
};



//unsigned char led_state = 0;

typedef unsigned int config;
config __at 0x2007 __CONFIG = _CPD_OFF & _CP_OFF & _BOD_OFF  & _MCLRE_OFF & _PWRTE_ON & _WDT_OFF & _INTOSCIO;

static void isr(void) __interrupt 0 { // every 8us = 1/(8e6 / 4 / 16) / TMR0 count 240..255
  // if timer interrupt: reset timer and toggle green led

  // if capture/compare interrupt: update 'current_value' from CCP value
  if ( CCP1IF ) {
    ir_interrupt();
    CCP1IF = 0;
  }

  if ( TMR1IF ) { // 8e6[Hz]/4/8192 ~ 244[Hz]
    ir_timeout();
    TMR1IF = 0;
  }

  if ( T0IF ) {
    TMR0 = 210;
//    if(period == 255) periods++;
//    if(period <= dc_green){

    period++;

    if(period <= dc_green){
      green = off;
    }else{
      green = on;
    }
    if(period <= dc_blue){
      blue  = off;
    }else{
      blue  = on;
    }
    if(period <= dc_red){
      red   = off;
    }else{
      red   = on;
    }
    T0IF = 0;
  }

}

void main() {
  ir_init();
  ir_enable();

  GIE     = 1;    // Global irq enable

  update = 0;
  while(1) {
    if (ir_flags.decoded) {
      if (ir.type == IR_NEC) {
        //if((nec.irdata & 0x000000ff) == 0b00001000) { // polariod rc mirrored address
        if((nec.irdata & 0x000000ff) == 0b00000000) { // ledstrip rc mirrored address
          //if((nec.irdata & 0x00ff0000)>>16 == 0b00010001) { // polariod rc mirrored command key "1"
          //if((nec.irdata & 0x00ff0000)>>16 == 0b00010010) { // polariod rc mirrored command key "2"
          //if((nec.irdata & 0x00ff0000)>>16 == 0b00010011) { // polariod rc mirrored command key "3"
          if((nec.irdata & 0x00ff0000)>>16 == ledstrip_keys[4]){
            dc_red   = 255;
            dc_green = 0;
            dc_blue  = 0;
          }
          if((nec.irdata & 0x00ff0000)>>16 == ledstrip_keys[5]){
            dc_red   = 0;
            dc_green = 255;
            dc_blue  = 0;
          }
          if((nec.irdata & 0x00ff0000)>>16 == ledstrip_keys[6]){
            dc_red   = 0;
            dc_green = 0;
            dc_blue  = 255;
          }
        }
      }
      ir_enable();
    }
  }
}
