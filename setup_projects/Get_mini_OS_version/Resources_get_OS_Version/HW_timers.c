


void Timer_T0_10mS_delay_x_m(int);
void Timer_T0_sub(char, unsigned char);
void Timer_T1_sub(char, unsigned int);



/*********************************************************************/
#define T0_delay_10ms 	5,178
#define T1_delay_100ms 	3, 0x9E62



/*********************************************************************/
void Timer_T1_sub(char Counter_speed, unsigned int Start_point){ 
TCNT1H = (Start_point >> 8);
TCNT1L = Start_point & 0x00FF;
TIFR1 = 0xFF;
TCCR1B = Counter_speed;
while(!(TIFR1 & (1<<TOV1)))wdr();
TIFR1 |= (1<<TOV1); 
TCCR1B = 0;}



/*********************************************************************/
void Timer_T0_10mS_delay_x_m(int m)
{for (int n = 0; n < m; n++){Timer_T0_sub(T0_delay_10ms);wdr();}}



/*********************************************************************/
void Timer_T0_sub(char Counter_speed, unsigned char Start_point){ 
TCNT0 = Start_point;
TCCR0B = Counter_speed;
while(!(TIFR0 & (1<<TOV0)));
TIFR0 |= (1<<TOV0); TCCR0B = 0;}


