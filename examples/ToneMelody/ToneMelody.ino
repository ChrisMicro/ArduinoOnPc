/*
 * ToneMelody test for ArduinoOnPC
 *
 * use a linux pipe to aplay for sound output
 * 
 * 2019 February ChrisMicro
 *
 */

#define APLAY "aplay -q --file-type wav --format S16_LE"


#define SAMPLINGFREQUENCY 8000
#define BUFFERLENGTH SAMPLINGFREQUENCY*2 // buffer for 10 seconds

int16_t SignalBuffer[BUFFERLENGTH];

void tone(uint8_t pin, uint16_t frequency_Hz, uint32_t duration_ms)
{
  FILE *pipeDescriptor;
  int16_t signal;


  pipeDescriptor = popen(APLAY,"w");
  if (pipeDescriptor==NULL)
  {
    printf("Error opening pipe to aplay. Check if you have it! \n");
    exit(0);
  }

  uint32_t len=SAMPLINGFREQUENCY*duration_ms/1000;

  if(len>BUFFERLENGTH) len=BUFFERLENGTH; // limit size, prevent buffer overflow

  for(uint32_t n=0;n<len;n++)
  {
      signal = sin(2*PI*n*(float)frequency_Hz/SAMPLINGFREQUENCY)*32767; 
      SignalBuffer[n]=signal;
  }

  fwrite(SignalBuffer,sizeof(SignalBuffer[0]),len,pipeDescriptor);

  fclose(pipeDescriptor);
}

void setup() 
{

}

void loop() 
{  
  tone(8,440,1000);

  delay(1000);     

  for(int n=0;n<10;n++)  tone(8,440+n*100,100);        
}


