/*******************************************
 * function:get the id of RFID key
 * RFID                    SunFounder Uno
 * VCC                        3.3V
 * RST                        2
 * GND                        GND
 * MISO                       3
 * MOSI                       4
 * SCK                        5
 * NSS                        6/8
 * IRQ                        7
 ****************************************/
//Website: www.sunfounder.com
//Email: service@sunfounder.com

#include"rfid1.h"
RFID1 rfid;//create a variable type of RFID1

uchar serNum[5];  // array to store your ID
int Nss1 = 9; //the pin NSS(chipselect) of RFID1

void setup()
{
  //SET the two rfid not work
  pinMode(Nss1, OUTPUT);
  digitalWrite(Nss1, HIGH);
  Serial.begin(9600); //initialize the serial for software
  Serial1.begin(9600); //initialize the serial for hardware
}
void loop()
{
  uchar status;
  uchar str[MAX_LEN];

  //RFID1 start to work
  rfid.begin(7, 15, 16, 17, Nss1, 3);  //rfid.begin(IRQ_PIN,SCK_PIN,MOSI_PIN,MISO_PIN,NSS_PIN,RST_PIN)
  delay(100);//delay 100ms
  rfid.init(); //initialize the RFID

  // Search card, return card types
  status = rfid.request(PICC_REQIDL, str);
  if (status == MI_OK)
  {
    // Show card type
    rfid.showCardType(str);
    //Prevent conflict, return the 4 bytes Serial number of the card
    status = rfid.anticoll(str);
    if (status == MI_OK)
    {
      Serial.print("The RFID1's number is: ");
      memcpy(serNum, str, 5);
      rfid.showCardID(serNum);//show the card ID
      Serial.println();
      Serial.println();
    }
    delay(500);
    rfid.halt(); //command the card into sleep mode
  }  
  
}

