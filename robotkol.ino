#include <Servo.h>
#include <IRremote.h>

//IR alici pini
int RECV_PIN = 2;

//IR alici digital input degerleri
#define UP 24
#define DOWN 82
#define YILDIZ 22
#define KARE 13
#define SAG 8
#define SOL 90
#define PLAYPAUSE 28
#define BUTON1 69
#define BUTON2 70
#define BUTON3 71
#define BUTON4 68
#define BUTON5 64
#define BUTON6 67
#define BUTON7 7
#define BUTON8 21
#define BUTON9 9

//SERVOLAR
Servo ileri_geri;
Servo yukari_asagi;
Servo sag_sol;
Servo tutamac;

//Baslangic dereceleri
//Bu kisim servonun pozisyonuna gore degisebilir
int pos_x = 158;
int pos_y = 150;
int pos_z = 0;
int pos_tut = 50;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN);
  //x pin
  ileri_geri.attach(3);
  //y pin
  yukari_asagi.attach(5);
  //z pin
  sag_sol.attach(6);
  //tutamac pin
  tutamac.attach(9);
}

void loop() {
  int button = digitalRead(buttonPin);
  if (IrReceiver.decode()) {
    IrReceiver.resume();
    switch (IrReceiver.decodedIRData.command) {
      /*
      Burada degerleri degistirerek daha hizli hareket etmesini saglayabilirsiniz.
      */
      case UP: pos_y += 5; break;
      case DOWN: pos_y -= 5; break;
      case SAG: pos_z += 5; break;
      case SOL: pos_z -= 5; break;
      case BUTON1: pos_x += 5; break;
      case BUTON2: pos_x -= 5; break;
      case YILDIZ: pos_tut += 10; break;
      case KARE: pos_tut -= 10; break;
    }
    Serial.println(IrReceiver.decodedIRData.command);  //Komut dinleme
  }
  //Servonun maksimum ve minimum acilar,
  //Bu degerlerin disina cikmamasi icin
  pos_x = max(158, min(200, pos_x));
  ileri_geri.write(pos_x);
  pos_y = max(135, min(180, pos_y));
  yukari_asagi.write(pos_y);
  pos_z = max(0, min(180, pos_z));
  sag_sol.write(pos_z);
  pos_tut = max(40, min(180, pos_tut));
  tutamac.write(pos_tut);
  delay(10);
}
