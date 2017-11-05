/**************************************************************
wall-socket.ino
BlackBug Engineering
05.11.2017
https://github.com/dbprof/wall-socket
***************************************************************/

// определение режима соединения и подключение библиотеки RemoteXY 
#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>

#include <RemoteXY.h>

// настройки соединения 
#define REMOTEXY_SERIAL_RX 10
#define REMOTEXY_SERIAL_TX 11
#define REMOTEXY_SERIAL_SPEED 9600


// конфигурация интерфейса  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =
  { 255,12,0,1,0,32,0,6,0,1,
  7,36,8,59,48,5,6,11,2,0,
  8,65,48,24,6,79,78,0,79,70,
  70,0,65,1,8,11,47,47,2 };
  
// переменные интерфейса управления 
struct {
  // input variable
  char edit_pw[11];  // =строка UTF8 оканчивающаяся нулем  
  uint8_t switch_1; // =1 если переключатель включен и =0 если отключен 
  // output variable
  uint8_t led_tv_b; // =0..255 LED Blue brightness 
  // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 
} RemoteXY;
#pragma pack(pop)

#define PIN_SWITCH_1 3

void setup() 
{
  RemoteXY_Init ();
  pinMode (PIN_SWITCH_1, OUTPUT);
  digitalWrite(PIN_SWITCH_1,HIGH);
}

void loop() 
{ 
  RemoteXY_Handler ();

  // индикатор работы показывает наличие сигнала
  if (digitalRead(PIN_SWITCH_1) == HIGH) {
    RemoteXY.led_tv_b = 0;
  }
  else {
    RemoteXY.led_tv_b = 255;
  }

  // проверка пароля (внутри кода неправильно, но иногда можно:)
  if (strcmp(RemoteXY.edit_pw,"6578") == 0){
    digitalWrite(PIN_SWITCH_1, (RemoteXY.switch_1==1)?LOW:HIGH);
  }
}
