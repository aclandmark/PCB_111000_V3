
#define T0_delay_10ms 	5,178

void Timer_T0_sub(char, unsigned char);
void String_to_PC_Basic(const char *);
void I2C_Tx(char , char mode, char *);
void send_byte_with_Ack(char);
void send_byte_with_Nack(char);


/*********************************************************************/
void setup_PC_comms_Basic (unsigned char UBRROH_N, unsigned char UBRR0L_N ){
UCSR0B = 0;
UBRR0H = UBRROH_N;  									
UBRR0L = UBRR0L_N;  								
UCSR0A = (1 << U2X0);
UCSR0B = (1 << RXEN0) | (1<< TXEN0);
UCSR0C =  (1 << UCSZ00)| (1 << UCSZ01);}



/**********************************************************************************************************************************************************************************/
void Char_to_PC_Basic(char data){														
while (!(UCSR0A & (1 << UDRE0)));										//Wait for transmit buffer to be ready to accept new data
UDR0 = data;}															//Load data register with "data" and it will immediately be transmitted



/**********************************************************************************************************************************************************************************/
void newline_Basic(void){String_to_PC_Basic ("\r\n");}



/**********************************************************************************************************************************************************************************/
void String_to_PC_Basic(const char s[]){								//Transmits a sequence (string) of characters and requires the address in program memory of the first one
int i = 0;																//"i" gives the relative address of the next character to be transmitted
while(i < 200){															//Transmits up to 200 characters using "Char_to_PC()" or untill the null (\0) character is detected
if(s[i] == '\0') break;
Char_to_PC_Basic(s[i++]);}}												//Transmit character and increment "i" so that it addresses (points to) the next one.





/*********************************************************************/
char waitforkeypress_Basic (void){										//Wait here indefinitely but prevent WDTime-out
while (!(UCSR0A & (1 << RXC0)))wdr();	
return UDR0;}		





/************************************************************************/
void PCB_test (char test_num, char test_digit){
char s[2]; char num_bytes=2; char mode = 'O';
s[0] = test_num;
s[1] = test_digit;
I2C_Tx(num_bytes, mode, s);}





/************************************************************************/
void I2C_Tx_any_segment_clear_all(void){
char segment = 'a'; char digit_num = 0;
char s[2]; char num_bytes=2; char mode = 2;
s[0] = segment;
s[1] = digit_num; 
I2C_Tx(num_bytes,mode, s);}




/*********************************************************************/
void Timer_T0_10mS_delay_x_m(int m)
{for (int n = 0; n < m; n++){Timer_T0_sub(T0_delay_10ms);wdr();}}

/*********************************************************************/
void Timer_T0_sub(char Counter_speed, unsigned char Start_point){ 
TCNT0 = Start_point;
TCCR0B = Counter_speed;
while(!(TIFR0 & (1<<TOV0)));
TIFR0 |= (1<<TOV0); TCCR0B = 0;}



/***********************************************************/
void I2C_Tx(char num_bytes, char mode, char s[]){
waiting_for_I2C_master;
send_byte_with_Ack(num_bytes);
send_byte_with_Ack(mode);
for (int m = 0;  m < num_bytes; m++){
if (m==num_bytes-1){send_byte_with_Nack(s[m]);}
else {send_byte_with_Ack(s[m]);}}
TWCR = (1 << TWINT);}		




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
