/*!
 * @file ODT_AT42QT1070.cpp
 *
 * @mainpage Oak Development Technologies AT42QT1070 Arduino Driver
 *
 * @section intro_sec Introduction
 *
 * This is a library for the AT42QT1070 I2C 7 Key Capacitive Touch Sensor
 *
 * Designed specifically to work with the Oak Development Technologies
 * AT42QT1070 Acorn
 * ----> urlhere
 *
 * The sensor uses I2C to communicate with additional pins that can be connected
 * to for other operational modes.
 *
 * @section author Author
 *
 * Writen by Seth Kerr for Oak Development Technologies
 *
 * Please support additional open source libraries and hardware through your
 * purchases from Oak Development Technologies
 *
 * @section license License
 *
 * MIT License, can be used, modified, or copied under license terms
 *
 */

#include "ODT_AT42QT1070.h"

/*!
 * @brief Constructor
 */

ODT_AT42QT1070::ODT_AT42QT1070() {}

/*!
    @brief  initializes the begin function to get us going on i2c.
            We should be able to communicate with the device over i2c
            after this.
    @param    i2caddr
              Is the register address from where we read from
    @param    theWire
              Is the value we want to write to the register specified
    @return No return value.
*/

bool ODT_AT42QT1070::begin(uint8_t i2caddr) {
  if (i2c_dev) {
    delete i2c_dev;
  }
  i2c_dev = new Adafruit_I2CDevice(i2caddr);

  if (!i2c_dev->begin()) {
    return false;
  }
  writeRegister8(AT42QT107_RESET,
                 0x01); // simply write a nonzero number to reset
  delay(1);
  writeRegister8(AT42QT107_RESET, 0x00);
  for (uint8_t i = 0; i < 0x7f; i++) {
  }

  writeRegister8(AT42QT107_CAL, 0x01); // Calibrate the device by writing a non
                                       // zero value to calibration register
  // may not need this curr variable...
  // uint8_t curr = readRegister16(AT42QT107_KEY_0_1, AT42QT107_KEY_0_2);
  return true;
}

/*!
    @brief  Gets the 8 bit register value from the called register.
            This function requests the register contents over i2c.
    @param    reg
              Is the register address from where we read from
    @return The 8 bit value of the register read is returned.
*/

uint8_t ODT_AT42QT1070::readRegister8(uint8_t reg) {
  Adafruit_BusIO_Register read_reg = Adafruit_BusIO_Register(i2c_dev, reg, 1);
  uint8_t r_val;
  return (read_reg.read(&r_val, 0x8)); // change to value returned from register
}

/*!
    @brief  Gets the 16 bit register value from the called register.
            This function requests the register contents over i2c.
    @param    regMSB
              Is the MSB register address from where we read from
    @param    regLSB
              Is the LSB register address from where we read from
    @return The 16 bit value of the register read is returned.
*/

uint16_t ODT_AT42QT1070::readRegister16(uint8_t regMSB) {
  uint16_t read16;
  Adafruit_BusIO_Register read_reg1 =
      Adafruit_BusIO_Register(i2c_dev, regMSB, 1);

  read_reg1.read(&read16);
  return (read16); // change to value returned from register
}

/*!
    @brief  Writes the 8 bit input value from to called register.
            This function requests the register contents over i2c.
    @param    reg
              Is the register address from where we read from
    @param    value
              Is the value we want to write to the register specified
*/

void ODT_AT42QT1070::writeRegister8(uint8_t reg, uint8_t value) {

  Adafruit_BusIO_Register write_reg = Adafruit_BusIO_Register(i2c_dev, reg, 1);
  write_reg.write(value, 0x8);
}

/*!
    @brief  Gets the 8 bit register value from the called register.
            This function requests the register contents over i2c.
    @param    value
              Is the value we want to write to the register specified
*/

void ODT_AT42QT1070::setLP(uint8_t value) {
  // make sure to write only to the Low Power Register in this section
  writeRegister8(AT42QT107_LP, value);
}

/*!
    @brief    Sets the negative threshold values for the key inputs
    @param    reg
              Is the register address from where we read from
    @param    negVal
              Is the value we want to write to the register specified
*/

void ODT_AT42QT1070::setNegThreshold(uint8_t reg, uint8_t negVal) {
  writeRegister8(reg, negVal);
}

/*!
    @brief    Checks the detect status register to return the value of bit 0

    @return returns value of bit 0 as a boolean value
*/

bool ODT_AT42QT1070::touched() {
  uint8_t t = readRegister8(AT42QT107_DETECT_STATUS);
  // Serial.println(t);
  if (t & 0xF) {
    return true;
  }
  return false;
}

/*!
    @brief    Checks the Key Status register to return the values of key inputs
              BIT 7 is reserved, key values are stored bits 7 through 0

    @return returns value of key status register
*/

uint8_t ODT_AT42QT1070::keyTouched() {
  return (readRegister8(AT42QT107_KEY_STATUS));
}
