#include <Printers.h>
#include <XBee.h>
#include <AddicoreRFID.h>
#include <SPI.h>

#define	uchar	unsigned char
#define	uint	unsigned int

uchar fifobytes;
uchar fifoValue;

AddicoreRFID myRFID; // create AddicoreRFID object to control the RFID module

const int chipSelectPin = 10;
const int NRSTPD = 5;

//Maximum length of the array
#define MAX_LEN 16

XBee xbee = XBee();


void setup() {     
    
    Serial.begin(9600);
    xbee.setSerial(Serial);
    
    // start the SPI library:
    SPI.begin();
    
    pinMode(chipSelectPin,OUTPUT);              // Set digital pin 10 as OUTPUT to connect it to the RFID /ENABLE pin 
      digitalWrite(chipSelectPin, LOW);         // Activate the RFID reader
    pinMode(NRSTPD,OUTPUT);                     // Set digital pin 10 , Not Reset and Power-down
      digitalWrite(NRSTPD, HIGH);
  
    myRFID.AddicoreRFID_Init();  
}

void loop()
{
  uint8_t payload[] = { 'H', 'i' };
    
  // Specify the address of the remote XBee (this is the SH + SL)
  XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x403e0f30);
  
  ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
  
  uchar i, tmp, checksum1;
  uchar status;
  uchar str[MAX_LEN];
  uchar RC_size;
  uchar blockAddr;	//Selection operation block address 0 to 63
  String mynum = "";
  
  str[1] = 0x4400;
  
	//Find tags, return tag type
	status = myRFID.AddicoreRFID_Request(PICC_REQIDL, str);	
	if (status == MI_OK)
	{
          xbee.send(zbTx);           

          Serial.println("RFID tag detected");
          Serial.print("Tag Type:\t\t");
          uint tagType = str[0] << 8;
          tagType = tagType + str[1];
          switch (tagType) {
            case 0x4400:
              Serial.println("Mifare UltraLight");
              break;
            case 0x400:
              Serial.println("Mifare One (S50)");
              break;
            case 0x200:
              Serial.println("Mifare One (S70)");
              break;
            case 0x800:
              Serial.println("Mifare Pro (X)");
              break;
            case 0x4403:
              Serial.println("Mifare DESFire");
              break;
            default:
              Serial.println("Unknown");
              break;
          }
          uint8_t testLoad[] = { 'O', 'K' };
          ZBTxRequest test = ZBTxRequest(addr64, testLoad, sizeof(testLoad));
          xbee.send(test);           
	}

	//Anti-collision, return tag serial number 4 bytes
	status = myRFID.AddicoreRFID_Anticoll(str);
	if (status == MI_OK)
	{
          xbee.send(zbTx);           

          checksum1 = str[0] ^ str[1] ^ str[2] ^ str[3];
          Serial.print("The tag's number is:\t");
    	    Serial.print(str[0]);
            Serial.print(" , ");
    	    Serial.print(str[1]);
            Serial.print(" , ");
    	    Serial.print(str[2]);
            Serial.print(" , ");
    	    Serial.println(str[3]);

          Serial.print("Read Checksum:\t\t");
    	      Serial.println(str[4]);
          Serial.print("Calculated Checksum:\t");
            Serial.println(checksum1);
            
            if(str[0] == 197)                     
            {
                Serial.println("\nHello Chris!\n");
            } else if(str[0] == 244) {             //You can change this to the first byte of your tag by finding the card's ID through the Serial Monitor
                Serial.println("\nHello other tag!!\n");
            }
            Serial.println();
            delay(1000);
	}
		
        myRFID.AddicoreRFID_Halt();		   //Command tag into hibernation              

}

