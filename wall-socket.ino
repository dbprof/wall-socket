/**************************************************************
wall-socket.ino
BlackBug Engineering
05.11.2017
https://github.com/dbprof/wall-socket
***************************************************************/


#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // 10=BLUETOOTH-TXD | 11=BLUETOOTH-RXD

void setup()
{
  pinMode(9, OUTPUT);   // этот пин - для управления AT режимом
  digitalWrite(9, LOW); 
  //delay(10000);          // раскомментируй для перехода в режим настройки
  //digitalWrite(9, HIGH); // раскомментируй для перехода в режим настройки
  
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(9600);  // 9600 - скорость по умолчанию для SPP-C ZS-040 (HC-05) чип BK3231
  
}

void loop()
{
  // читаем с SPP-C в монитор порта Arduino
  if (BTSerial.available())
    Serial.write(BTSerial.read());

  // возвращаем из монитора порта Arduino в SPP-C
  if (Serial.available())
    BTSerial.write(Serial.read());
}
