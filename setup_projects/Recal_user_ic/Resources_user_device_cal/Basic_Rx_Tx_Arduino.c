
void I2C_Tx(char, char, char*);

void send_byte_with_Ack(char);
void send_byte_with_Nack(char);
char receive_byte_with_Ack(void);
char receive_byte_with_Nack(void);
void I2C_Tx_initiate_mode(char);




/**********************************************************************************************************************************************************************************/
char isCharavailable_A (int m){int n = 0;								//Version of isCharavailable_Basic() that uses the Arduino library
while (!(Serial.available())){n++;	wdr();			
if (n>8000) {m--;n = 0;}if (m == 0)return 0;}	
return 1;}	



/**********************************************************************************************************************************************************************************/
char waitforkeypress_A (void){											//Version of waitforkeypress_Basic() that uses the Arduino library
while (!(Serial.available()))wdr();	
return Serial.read(); }



/**********************************************************************************************************************************************************************************/
char wait_for_return_key_A(void){                  						//Returns key presses one at a time
char keypress,temp;
while(1){																//Remain in while loop until a character is received
if (isCharavailable_A(8)){												//Pauses but returns 1 immediately that a character is received
keypress = Serial.read();												//Skip if no character has been received 
break;}}																//Exit while loop when character has been read
if((keypress == '\r') || (keypress == '\n')){							//Detect \r\n, \r or \n and converts to \r
if (isCharavailable_A(1)){temp = Serial.read();}
keypress = '\r';}
return keypress;}



/**********************************************************************************************************************************************************************************/
void newline_A(void){Serial.write ("\r\n");}




/**********************************************************************************************************************************************************************************/
char decimal_digit_A (char data){											//Returns 1 if data is a character of 0 to 9 inclusive
if (((data > '9') || (data < '0')) )return 0;							//Otherwise return zero
else return 1;}



/*********************************************************************/
char hex_digit (char data){
switch(data){
case '0': case '1': case '2': case '3': case '4': case '5': case '6':
case '7': case '8': case '9': case 'A': case 'B': case 'C': case 'D':
case 'E': case 'F': return 1; break;
default: return 0; break;}}


void Hex_to_PC_A(long Hex_num, char * num_as_string, char next_char)
{
ltoa(Hex_num, num_as_string, 16);								//Long to askii
Serial.print(num_as_string);Serial.print(next_char);}




void Int_Num_to_PC_A
(long Int_num, char * num_as_string, char next_char)			//Same as Unsigned_Int_to_PC()
{
ltoa(Int_num, num_as_string, 10);								//Long to askii
Serial.print(num_as_string);Serial.print(next_char);}



long Hex_from_KBD(void){
char keypress, sign = '+';
long number;

do
{keypress =  waitforkeypress_A();} 
while ((!(hex_digit(keypress)))&& (keypress != '-'));//(non_hex_char(keypress));

newline_A(); Serial.write(keypress);

if(keypress == '-') {sign = '-'; number = 0;}

else {keypress -= '0';
if (keypress > 9)keypress -= 7;
number =  keypress;}

while(1){
if ((keypress = wait_for_return_key_A())  =='\r')break;
if (hex_digit (keypress))	
{Serial.write(keypress);
keypress -= '0';
if (keypress > 9)keypress -= 7;

number = number * 0x10 + keypress;}}

if(sign == '-')number*= -1;					
return number;}


