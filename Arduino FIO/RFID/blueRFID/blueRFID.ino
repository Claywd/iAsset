/*******************************************
 * function:get the id of RFID key
 * RFID                    SunFounder Uno
 * VCC                        3.3V
 * RST                        3
 * GND                        GND
 * MISO                       17
 * MOSI                       16
 * SCK                        15
 * NSS                        9
 * IRQ                        7
 ****************************************/

#include"rfid1.h"
#define DEBUG_MODE 1
RFID1 rfid;//create a variable type of RFID1
//int RXLED=17;
uchar serNum[5];  // array to store your ID

void setup()
{
  Serial1.begin(9600); //initialize the serial
  rfid.begin(7, 15, 16, 17, 9, 3);  ////rfid.begin(IRQ_PIN,SCK_PIN,MOSI_PIN,MISO_PIN,NSS_PIN,RST_PIN)
  delay(100);//delay 1s
  rfid.init(); //initialize the RFID
  TXLED0;
}
void loop()
{
  //Serial.print("TEST\n");
  uchar status;
  
  uchar str[MAX_LEN];
  // Search card, return card types
  status = rfid.request(PICC_REQIDL, str);
  if (status != MI_OK)
  {
    TXLED1;
    
    delay(100);
    //TXLED1;
    delay(100);
    //TXLED0;
    delay(100);
    //TXLED1;
    delay(100);
    //TXLED0;    
    
    return;
  }
  // Show card type
 // rfid.showCardType(str);
  //Prevent conflict, return the 4 bytes Serial number of the card
  status = rfid.anticoll(str);

  if (status == MI_OK)
  {

    TXLED0;
    memcpy(serNum, str, 5);
    int blah = 0;
    for(int i=0; i<5; i++){
        blah = blah + (int)serNum[i];
    }
    Serial.println(blah);
    String data = String(blah);
    data = data + ",1";

    char buff[5];
    data.toCharArray(buff, data.length()+1);
    Serial1.write(buff);   
    Serial1.println();
    
    //rfid.showCardID(serNum);//show the card ID

  }
  delay(500); 
}
