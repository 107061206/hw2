 #include "mbed.h"


Serial pc( USBTX, USBRX );

AnalogOut Aout(DAC0_OUT);

AnalogIn Ain(A0);


DigitalIn  Switch(SW3);

DigitalOut redLED(LED1);

DigitalOut greenLED(LED2);


BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);

char table[20] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,
                  0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87, 0xFF, 0xEF};

int sample = 2048;

int i,j;

int a = 0;
int b = 0;
int fq = 0;
int n[3];


float ADCdata[2048];


int main()
{

  for (i = 0; i < sample; i++)
  {

    //Aout = Ain;

    ADCdata[i] = Ain;

    wait(1./sample);

  }

  for (i = 0; i < sample; i++)
  {

    pc.printf("%1.3f\r\n", ADCdata[i]);

    wait(1./sample);

  }

  for (i = 0; i < sample && (a == 0 || b == 0); i++)
  {
    if( ADCdata[i] <= 0.0021 )
    {
      a = i;
    }

    if( ADCdata[i] >= 0.5935 )
    {
      b = i;
    }

  }

  if( a > b )
  {
    fq = 1024/ (a - b);
  }
  if( b > a )
  {
    fq = 1024/ (b - a);
  }

  n[0] = fq / 100;
  n[1] = (fq % 100)/10;
  n[2] = (fq % 100) % 10;

  while(1)
  {
        
        

          if( Switch == 1 )
          {
          
            greenLED = 0;
            redLED = 1;
            display = 0;

             
          }

          else
          {

            redLED = 0;

            greenLED = 1;
            for (i = 0; i < 3; i++)
            {

            if( i == 2)
            {
              display = table[n[i]+10];
              wait(1);
            }
            else
            {
                display = table[n[i]];
                wait(1);
            }
            }
          } 

          for ( i = 0; i < sample ; i++)
          {
            Aout = ADCdata[i];
            wait(1./2048);
          }    
  }


}