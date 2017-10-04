/*
  C3JR_Slave.h -- I2C <--> C3jr interface. 

  Justin Shaw
  LIBRARY DATED 11/9/2011

Licenced under Creative Commons Attribution.
Attribution 3.0 Unported
This license is acceptable for Free Cultural Works.
You are free:

    * to Share — to copy, distribute and transmit the work
    * to Remix — to adapt the work
    *

Under the following conditions:

    *

      Attribution — You must attribute the work in the manner specified by 
the author or licensor (but not in any way that suggests that they endorse
you or your use of the work).

      Attribute this work:
      Information
      What does "Attribute this work" mean?
      The page you came from contained embedded licensing metadata, including
how the creator wishes to be attributed for re-use. You can use the HTML here 
to cite the work. Doing so will also include metadata on your page so that 
others can find the original work as well.

With the understanding that:
    * Waiver — Any of the above conditions can be waived if you get permission 
      from the copyright holder.
    * Public Domain — Where the work or any of its elements is in the public 
      domain under applicable law, that status is in no way affected by the 
      license.
    * Other Rights — In no way are any of the following rights affected by the
      license:
          o Your fair dealing or fair use rights, or other applicable copyright
	    exceptions and limitations;
          o The author's moral rights;
          o Rights other persons may have either in the work itself or in how 
            the work is used, such as publicity or privacy rights.
    * Notice — For any reuse or distribution, you must make clear to others 
     the license terms of this work. The best way to do this is with a link 
     to this web page.
*/
#ifndef C3JR_Slave_H
#define C3JR_Slave_H

#include <inttypes.h>
#include "ClockTHREE.h"
#include "Wire.h"
#include "mem_font.h"

const uint8_t C3JR_BASE_ADDR = 78; // MADE UP NUMBER
const uint8_t C3JR_N_COL = 16; 
const uint8_t C3JR_SET_MSG = 1;
const uint8_t C3JR_SCROLL_LEFT_MSG = 2;
const uint8_t C3JR_SET_PIXEL_MSG = 3;
const uint8_t C3JR_SET_CHAR_MSG = 4;
const uint8_t C3JR_SCROLL_CHAR_V_MSG = 5;
const uint8_t C3JR_SCROLL_CHAR_H_MSG = 6;
const uint8_t C3JR_CLEAR_MSG = 7;
const uint8_t C3JR_SCROLL_V_MSG = 8;
const uint8_t C3JR_DISPLAY_ID_MSG = 9;
const uint8_t C3JR_TONE_MSG = 10;
const uint8_t C3JR_FADETO_MSG = 11;

const uint8_t C3JR_DBG_PIN = 1;

const uint8_t C3JR_ADDR_PINS[] = {8, 3, 15, 2};

class C3JR_Driver{
 public:
  C3JR_Driver();

  void init(uint8_t _addr);

  // send an entire display array to slave device
  void set_display(uint32_t *display);

  // scroll entire display one column to the left adding new col on right side
  void scroll_left(uint8_t new_col);

  // set a single pixel on slave high or low
  void set_pixel(uint8_t row, uint8_t col, bool val);

  // set an ASCII character on the slave
  void set_char(char c);

  // scroll an ASCII char in from top
  void scroll_char_v(char c);

  // scroll an ASCII cahr in from right
  void scroll_char_h(char c);

  // turn all LEDS off
  void clear();

  // scroll the display down n rows
  void scroll_v(uint8_t n_row);

  // display I2C ID (for debugging)
  void display_id();

  // fade to new display (to avoid abrupt changes)
  void fadeto(uint32_t *display, uint8_t steps);

  // fade to new display (to avoid abrupt changes)
  void fadeto(uint8_t *display, uint8_t steps);

  // helper routine
  void send_msg(uint8_t msg_id, uint8_t msg_len, uint8_t *msg); // helper function
private:
  uint8_t addr;
};
void C3JR_driver_onRequest();
void C3JR_driver_onReceive(int n_byte);

#endif
