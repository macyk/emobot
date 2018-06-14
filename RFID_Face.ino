/*
PINOUT:
RC522 MODULE    Uno/Nano     MEGA
SDA             D10          D9
SCK             D13          D52
MOSI            D11          D51
MISO            D12          D50
IRQ             N/A          N/A
GND             GND          GND
RST             D9           D8
3.3V            3.3V         3.3V
*/
/* Include the standard Arduino SPI library */
#include <SPI.h>
/* Include the RFID library */
#include <RFID.h>
#include <Servo.h>

Servo left_servo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
Servo right_servo; 

int pos = 0;    // variable to store the servo position
bool like = false;

/* Define the DIO used for the SDA (SS) and RST (reset) pins. */
#define SDA_DIO 9
#define RESET_DIO 8
/* Create an instance of the RFID library */
RFID RC522(SDA_DIO, RESET_DIO); 
String CARD_ONE = "14427192128203";
String CARD_TWO = "80858812239";
String cardID;

void setup()
{ 
  Serial.begin(9600);
  /* Enable the SPI interface */
  SPI.begin(); 
  /* Initialise the RFID reader */
  RC522.init();
  left_servo.attach(2);  // attaches the servo on pin 9 to the servo object
  right_servo.attach(3);
}

void loop()
{
  /* Has a card been detected? */
  if (RC522.isCard())
  {
    /* If so then get its serial number */
    RC522.readCardSerial();
    Serial.println("Card detected:");
    
    for(int i=0;i<5;i++)
    {
      cardID += RC522.serNum[i];
      
      //Serial.print(RC522.serNum[i],HEX); //to print card detail in Hexa Decimal format
    }
    Serial.print(cardID);
    
    if(cardID == CARD_ONE)
    {
      like = true;
    }
    else if(cardID == CARD_TWO)
    {
      like = false;
    }

    if(like)
    {
      left_servo.write(0);              // tell servo to go to position in variable 'pos'
      right_servo.write(180);
      delay(20); 
    }
    else
    {
      left_servo.write(60);              // tell servo to go to position in variable 'pos'
      right_servo.write(120);
      delay(20); 
    }
    cardID = "";
    Serial.println();
    Serial.println();
  }
  delay(1000);
}
