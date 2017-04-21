Getting Started with SPI:

# Background

The two RFIDS we have right now have a slightly different pin Configuration so there is code for both and a pin layout below. 


Typical pin layout used:
   -----------------------------------------------------------------------------------------
               Red MFR-C522 Blue MFR-C522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Reader/PCD         Uno/101       Mega      FIO v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin                Pin           Pin        Pin       Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          RST                9             5         D3         RESET/ICSP-5     RST
   SPI SS      NSS(SS)      SDA                10            53        D9         10               10
   SPI MOSI    MOSI         MOSI               11 / ICSP-4   51        D17        ICSP-4           16
   SPI MISO    MISO         MISO               12 / ICSP-1   50        D16        ICSP-1           14
   SPI SCK     SCK          SCK                13 / ICSP-3   52        D15        ICSP-3           15
   SPI IRQ     IRQ          IRQ                8                       D7         

## About SPI:
  - https://learn.sparkfun.com/tutorials/serial-peripheral-interface-spi

# Sources
  - https://forums.adafruit.com/viewtopic.php?f=19&t=45652&p=235283#p235283
  - https://github.com/miguelbalboa/rfid/blob/master/examples/AccessControl/AccessControl.ino
  -
