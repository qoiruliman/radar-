#include <Servo.h>  // Mengimpor library Servo untuk mengendalikan motor servo
Servo servo;  // Membuat objek servo untuk mengontrol motor servo

byte derajat = 0;  // Variabel untuk menyimpan sudut servo, mulai dari 0 derajat
long durasi, jarak = 0;  // Variabel untuk menyimpan durasi pulse dan jarak yang diukur

const byte TRIG_PIN = 5;  // Menetapkan pin 5 sebagai pin Trigger untuk sensor Ultrasonic
const byte ECHO_PIN = 4;  // Menetapkan pin 4 sebagai pin Echo untuk sensor Ultrasonic
const byte buzzer = 12;  // Menetapkan pin 12 sebagai pin untuk buzzer

void setup() {
  Serial.begin(9600);  // Memulai komunikasi serial dengan baud rate 9600 untuk menampilkan data di Serial Monitor
  
  pinMode(buzzer, OUTPUT);  // Mengatur pin buzzer sebagai output
  pinMode(TRIG_PIN, OUTPUT);  // Mengatur pin Trigger sebagai output
  pinMode(ECHO_PIN, INPUT);  // Mengatur pin Echo sebagai input
  
  servo.attach(6);  // Menghubungkan servo ke pin 6
  servo.write(0);  // Menggerakkan servo ke posisi 0 derajat pada awal
}

void loop() {
  // Menggerakkan servo dari 0 derajat ke 180 derajat
  for (derajat = 0; derajat < 180; derajat++) {
    servo.write(derajat);  // Menggerakkan servo ke sudut yang ditentukan
    bacaUltrasonic();  // Memanggil fungsi untuk membaca jarak dari sensor Ultrasonic
    delay(20);  // Menunggu selama 20 milidetik untuk stabilitas
  }

  // Menggerakkan servo dari 180 derajat kembali ke 0 derajat
  for (derajat = 180; derajat > 0; derajat--) {
    servo.write(derajat);  // Menggerakkan servo ke sudut yang ditentukan
    bacaUltrasonic();  // Memanggil fungsi untuk membaca jarak dari sensor Ultrasonic
    delay(20);  // Menunggu selama 20 milidetik untuk stabilitas
  }
}

void bacaUltrasonic() {
  // Fungsi untuk membaca jarak menggunakan sensor Ultrasonic
  
  digitalWrite(TRIG_PIN, LOW);  // Mengatur pin Trigger ke LOW untuk memulai pengukuran
  delayMicroseconds(2);  // Menunggu selama 2 mikrodetik untuk stabilitas
  digitalWrite(TRIG_PIN, HIGH);  // Mengatur pin Trigger ke HIGH untuk memicu sensor Ultrasonic
  delayMicroseconds(10);  // Memberikan pulse selama 10 mikrodetik
  digitalWrite(TRIG_PIN, LOW);  // Mengatur pin Trigger kembali ke LOW
  
  durasi = pulseIn(ECHO_PIN, HIGH);  // Mengukur durasi pulsa yang diterima di pin Echo
  jarak = durasi * 0.0344 / 2;  // Menghitung jarak dengan rumus (durasi * kecepatan suara / 2)

  Serial.print("Jarak: ");  // Menampilkan kata "Jarak:" di Serial Monitor
  Serial.print(jarak);  // Menampilkan nilai jarak yang dihitung
  Serial.println(" cm");  // Menambahkan satuan cm dan pindah ke baris baru

  // Jika jarak lebih kecil dari 25 cm, maka buzzer akan aktif
  if (jarak < 25) {
    Serial.println("TERDETEKSI ADANYA OBJEK!!!");  // Menampilkan pesan jika objek terdeteksi
    digitalWrite(buzzer, HIGH);  // Menghidupkan buzzer
  } else {
    digitalWrite(buzzer, LOW);  // Mematikan buzzer jika tidak ada objek terdeteksi
  }
}