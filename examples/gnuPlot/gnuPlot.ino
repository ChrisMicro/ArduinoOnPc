
/*
  gnuplot
 
  use a linux pipe to gnuplot to visualize data
  

  v0.1  14 Feb 2019 ChrisMicro  initial version
 
 */

FILE *pipe=NULL;

void plot(double y[],int32_t length)
{
  if(pipe==NULL)
  {
    pipe = popen("gnuplot -persist","w"); 
    if (pipe==NULL)
    {
      printf("gnuplot missing ...  \n");
    }
    delay(100);

  }
  if(pipe!=NULL)
  {
    fprintf(pipe, "set title 'sine wave online plot'\n");
    fprintf(pipe, "set xlabel 'time[s]'\n");
    fprintf(pipe, "set ylabel 'amplitude [V]'\n");
    fprintf(pipe, "set style data lines\n");
    fprintf(pipe, "set yrange [-200:200]\n");
    fprintf(pipe, "set ytics 100\n");
    fprintf(pipe, "set grid\n");
    fprintf(pipe, "set key off\n");

    fprintf(pipe, "plot '-'\n");   
   
    for(int32_t n=0;n<length;n++)
    {
      fprintf(pipe, "%f %f\n", (double)n, y[n]);  
    }
    fprintf(pipe, "e\n"); // show plot
  }
}

void plotClose()
{
    if(pipe!=NULL) fclose(pipe);
}

#define SIGNALLENGTH 1000
double signal[SIGNALLENGTH];

int Counter=0;

void setup() 
{
 
}

void loop() 
{
  for(int n=0;n<SIGNALLENGTH;n++) signal[n]=sin(2*3.1415*n/(SIGNALLENGTH/10)+Counter)*100;
  plot(signal,SIGNALLENGTH);

  Serial.println(Counter++); 

  delay(1000);            
}


