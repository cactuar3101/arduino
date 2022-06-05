/************************************************************** 
 *
 *  DHT_func
 * 
 *  task นี้จะทำหน้าที่ อ่านค่าเซนเซอร์ DHT อย่างเดียว 
 *  จะไม่มีการทำงานอย่างอื่นเป็นการแบ่ง งานกันทำอย่างเด็ดขาดไม่ปะปนกัน
 *  โดยค่าล่าสุดของ DHT sensor จะถูกเก็บไว้ที่ตัวแปร DHT_temp , DHT_humid 
 *  ซึ่ง task อื่นๆ สามารถนำไปใช้งานได้ เมื่อต้องการ
 *  
 *  หมายเหตุ
 *  ภายใน task ให้ใช้ DELAY() ตัวพิมพ์ใหญ่ทั้งหมด
 *  ไลบรารี่ DHT ใช้ของ Adafruit โดย ให้ติดตั้งไลบรารี่ทั้ง 2 นี้
 *     https://github.com/adafruit/Adafruit_Sensor
 *     https://github.com/adafruit/DHT-sensor-library
 *  
 **************************************************************/
 


#include <Wire.h>
#include "Adafruit_HTU21DF.h"

Adafruit_HTU21DF htu = Adafruit_HTU21DF();


// Task Share Variables Info
// xDHT_temp   : ข้อมูล อุณหภูมิ ล่าสุด สำหรับ task อื่นนำไปใช้ได้ 
// xDHT_humid  : ข้อมูล ความชื้น ล่าสุด สำหรับ task อื่นนำไปใช้ได้ 

void HTU_func(void*) {
  //----พื้นที่สำหรับประกาศตัวแปรที่ใช้ภายใน task นี้เท่านั้น----
  
  //-----------------------------------------------
 VOID SETUP() {
  Serial.begin(115200);
  Serial.println("HTU21DF Humidity & Temperature sensor");

  if (!htu.begin()) {
    Serial.println("Couldn't find HTU21DFsensor!");
    while (1);
  }
}

  VOID LOOP() {                       // VOID LOOP() ใน task ใช้พิมพ์ใหญ่
    float t = NAN; float h = NAN;  
    while( isnan(t) || isnan(h) ) {
      t = htu.readTemperature();
      h = htu.readHumidity();
    }
    xHTU_temp = t;  xHTU_humid = h;  // ค่าที่อ่านได้ถูกต้องแล้ว ค่อย copy ไปไว้ที่ ตัวแปรค่าล่าสุด
    Serial.printf("[HTU] temp : %.2f C\thumid : %.2f %%\n", xHTU_temp, xHTU_humid);
    
    DELAY(500);              // วนรอบถัดไปที่จะอ่าน sensor อีกครั้ง
  }
}
