

void I2C_Tx(char, char, char*);
unsigned int PRN_16bit_GEN(unsigned int, unsigned char*);



void I2C_Tx_initiate_mode(char);
void I2C_Tx(char, char, char*);
void send_byte_with_Ack(char);
void send_byte_with_Nack(char);
char receive_byte_with_Ack(void);
char receive_byte_with_Nack(void);
void I2C_Rx_RN(unsigned long *, signed char *);		//Real numbers only


void I2C_Tx_initiate_mode(char mode){
char num_bytes = 0;
waiting_for_I2C_master;		
send_byte_with_Ack(num_bytes);
send_byte_with_Nack(mode);
TWCR = (1 << TWINT);}



/***********************************************************/
void I2C_Tx(char num_bytes, char mode, char s[]){
waiting_for_I2C_master;
send_byte_with_Ack(num_bytes);
send_byte_with_Ack(mode);
for (int m = 0;  m < num_bytes; m++){
if (m==num_bytes-1){send_byte_with_Nack(s[m]);}
else {send_byte_with_Ack(s[m]);}}
TWCR = (1 << TWINT);}										//Clear interrupt and close I2C slave


/***********************************************************/
void send_byte_with_Ack(char byte){
TWDR = byte;											//Send payload size: Zero in this case
TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);		//clear interrupt and set Enable Acknowledge
while (!(TWCR & (1 << TWINT)));}

/***********************************************************/
void send_byte_with_Nack(char byte){
TWDR = byte;										//Send payload size: Zero in this case
TWCR = (1 << TWINT) | (1 << TWEN);		//clear interrupt and set Enable Acknowledge
while (!(TWCR & (1 << TWINT)));}

/***********************************************************/
char receive_byte_with_Ack(void){
char byte;
TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT);		//Set Ack enable and clear interrupt
while (!(TWCR & (1 << TWINT)));						//Wait for interrupt
byte = TWDR;
return byte;}

/***********************************************************/
char receive_byte_with_Nack(void){
char byte;
TWCR = (1 << TWEN) | (1 << TWINT);		//Set Ack enable and clear interrupt
while (!(TWCR & (1 << TWINT)));						//Wait for interrupt
byte = TWDR;
return byte;}

/***********************************************************/


/************************************************************************/
void I2C_Tx_2_integers(unsigned int s1, unsigned int s2){			
char num_bytes=4; char mode = 1; char s[4];
for (int m = 0;  m < 4; m++){
switch (m){
case 0: s[m] = s1; break; 											//Send S1 lower byte
case 1: s[m] = s1 >> 8; break; 									//Send S1 higher byte									
case 2: s[m] = s2; 	break;											//Send S1 lower byte
case 3: s[m] = s2 >> 8; break;}}									//Send S1 higher byte
I2C_Tx(num_bytes,mode, s);}





/************************************************************************/
void I2C_Tx_display(void){


   unsigned int PORT_1 = 1;
  char m = 1;
  char overflow = 0;

    for(int p = 0; p < 16; p++){
   I2C_Tx_2_integers(PORT_1, ~PORT_1);
    
    Timer_T1_sub(T1_delay_100ms);
	
	
    if (m <= 5)
    {
      PORT_1 |= (PORT_1 << 1);
      m += 1;
    wdr();}
    else PORT_1 = PORT_1 << 1;
    if (overflow)PORT_1 |= 1;
    if (PORT_1 & 0x8000) overflow = 1;
    else overflow = 0;  }}  



/************************************************************************/
void I2C_Tx_LED_dimmer(void){
char Dimmer_control;

Dimmer_control = 0;

if ((PIND & 0x04) && (PINB & 0x40) && (PIND & 0x80)) Dimmer_control = 0;				//No user switches pressed

if(((PIND & 0x04)^0x04) && ((PINB & 0x40)^0x40) && (PIND & 0x80))Dimmer_control = 1;		//sw1 and sw2 pressed

if(((PIND & 0x04)^0x04) && (PINB & 0x40) && ((PIND & 0x80)^0x80))Dimmer_control = 2;		//sw1 and sw3 pressed

if ((PIND & 0x04) && ((PINB & 0x40)^0x40) && ((PIND & 0x80)^0x80))Dimmer_control = 3;	//sw2 and sw3 pressed

I2C_Tx(1, 'Q', &Dimmer_control);}


/************************************************************************/
void I2C_TX_328_check(void){			//NEEDED:	Tests to see whether or not user wants to chech version info
char num_bytes=0;						//or test clock calibration 
char mode = 'V';

waiting_for_I2C_master;		
send_byte_with_Ack(num_bytes);
send_byte_with_Nack(mode);
TWCR = (1 << TWINT) | (1 << TWEN);		//clear interrupt and leave I2C slave active
TWCR |= (1 << TWEA) | (1 << TWIE);} 	//Slave mode with interrupt and Enable Acknowledge



/************************************************************************/



