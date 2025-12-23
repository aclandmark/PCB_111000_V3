

//14 more projects very like those saved under            
//“0_project_zero” this time generating simple patterns on the display 
//some of them regular and repeating and some of them random.
//Why not copy the C code for one or two examples to be found in folder "C_file_images\1_first_project"



#include "First_project_header.h"



int main (void)       //Example 1
  { unsigned int PORT_1;

  setup_HW;
    PORT_1 = 1;
  for (int m = 0; m <= 15; m++)
  {  I2C_Tx_2_integers(PORT_1, PORT_1);
    Timer_T0_10mS_delay_x_m(12);
   PORT_1 = PORT_1 << 1;
   while(switch_1_down);
   }
  SW_reset; }





ISR (WDT_vect){
Reset_Atmega328;
Reset_I2C;}
  
