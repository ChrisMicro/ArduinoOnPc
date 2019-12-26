/*

How to use serial input with ArduinoOnPc?

At the momemt the keyboard of the PC is used as serial input. 
Due to the limitations of the linux console only whole lines can be read ( terminated with 'return key').

Original Code is found here:

https://www.arduino.cc/reference/de/language/functions/communication/serial/available/


26 December 2019, ChrisMicro

*/

int incomingByte = 0; 

void setup() 
{
  Serial.begin(9600); 
}

void loop() 
{
  if (Serial.available() > 0) // serial chars are available, when a whole line was read and the return key was pressed
  {
    incomingByte = Serial.read();

    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }else // if the return key on the keyboard was not pressed
  {
    Serial.println("waiting");
    delay(1000);
  }
}
