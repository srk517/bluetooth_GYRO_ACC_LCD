//master_configured
#include <SoftwareSerial.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal.h>
#include <Wire.h>
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
char buff0[5]={0};
char buff1[5]={0};
char buff2[5]={0};
char buff3[5]={0};
char buff4[5]={0};
char buff5[5]={0};
 float f0=0;
 float f1=0;
 float f2=0;
 float f3=0;
 float f4=0;
 float f5=0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define tx 2
#define rx 3
SoftwareSerial configBt(rx, tx); // RX, TX
String val; 
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
 float f0=a.acceleration.x;
 float f1=a.acceleration.y;
 float f2=a.acceleration.z;
 float f3=g.gyro.x;
 float f4=g.gyro.y;
 float f5=a.gyro.z;
  lcd.setCursor(0,0);
  lcd.print("A");
  lcd.print(f0);
  //lcd.print("Y:");
  lcd.print(f1);
  //lcd.print("Z:");
  lcd.print(f2);
  //lcd.print("m/s^2");
  lcd.setCursor(0,1);
  lcd.print("R:");
  lcd.print(f3);
  //lcd.print("Y:");
  lcd.print(f4);
  //lcd.print("Z:");
  lcd.print(f5);
  //lcd.print("rad/s");
  lcd.print("");
  delay(1000);
 
   if(configBt.available()>0) // if the HC05 is sending something… 
  {
    Serial.print("Recieved DATA");
    val = configBt.readString();
    dtostrf(f0,4,3,buff0);
    dtostrf(f1,4,3,buff1);
    dtostrf(f2,4,3,buff2);
    dtostrf(f3,4,3,buff3);
    dtostrf(f4,4,3,buff4);
    dtostrf(f5,4,3,buff5);
   // configBt.write(f);
  
  if(val.charAt(0)=='A')
    {
      configBt.write("X= ");
       for(int i=2;i<5;i++)
      {
        Serial.print(buff0[i]);
        configBt.write(buff0[i]);
        buff0[i]={0};
      }
          configBt.write("Y= ");  
        for(int i=2;i<5;i++)
      {
        Serial.print(buff1[i]);
        configBt.write(buff1[i]);
        buff1[i]={0};
      }
        configBt.write("Z= ");  
       for(int i=2;i<5;i++)
      {
        Serial.print(buff2[i]);
        configBt.write(buff2[i]);
        buff2[i]={0};
      }
      delay(1000);
      
    }
    if(val.charAt(0)=='G')
    {
      configBt.write("X= ");
       for(int i=2;i<5;i++)
      {
        Serial.print(buff3[i]);
        configBt.write(buff3[i]);
        buff0[i]={0};
      }
          configBt.write("Y= ");  
        for(int i=2;i<5;i++)
      {
        Serial.print(buff4[i]);
        configBt.write(buff5[i]);
        buff1[i]={0};
      }
        configBt.write("Z= ");  
       for(int i=2;i<5;i++)
      {
        Serial.print(buff5[i]);
        configBt.write(buff5[i]);
        buff2[i]={0};
      }
      delay(1000);
      
    }
  }
}
