#include "ClockTHREE.h"
#include "german.h"

/* char text[12 * 16 + 1] = 
ES-IST-VIERTEL--
FUNF-ZWANZIGZEHN
VORNACH-HALB----
EINSZWEIDREI--- 
VIERFUNFSECHS-- 
SIEBENACHTZWOLF 
ZEHNELFNEUN-UHR 
AM-NACHMITTAGS- 
MORGENSABENDS---
IN-DER-NACHTS---
PETERSCLOCKTHREE
 YMTUMSALARM     
*/


void German::display_word(ClockTHREE c3, uint8_t color, 
			   const uint8_t *w){
  c3.horizontal_line(w[0], w[1], w[2], color);
}

void German::display_time(int YY, int MM, int DD, int hh, int mm, int ss, 
			   ClockTHREE c3, uint8_t color, uint8_t fade_steps
			   ){
  display_time(YY, MM, DD, hh, mm, ss, c3, color, fade_steps, (uint8_t)1, 
	       (uint8_t)1);
}

void German::display_time(int YY, int MM, int DD, int hh, int mm, int ss, 
			   ClockTHREE c3, uint8_t color, uint8_t fade_steps,
			   uint8_t its_flag, uint8_t minutes_hack_flag){
  uint8_t hour12;
  uint8_t hour24;
  uint8_t h_offset = 0;
  uint32_t *new_display = c3.display + N_COL;
  uint32_t *old_display;

  old_display = c3.setdisplay(new_display);
  // copy mono rows; clear rest
  for(int i = 0; i < N_COL; i++){
    new_display[i] = old_display[i] & 0xc0000000;
  }
  if(its_flag){
    display_word(c3, color, es);
    display_word(c3, color, ist);
  }

  if(0 <= mm && mm < 5){
    if(hh != 0){
      display_word(c3, color, uhr);
    }
  }
  else if(5 <= mm && mm < 10){
    display_word(c3, color, mfunf);
    display_word(c3, color, mnach);
    display_word(c3, color, uhr);
  }
  else if(10 <= mm && mm < 15){
    display_word(c3, color, mzehn);
    display_word(c3, color, mnach);
    display_word(c3, color, uhr);
  }
  else if(15 <= mm && mm < 20){
    display_word(c3, color, viertel);
    display_word(c3, color, mnach);
    display_word(c3, color, uhr);
  }
  else if(20 <= mm && mm < 25){
    display_word(c3, color, zwanzig);
    display_word(c3, color, mnach);
    display_word(c3, color, uhr);
  }
  else if(25 <= mm && mm < 30){
    display_word(c3, color, mfunf);
    display_word(c3, color, vor);
    display_word(c3, color, halb);
    h_offset = 1;
  }
  else if(30 <= mm && mm < 35){
    display_word(c3, color, halb);
    h_offset = 1;
  }
  else if(35 <= mm && mm < 40){
    display_word(c3, color, mfunf);
    display_word(c3, color, mnach);
    display_word(c3, color, halb);
    h_offset = 1;
  }
  else if(40 <= mm && mm < 45){
    display_word(c3, color, zwanzig);
    display_word(c3, color, vor);
    display_word(c3, color, uhr);
    h_offset = 1;
  }
  else if(45 <= mm && mm < 50){
    display_word(c3, color, viertel);
    display_word(c3, color, vor);
    display_word(c3, color, uhr);
    h_offset = 1;
  }
  else if(50 <= mm && mm < 55){
    display_word(c3, color, mzehn);
    display_word(c3, color, vor);
    display_word(c3, color, uhr);
    h_offset = 1;
  }
  else if(55 <= mm && mm < 60){
    display_word(c3, color, mfunf);
    display_word(c3, color, vor);
    display_word(c3, color, uhr);
    h_offset = 1;
  }
  hour24 = (hh + h_offset) % 24;
  hour12 = hour24 % 12;
  if(hour12 == 0){
    if(hour24 == 0 and mm < 5){
      // pass
    }
    else{
      display_word(c3, color, zwolf);
    }
  }
  else if(hour12 == 1){
    if(25 <= mm && mm < 40){
      display_word(c3, color, eins);
    }
    else{
      display_word(c3, color, ein);
    }
  }
  else if(hour12 == 2){
    display_word(c3, color, zwei);
  }
  else if(hour12 == 3){
    display_word(c3, color, drei);
  }
  else if(hour12 == 4){
    display_word(c3, color, vier);
  }
  else if(hour12 == 5){
    display_word(c3, color, ufunf);
  }
  else if(hour12 == 6){
    display_word(c3, color, sechs);
  }
  else if(hour12 == 7){
    display_word(c3, color, sieben);
  }
  else if(hour12 == 8){
    display_word(c3, color, acht);
  }
  else if(hour12 == 9){
    display_word(c3, color, neun);
  }
  else if(hour12 == 10){
    display_word(c3, color, uzehn);
  }
  else if(hour12 == 11){
    display_word(c3, color, elf);
  }
  if(0 <= hour24 && hour24 < 6){
    if(mm < 5){
      if(hour12 == 0){
	display_word(c3, color, mitter);	
	display_word(c3, color, nacht);	
      }
      else{
	display_word(c3, color, nachts);
      }
    }
    else{
      display_word(c3, color, in);
      display_word(c3, color, der);
      display_word(c3, color, nacht);
    }
  }
  else if(6 <= hour24  && hour24 < 12){
    if(mm < 5){
      display_word(c3, color, morgens);
    }
    else{
      display_word(c3, color, am);
      display_word(c3, color, morgen);
    }
  }
  else if(12 <= hour24  && hour24 < 13){
    if(mm < 5){
      display_word(c3, color, mittags);
    }
    else{
      display_word(c3, color, am);
      display_word(c3, color, mittag);
    }
  }
  else if(13 <= hour24  && hour24 < 17){
    display_word(c3, color, znach);
    if(mm < 5){
      display_word(c3, color, mittags);
    }
    else{
      display_word(c3, color, am);
      display_word(c3, color, mittag);
    }
  }
  else if(17 <= hour24  && hour24 < 23){
    if(mm < 5){
      display_word(c3, color, abends);
    }
    else{
      display_word(c3, color, am);
      display_word(c3, color, abend);
    }
  }
  else if(23 <= hour24  && hour24 < 24){
    if(mm < 5){
      display_word(c3, color, nachts);
    }
    else{
      display_word(c3, color, in);
      display_word(c3, color, der);
      display_word(c3, color, nacht);
    }
  }

  if(minutes_hack_flag){
    minutes_hack(c3, mm, ss);
  }
  c3.setdisplay(old_display);
  c3.fadeto(new_display, fade_steps);
  // copy new_display over
  for(int i = 0; i < N_COL; i++){
    old_display[i] = new_display[i];
  }
}

void German::minutes_hack(ClockTHREE c3, int mm, int ss){
  mm %= 5;
  uint8_t color, num;
  num = ss / 10;
  for(int i = 0; i < mm; i++){
    c3.setPixel(15, 4 + i, WHITE);
  }
  switch(num){
  case 0:
    color = BLUE;
    break;
  case 1:
    color = GREEN;
    break;
  case 2:
    color = RED;
    break;
  case 3:
    color = REDBLUE;
    break;
  case 4:
    color = REDGREEN;
    break;
  case 5:
    color = WHITE;
    break;
  }
  c3.setPixel(15, 4 + mm, color);
  // c3.setPixel(ss / 4, 10, BLUE);
  // c3.setPixel(ss / 4, 11, BLUE);
}
