#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>


RF24 radio(9,8); // CE CSN

const byte address[6] = "00001";

struct Data_Package
{
  byte j1PotX;
  byte j1PotY;
  byte j2PotX;
  byte j2PotY;
  byte pot;
  byte leftToggle;
  byte rightToggle;
};

Data_Package data;

void setup()
{
  radio.begin();
  radio.openWritingPipe(address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  

  pinMode(7, INPUT);
  pinMode(3, INPUT);

  data.j1PotX = 127;
  data.j1PotY = 127;
  data.j2PotX = 127;
  data.j2PotY = 127;
  data.leftToggle = 0;
  data.rightToggle = 0;
  data.pot = 1;
}

void loop()
{
 data.j1PotX = map(analogRead(A0), 0, 1023, 0, 255);
 data.j1PotY = map(analogRead(A1), 0, 1023, 0, 255);
 data.j2PotX = map(analogRead(A5), 0, 1023, 0, 255);
 data.j2PotY = map(analogRead(A4), 0, 1023, 0, 255);
 data.pot = map(analogRead(A2), 0, 1023, 0, 255);
 data.leftToggle = digitalRead(3);
 data.rightToggle = digitalRead(7);

 radio.write(&data, sizeof(Data_Package));
}
  
