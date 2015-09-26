#include <RCSwitch.h>
#include "SerialRcSwitch.h"

#define BUFF_SIZE 8
#define TX_PIN 10
#define LED_PIN 13

RCSwitch rcSwitch = RCSwitch();
char inData[BUFF_SIZE + 1]; // +1 for null termination
char charIdx = -1;

void setup() {
  rcSwitch.enableTransmit(10);
  pinMode(LED_PIN, OUTPUT);

  // Init serial port
  Serial.begin(9600);
  Serial.println("SerialRcSwitch - trigger rc switch command sending via serial port");
  Serial.println("Source code at https://github.com/pingec/SerialRcSwitch");
  Serial.println("Supported commands:");
  Serial.println("ON(<int>,<int>) - where int is a digit between 1 and 4");
  Serial.println("OFF(<int>,<int>) - where int is a digit between 1 and 4");
  Serial.println("For example: OFF(2,4)");
  Serial.println("Terminate command (line) with either CR or LF, not both.");
}

void loop() {
  if (Serial.available() > 0)
  {
    char readChar  = Serial.read();

    // Evaluate read data when new line detected
    if (readChar == '\r' || readChar == '\n')
    {
      processReadData();
      resetReadData();
    }

    else if (charIdx < BUFF_SIZE)
    {
      inData[++charIdx] =  readChar;
    }
  }
}

void processReadData()
{
  // null terminate string
  inData[++charIdx] = '\0';

  int int1 = -1;
  int int2 = -1;
  Command cmd;

  if (startsWith("OFF(", inData))
  {
    cmd = off;
    int1 = (inData[4] - '0');
    int2 = (inData[6] - '0');    
  }
  else if (startsWith("ON(", inData))
  {
    cmd = on;
    int1 = (inData[3] - '0');
    int2 = (inData[5] - '0');
  }
  else {
    Serial.print(inData);
    Serial.println(" invalid command.");
    return;
  }

  if (argumentsValid(int1, int2))
  {    
    txCommand(cmd, int1, int2);
    Serial.print(inData);    
    Serial.println(" OK!");
  }
  else {
    Serial.println("Command parameters out of range.");
  }
}

bool argumentsValid(int int1, int int2)
{
  return int1 >= 1 && int1 <= 4 && int2 >= 1 && int2 <= 4;
}

 
void txCommand(Command cmd, int int1, int int2)
{ 
  digitalWrite(LED_PIN, HIGH);  
  if(cmd == on)
  {
    rcSwitch.switchOn(int1, int2);
  }
  else if(cmd == off)
  {
    rcSwitch.switchOff(int1, int2);    
  }    
  digitalWrite(LED_PIN, LOW);   
}


void resetReadData()
{
  charIdx = -1;
}

bool startsWith(const char *pre, const char *str)
{
  size_t lenpre = strlen(pre),
         lenstr = strlen(str);
  return lenstr < lenpre ? false : strncmp(pre, str, lenpre) == 0;
}


