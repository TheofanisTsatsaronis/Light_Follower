int sensorMin0 = 1023;  int sensorMin1 = 1023;int sensorMin2 = 1023;
int sensorValue0;int sensorValue1;int sensorValue2;
int i=0;
int minimum;
void main ()
{
 //short duty1 = 160;
ADC_Init();
TRISD.TRISD1=0;
TRISD.TRISD0=0;
TRISC.TRISC1=0;
TRISC.TRISC2=0;
//rc1_bit = 1;
//rc2_bit = 1;
//CCP1CON=12;
//CCP2CON=12;
PWM1_Init(5000);  // Initialize PWM1
PWM2_Init(5000);  // Initialize PWM2

 //CCP1CON=0b00001111;
 //CCP2CON=0b00001111;
 //setup_timer_2(T2_DIV_BY_1,255,1);   // Set PWM frequency
   //setup_ccp1(CCP_PWM);          // Configure CCP1 to PWM mode
   //set_pwm1_duty(512L);
    //PWM1_Init(1000);
  //PWM2_Init(1000);
while(i<50000){
rd0_bit = 1;
rd1_bit = 1;
sensorValue0 = ADC_Read(0);
sensorValue1 = ADC_Read(1);
sensorValue2 = ADC_Read(2);
    if (sensorValue0 < sensorMin0) {
      sensorMin0 = sensorValue0;
    }
    if (sensorValue1 < sensorMin1) {
      sensorMin1 = sensorValue1;
    }
    if (sensorValue2 < sensorMin2) {
      sensorMin2 = sensorValue2;
    }


i++;
}
rd0_bit = 0;
rd1_bit = 0;
if (sensorMin0 <= sensorMin1 && sensorMin0 <= sensorMin2) {minimum=sensorMin0;}
else if (sensorMin1 <= sensorMin0 && sensorMin1 <= sensorMin2) {minimum=sensorMin1;}
else if (sensorMin2 <= sensorMin0 && sensorMin2 <= sensorMin1) {minimum=sensorMin2;}
else {minimum=sensorMin0;}
minimum=minimum-30;
//TRISA=0xFF;
//ADCON1 = 0x0F;
//CMCON = 0x07;
//TRISA.TRISA0=1;
//TRISA.TRISA1=1;
//TRISA.TRISA2=1;
//TRISA.TRISA3=1;
//TRISA=0xFF;
//ADCON1=0b00000110;
TRISB=0x00;
while(1){
       PWM1_Start();  // start PWM1
  PWM2_Start();  // start PWM2
   PWM1_Set_Duty(140); // deksi moter
  PWM2_Set_Duty(150); // aristero moter
      sensorValue0 = ADC_Read(0);
      sensorValue1 = ADC_Read(1);
      sensorValue2 = ADC_Read(2);
      if      (sensorValue1 < minimum && sensorValue1 < sensorValue0-50 && sensorValue1 < sensorValue2-50)  { //eutheia
      rd0_bit = 1;
      rd1_bit = 1;
      delay_ms(300);
      rb0_bit=0;
      rb1_bit=1;
      rb2_bit=0;
      rb3_bit=1;
      rd1_bit = 0;
      rd0_bit = 0;
      Delay_ms(1);
      //duty1++; // increment duty cycle
      //PWM1_Set_Duty(duty1); //Change the duty cycle
      //PWM2_Set_Duty(duty1); //Change the duty cycle
      }
      else if (sensorValue0 < minimum && sensorValue0 < sensorValue1-50 && sensorValue0 < sensorValue2-50 )   {  //aristera
      rd1_bit = 1;
      delay_ms(300);
      portb.b0=1;
      portb.b1=0;
      portb.b2=0;
      portb.b3=1;
       rd1_bit = 0;
       Delay_ms(1);
      //duty1++; // increment duty cycle
      //PWM1_Set_Duty(duty1); //Change the duty cycle
      //PWM2_Set_Duty(duty1); //Change the duty cycle
        }
      else if (sensorValue2 < minimum && sensorValue2 < sensorValue0-50  && sensorValue2 < sensorValue1-50  )   {//aristera
      rd0_bit = 1;
       rd1_bit = 0;
      portb.b0=0;
      portb.b1=1;
      portb.b2=1;
      portb.b3=0;
       delay_ms(300);
       rd1_bit = 0;
      rd0_bit = 0;
      Delay_ms(1);
      //duty1++; // increment duty cycle
      //PWM1_Set_Duty(duty1); //Change the duty cycle
      //PWM2_Set_Duty(duty1); //Change the duty cycle
        }
      else{     //stamatimeno
      portb.b3=0;
      portb.b2=0;
      portb.b1=0;
      portb.b0=0;
      Delay_ms(1);
      //duty1++; // increment duty cycle
      //PWM1_Set_Duty(duty1); //Change the duty cycle
      //PWM2_Set_Duty(duty1); //Change the duty cycle
      }

 }

}