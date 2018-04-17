int sensorPin = 0;     //set potentiometer pin
int sensorValue = 0;   //variable for potetiometer 0-1023

int ledAnalogOne[] = {9, 11, 10};   //set RGB led pins red, gree, blue
int ledIndicator[] = {8, 7, 6};     //set pins of red light, green light, blue light

int setRGB = 0; //0 is red, 1 is green, 2 is blue

int inputPin = 2;         //set button pin
int val = 0;              //variable for pin status
bool wasPressed = false;  //check if button was already down

void setup() {
  
  Serial.begin(9600);    //begin the conole debug thing

  pinMode(inputPin, INPUT_PULLUP);    //set button to input
  
  for (int i = 0; i < 3; i++)
  {
    pinMode(ledAnalogOne[i], OUTPUT);    //set leds to output
    pinMode(ledIndicator[i], OUTPUT);
    analogWrite(ledAnalogOne[i], 255);   //turn off led
  }
}

void loop() {

  val = digitalRead(inputPin);    //read input value
  if (val == LOW && !wasPressed)  //change RGB compenent on led
  {                               //if button was pressed
    setRGB++;
    if (setRGB > 2)
    {
      setRGB = 0;                 //cycle back to red (0) if >2
    }
    wasPressed = true;
  }
  else if (val == HIGH)
  {
    wasPressed = false;
  }

  
  sensorValue = analogRead(sensorPin);
  if (sensorValue < 12)
  {
    sensorValue = 0;   //fixes some stuff with twisty thing
  }
  int sensorRGB = sensorValue / (1023/255);   //make sensor values 0-255
  byte color[] = {sensorRGB, sensorRGB, sensorRGB};
  
  SetColor(ledAnalogOne, color);
  
}

void SetColor(int* led, byte* color)
{
  for(int i = 0; i < 3; i++)
  {
    if (i == setRGB)    //only edit the selected component
    {
      analogWrite(led[i], 255 - color[i]);
      digitalWrite(ledIndicator[i], HIGH);  //turn on corresponding
    }                                       //indicator light
    else
    {
      digitalWrite(ledIndicator[i], LOW);  //turn off others
    }
  }
}

