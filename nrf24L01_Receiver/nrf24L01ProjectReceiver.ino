
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <Servo.h>

RF24 radio(7,8); // CE CNS

const byte address[6] = "00001";

unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;

Servo esc;
Servo servo1;
Servo servo2;
int escValue, servo1Value, servo2Value;

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
  radio.openReadingPipe(0, address);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  resetData();

  esc.attach(6);
  servo1.attach(10);
  servo2.attach(9);
  
}

void loop()
{
  if(radio.available()){
    radio.read(&data, sizeof(Data_Package));

    lastReceiveTime = millis();
  }

  currentTime = millis();
  if(currentTime - lastReceiveTime > 100)
  {
    resetData();
  }

  servo1Value = map(data.j1PotX, 0, 255, 0, 180);
  servo2Value = map(data.j1PotY, 0, 255, 0, 180);

  servo1.write(servo1Value);
  servo2.write(servo2Value);

  escValue = map(data.pot, 0, 255, 1000, 2000);
  esc.writeMicroseconds(escValue);

}
  

void resetData()
{
  data.j1PotX = 127;
  data.j1PotY = 127;
  data.j2PotX = 127;
  data.j2PotY = 127;
  data.pot = 1;
  data.leftToggle = 0;
  data.rightToggle = 0;
  
}
