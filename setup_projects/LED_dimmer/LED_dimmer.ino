

#include "First_project_header.h"



int main (void)       //Example 1
  { unsigned int PORT_1;

  setup_HW;
    PORT_1 = 1;
  for (int m = 0; m <= 15; m++)
  {  I2C_Tx_2_integers(PORT_1, PORT_1);
    Timer_T0_10mS_delay_x_m(12);
   PORT_1 = PORT_1 << 1;
   }
  SW_reset; }
