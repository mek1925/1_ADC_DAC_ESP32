#include <stdlib.h>

// DAC OUTPUT is connected to GPIO 34 (Analog ADC1_CH6)
#define ADC6 34
#define DAC1 25
#define LED1 2
#define LED2 0
#define LED3 4

// Variable delaration
static int adcValue = 0;
int dacValue = 0;
float adcVotalegValue;
float dacVotalegValue;
float adcResolution = (3.3 / 4095);
float dacResolution = (3.3 / 255);

// Function delaration
void LED(int, float);
int stringToInt(String);

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Type any number between 0 - 255");
  // dacWrite(DAC1, 0);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop()
{
  while (Serial.available() > 0)
  {
    
    // Reading DAC value
    delay(500);
    String dacString = Serial.readString();
    dacValue = stringToInt(dacString);

    if (dacValue <= 255)
    {
      Serial.print("DAC Type value-");
      Serial.println(dacValue);

      delay(500);
      dacWrite(DAC1, dacValue);
      Serial.print("DAC OutPute value-");
      Serial.println(dacValue);

      dacVotalegValue = dacResolution * dacValue;
      Serial.print("DAC Voltage value-");
      Serial.println(dacVotalegValue);
      Serial.println("---------");
      delay(500);

      // Reading ADC value
      adcValue = analogRead(ADC6);
      adcVotalegValue = adcResolution * analogRead(ADC6);
      delay(500);

      LED(adcValue, adcVotalegValue);
    }
    else
    {
      Serial.println("Enter number is Invalid, Pls type agin");
    }
  }
}

int stringToInt(String inputString)
{
  int number = 0;
  for (int i = 0; inputString[i] != '\0'; i++)
  {
    number = number * 10 + (inputString[i] - 48);
  }
  return number;
}

void LED(int v, float p)
{

  if (p >= 2.5)
  {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    Serial.println("\tLED1 HIGH");
    Serial.print("ADC InPute value-");
    Serial.println(v);
    Serial.print("ADC Voltage value-");
    Serial.println(p);
    Serial.println("********");
  }

  if (2.5 > p && p > 1.5)
  {
    digitalWrite(LED2, HIGH);
    digitalWrite(LED1, LOW);
    digitalWrite(LED3, LOW);
    Serial.println("\tLED2 HIGH");
    Serial.print("ADC InPute value-");
    Serial.println(v);
    Serial.print("ADC Voltage value-");
    Serial.println(p);
    Serial.println("********");
  }

  if (p <= 1.5)
  {
    digitalWrite(LED3, HIGH);
    digitalWrite(LED2, LOW);
    digitalWrite(LED1, LOW);
    Serial.println("\tLED3 HIGH");
    Serial.print("ADC InPute value-");
    Serial.println(v);
    Serial.print("ADC Voltage value-");
    Serial.println(p);
    Serial.println("********");
  }
}