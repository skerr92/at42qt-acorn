/**
*
*
*
*
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
    writeRegister(AT42QT107_RESET, 0x01); // simply write a nonzero number to reset
    delay(1);
    for (uint8_t i = 0; i < 0x7f; i++) {
    }

    writeRegister(AT42QT107_CAL, 0x01); // Calibrate the device by writing a non zero value to calibration register

    uint8_t curr = readRegister8(AT42QT107_KEY_0_1);
}
