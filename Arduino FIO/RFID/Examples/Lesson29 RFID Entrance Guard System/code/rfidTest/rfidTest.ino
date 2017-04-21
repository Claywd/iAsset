/*******************************************
 * name:RFID Entrance Guard System
 * function:first: get the id of RFID key by the getid.ino file ,then divide the ID into four parts and fill them in loop() function
 * swipe the RFID key ring on the RFID module. 
 * If the password is correct, the normally open contact of the relay will be closed and the LCD will display a string “ID:5AE4C955” "hello SunFounder",
 * and then "Welcome!" two seconds later;
 * if the password is incorrect, the normally open contact of the relay will be disconnected and the LCD will display a string "Hello unknown guy" ,
 * and then "Welcome!" two seconds later
 * connection:
 * RFID	                  SunFounder Uno
 * VCC	                      3.3V
 * RST	                      2
 * GND	                      GND
 * MISO	                      3
 * MOSI	                      4
 * SCK	                      5
 * NSS	                      6
 * IRQ	                      7
 ****************************************/
//Email:support@sunfounder.com
//Website:www.sunfounder.com

#include"rfid.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27,16,2);
RFID rfid;  //create a variable type of RFID
#define relayPin 8  //relay module attach to pin8

uchar serNum[5]; // array to store your ID

void setup()
{
  lcd.init();  //initialize lcd
  lcd.backlight();  //turn on the backlight
  Serial.begin(9600);
  rfid.begin(7, 5, 4, 3, 6, 2);//rfid.begin(IRQ_PIN,SCK_PIN,MOSI_PIN,MISO_PIN,NSS_PIN,RST_PIN)
  delay(100);
  rfid.init();  //initialize the RFID
  pinMode(relayPin, OUTPUT);  //set relayPin as OUTPUT
  digitalWrite(relayPin,LOW);  //and high level
  //Serial.begin(9600);
  lcd.setCursor(0,0);
  lcd.print("    Welcome!    ");  //print"    Welcome!    "
  delay(2000);  //delay 2s

}
void loop()
{
  uchar status;
  uchar str[MAX_LEN];
  // Search card, return card types
  status = rfid.request(PICC_REQIDL, str);
  if (status != MI_OK)
  {
    return;
  }
  // Show card type
  rfid.showCardType(str);
  //Prevent conflict, return the 4 bytes Serial number of the card
  status = rfid.anticoll(str);

  if (status == MI_OK)
  {
    //Serial.print("The card's number is: ");
    lcd.setCursor(0,0);
    lcd.print(" ID: ");
    memcpy(serNum, str, 5);
    rfid.showCardID(serNum);  //show the card ID
    // Serial.println();

    // Check people associated with card ID
    uchar* id = serNum;
    if( id[0]==0x4B && id[1]==0xE6 && id[2]==0xD1 && id[3]==0x3B ) 
    {
      digitalWrite(relayPin,HIGH);
      // Serial.println("Hello Dannel!");
      lcd.setCursor(0,1);
      lcd.print(" Hello Dannel! ");
      delay(2000);
      lcd.clear();
      digitalWrite(relayPin,LOW);
    } 
     //if the card id is 5AE4C955,then relay connect 
    else if(id[0]==0x5A && id[1]==0xE4 && id[2]==0xC9 && id[3]==0x55) 
    {
      digitalWrite(relayPin,HIGH);
      //Serial.println("Hello SunFounder");
      lcd.setCursor(0,1);
      lcd.print("Hello SunFounder");
      delay(2000);
      lcd.clear();
      digitalWrite(relayPin,LOW);
    } 
    else
    {

      //Serial.println("Hello unkown guy!");
      lcd.setCursor(0,1);
      lcd.print("Hello unkown guy");
      delay(2000);
      lcd.clear();
    }
  }
  lcd.setCursor(0,0);
  lcd.print("    Welcome!    ");
  delay(2000);
  rfid.halt(); //command the card into sleep mode 
}

