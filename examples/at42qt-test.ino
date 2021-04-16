#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_BusIO_Register.h>
#include <Wire.h>

#include <ODT_AT42QT1070.h>

//Adafruit_I2CDevice i2c_dev = Adafruit_I2CDevice(0x1B);
ODT_AT42QT1070 test = ODT_AT42QT1070();
void setup() {
  // put your setup code here, to run once:
  while (!Serial) { delay(10); }
  Serial.begin(115200);
  Serial.println("Qt Py using ODT AT42QT1070 Acorn: i2c detection test...");
  
  test.begin();
  //delay(1000);
  //Serial.print("printing value of ODT_AT42QT1070.begin() : ");
  //Serial.println(ODT_AT42QT1070().begin());
  Serial.print("Attempting to read register 0x02: ");
  Serial.println(test.readRegister8((0x02)));
  //Serial.println(touched());
  /*if (!i2c_dev.begin()) {
    Serial.print("Did not find device at 0x");
    Serial.println(i2c_dev.address(), HEX);
    while (1);
  }
  Serial.print("Device found on address 0x");
  Serial.println(i2c_dev.address(), HEX);*/

  /*Adafruit_BusIO_Register id_reg = Adafruit_BusIO_Register(&i2c_dev, 0x00, 1);
  uint8_t id;
  id_reg.read(&id);
  Serial.print("ID register = 0x"); Serial.println(id, HEX);
  
  Adafruit_BusIO_Register fw_reg = Adafruit_BusIO_Register(&i2c_dev, 0x01, 1);
  uint8_t fw;
  fw_reg.read(&fw);
  Serial.print("Firmware register = 0x"); Serial.println(fw, HEX);*/
  Serial.println(test.touched());
  delay(1000);
   
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.print("value of register 0x04: ");
  
  //Serial.println("what's going on here...");
  Serial.println(test.readRegister16(0x04));
  delay(1000);
  /*Adafruit_BusIO_Register detect_reg = Adafruit_BusIO_Register(&i2c_dev, 0x02, 1);
  uint8_t dt;
  detect_reg.read(&dt);
  Serial.print("Detect register = 0x"); Serial.println(dt, HEX);*/
}
