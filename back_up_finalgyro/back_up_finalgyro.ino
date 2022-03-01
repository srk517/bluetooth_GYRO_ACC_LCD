//master_configured
#include <SoftwareSerial.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal.h>
#include <Wire.h>
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
String Data;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define tx 2
#define rx 3
SoftwareSerial configBt(rx, tx); // RX, TX
String val; 
float p;
Adafruit_MPU6050 mpu;
void setup() 
{
  Serial.begin(38400);
  configBt.begin(9600);
  lcd.begin(16, 2);
  pinMode(tx, OUTPUT);
  pinMode(rx, INPUT);
  while(!Serial)
  delay(10);
  Serial.println("Adafruit MPU6050 test!");
   if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  lcd.print("Acc. range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    lcd.print("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    lcd.print("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    lcd.print("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    lcd.print("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  lcd.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    lcd.print("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    lcd.print("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    lcd.print("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    lcd.print("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  lcd.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    lcd.print("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    lcd.print("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    lcd.print("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    lcd.print("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    lcd.print("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    lcd.print("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    lcd.print("5 Hz");
    break;
  }

  lcd.print("");
  delay(100);


  
}

void loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
   lcd.setCursor(0,0);
  lcd.print("A");
  lcd.print(a.acceleration.x);
  //lcd.print("Y:");
  lcd.print(a.acceleration.y);
  //lcd.print("Z:");
  lcd.print(a.acceleration.z);
  //lcd.print("m/s^2");
  lcd.setCursor(0,1);
  lcd.print("R:");
  lcd.print(g.gyro.x);
  //lcd.print("Y:");
  lcd.print(g.gyro.y);
  //lcd.print("Z:");
  lcd.print(g.gyro.z);
  //lcd.print("rad/s");
  lcd.print("");
  delay(1000);
  float f=a.acceleration.x;
  val=String(f);
   if(configBt.available()>0) // if the HC05 is sending something… 
  {
  //  if(Data=="A"){
    Serial.print("Recieved DATA");
   // val = Serial.read();
   Data=configBt.readString();
   if(Data=="A"){
    Serial.println(Data); // print in serial monitor
    //Serial.print("HERE");
    Serial.print(val);
    configBt.write("f");
    configBt.write(f);
   // configBt.write(Data);
   // configBt.write(f);
  /*}
  if(Serial.available()>0) // if serial monitor is outputting something… 
  {
    if(Data=="A")
    {
      Serial.print("inside");
      configBt.write(a.acceleration.x);
    }
    //configBt.write(Serial.read()); // write to Arduino’s Tx pin
    //Serial.print("BOO");*/
  }

  /* Print out the values */
 
}
}
