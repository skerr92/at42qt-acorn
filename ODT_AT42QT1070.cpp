/**
 * @file ODT_AT42QT1070.cpp
 *
 * @mainpage Oak Development Technologies AT42QT1070 Arduino Driver
 *
 * @section intro_sec Introduction
 *
 * This is a library for the AT42QT1070 I2C 7 Key Capacitive Touch Sensor
 *
 * Designed specifically to work with the Oak Development Technologies AT42QT1070 Acorn
 * ----> urlhere
 *
 * The sensor uses I2C to communicate with additional pins that can be connected to
 * for other operational modes.
 *
 * @section author Author
 *
 * Writen by Seth Kerr for Oak Development Technologies
 *
 * Please support additional open source libraries and hardware through your purchases
 * from Oak Development Technologies
 *
 * @section license License
 *
 * MIT License, can be used, modified, or copied under license terms
 *
*/

#include "ODT_AT42QT1070.h"

ODT_AT42QT1070::ODT_AT42QT1070() {}

bool ODT_AT42QT1070::begin(uint8_t i2caddr, TwoWire *theWire) {

    if (i2c_dev) {
        delete i2c_dev;
    }
    i2c_dev = new Adafruit_I2CDevice(i2caddr, theWire);

    if (!i2c_dev->bgein()) {
        return false;
    }
    writeRegister8(AT42QT107_RESET, 0x01); // simply write a nonzero number to reset
    delay(1);
    for (uint8_t i = 0; i < 0x7f; i++) {
    }

    writeRegister8(AT42QT107_CAL, 0x01); // Calibrate the device by writing a non zero value to calibration register

    uint8_t curr = readRegister16(AT42QT107_KEY_0_1, AT42QT107_KEY_0_2);

}
uint8_t ODT_AT42QT1070::readRegister8(uint8_t reg) {
    Adafruit_BusIO_Register read_reg = Adafruit_BusIO_Register(12c_dev, reg, 1);

    return (read_reg.read()); // change to value returned from register
}

uint16_t ODT_AT42QT1070::readRegister16(uint8_t regMSB, uint8_t regLSB) {
    uint16_t read16 = 0x0000;
    Adafruit_BusIO_Register read_reg1 = Adafruit_BusIO_Register(i2c_dev, regMSB, 1);
    Adafruit_BusIO_Register read_reg2 = Adagruit_BusIO_Register(i2c_dev, regLSB, 1);

    read16 = (read_reg1.read()) | (read_reg2.read());
    return (read16); // change to value returned from register
}

void ODT_AT42QT1070::writeRegister8(uint8_t reg, uint8_t value) {

    Adafruit_BusIO_Register write_reg = Adafruit_BusIO_Register(i2c_dev, reg, 1);
    write_reg.write(value);

}

void ODT_AT42QT1070::setLowPower(uint8_t value) {
    // make sure to write only to the Low Power Register in this section
    writeRegister8(AT42QT107_LP, value);
}
void ODT_AT42QT1070::setNegThreshold(uint8_t reg, uint8_t negVal) {
    writeRegister8(reg, negVal);
}
bool ODT_AD42QT1070::touched(void) {
    uint8_t t = readRegister8(AT42QT107_DETECT_STATUS);
    return t[0];
}
uint8_t keyTouched(void) {
    uint8_t t = readRegister8(AT42QT107_KEY_STATUS);
    return (t);
}
