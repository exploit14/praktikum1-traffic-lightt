#include <Arduino.h>

const int PIN_MERAH  = 8;
const int PIN_KUNING = 9;
const int PIN_HIJAU  = 10;
const int PIN_TOMBOL = 2;

bool modeMalam = false;
bool tombolSebelumnya = HIGH;

void setup() {
  pinMode(PIN_MERAH, OUTPUT);
  pinMode(PIN_KUNING, OUTPUT);
  pinMode(PIN_HIJAU, OUTPUT);
  pinMode(PIN_TOMBOL, INPUT_PULLUP);   // tombol aktif LOW
  Serial.begin(9600);
  Serial.println("Mode SIANG");
}

void cekTombol() {
  bool sekarang = digitalRead(PIN_TOMBOL);
  if (sekarang == LOW && tombolSebelumnya == HIGH) {   // tombol ditekan
    modeMalam = !modeMalam;                            // ganti mode
    Serial.println(modeMalam ? "Mode MALAM" : "Mode SIANG");
    delay(50);                                         // debounce sederhana
  }
  tombolSebelumnya = sekarang;
}

void kedipKuning(int jumlah) {
  for (int i = 0; i < jumlah; i++) {
    digitalWrite(PIN_KUNING, HIGH);
    delay(300);
    digitalWrite(PIN_KUNING, LOW);
    delay(300);
  }
}

void loop() {
  cekTombol();
  if (modeMalam) {
    kedipKuning(1);
  } else {
    digitalWrite(PIN_MERAH, HIGH);
    delay(5000);
    digitalWrite(PIN_MERAH, LOW);

    digitalWrite(PIN_HIJAU, HIGH);
    delay(5000);
    digitalWrite(PIN_HIJAU, LOW);

    kedipKuning(3);
  }
}