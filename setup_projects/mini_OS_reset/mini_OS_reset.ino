

//14 more projects very like those saved under            
//“0_project_zero” this time generating simple patterns on the display 
//some of them regular and repeating and some of them random.
//Why not copy the C code for one or two examples to be found in folder "C_file_images\1_first_project"



#include "First_project_header.h"

volatile long PORT_1;
volatile char timer_counter=0;
volatile unsigned char char_offset = 0;

int main (void)       //Example 1
  { 
char keypress;
  setup_HW;
  
if (((eeprom_read_byte((uint8_t*)0x11)) == 0xFF) && ((eeprom_read_byte((uint8_t*)0x10)) == 0xFF))PORT_1 = 1;

else {PORT_1 = (((eeprom_read_byte((uint8_t*)0x11))  << 8) | (eeprom_read_byte((uint8_t*)0x10)));
eeprom_write_byte((uint8_t*)(0x11),0xFF);eeprom_write_byte((uint8_t*)(0x10),0xFF);}


if((eeprom_read_byte((uint8_t*)0x12)) == 0xFF)char_offset = 0;
else {char_offset =  eeprom_read_byte((uint8_t*)0x12); eeprom_write_byte((uint8_t*)(0x12),0xFF);}



I2C_Tx_2_integers(PORT_1, PORT_1);

Timer_T1_sub(T1_delay_100ms);Timer_T1_sub(T1_delay_100ms);Timer_T1_sub(T1_delay_100ms);Timer_T1_sub(T1_delay_100ms);



       
Thirty_two_ms_WDT_with_interrupt;
set_up_PCI_on_sw2;
 enable_pci_on_sw2;
  sei();
  while(1){
  keypress = 0;
  
  for (int m = 0; m <= 15; m++)
  {  I2C_Tx_2_integers(PORT_1, PORT_1);
    Timer_T0_10mS_delay_x_m(6);

I2C_initiate_7_8125mS_ref();
for (int p = 0; p < 30; p++){

waiting_for_I2C_master;                               //Energise  slave I2C and wait for master
send_byte_with_Nack(1);                               //Master will respond by staying in mode P
if(keypress != 'y')
clear_I2C_interrupt;}
waiting_for_I2C_master;
send_byte_with_Nack(0);
  clear_I2C_interrupt;
  Char_to_PC_Basic('!' + char_offset%25); char_offset++;

    if(PORT_1 == 0x8000)PORT_1 = 1;
  else PORT_1 = PORT_1 << 1;
  
   
  if (UCSR0A & (1 << RXC0))keypress = Char_from_PC_Basic();
  if(keypress == 'x'){cli();wdt_enable(WDTO_500MS);while(1);}

  if(keypress == 'y')crash_mini_OS();

  
         // Neeeds to be in ISR
   }}
  SW_reset; }



ISR(PCINT0_vect)
{ if(switch_2_down)SW_reset;
}






ISR (WDT_vect){ 

if(PORT_1 == 0x8000)PORT_1 = 1;
 eeprom_write_byte((uint8_t*)(0x10),PORT_1); 
 eeprom_write_byte((uint8_t*)(0x11),PORT_1 >> 8); 
 eeprom_write_byte((uint8_t*)(0x12),char_offset);


DDRB |= (1 << DDB4);
PORTB &= (~(1 << PORTB4));      //MISO output / input
PORTC |= (1 << PC3);            //Mini-OS reset control
DDRC |= (1 << PC3);
_delay_ms(1);
PORTC &= (~((1 << PC3)));
_delay_ms(1);
PORTC |= (1 << PC3);
while(1);}

/*
ISR (WDT_vect){ 
if(PORT_1 == 0x8000)PORT_1 = 1;
 eeprom_write_byte((uint8_t*)(0x10),PORT_1); 
 eeprom_write_byte((uint8_t*)(0x11),PORT_1 >> 8); 
 eeprom_write_byte((uint8_t*)(0x12),char_offset);

DDRB |= (1 << DDB4);
PORTB &= (~(1 << PORTB4));      //MISO output / input
PORTC |= (1 << PC3);            //Mini-OS reset control
DDRC |= (1 << PC3);
_delay_ms(1);
PORTC &= (~((1 << PC3)));
_delay_ms(1);
PORTC |= (1 << PC3);
while(1);}
*/
  
