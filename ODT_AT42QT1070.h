/*!
 * @file ODT_AT42QT1070.h
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
 * Writen by Seth Kerr for Oak Development Technologies
 *
 * Please support additional open source libraries and hardware through your
 * purchases from Oak Development Technologies
 *
 * MIT License, can be used, modified, or copied under license terms
 *
 */

#ifndef ODT_AT42QT1070_H
#define ODT_AT42QT1070_H

#include "Arduino.h"

#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Wire.h>

// I2C Address (permanent, can not be changed

#define AT42QT1070_ADDRESS (0x1B) ///< default I2C Address (fixed)

//===========================================

// Registers

/*!
 * @brief   Information addresses for the AT42QT1070
 */

enum chip_info {
  AT42QT107_CHIP_ID = (0x00),  // Chip ID should be 0x2F
  AT42QT107_FIRMWARE = (0x01), // get firmware version number
  AT42QT107_DETECT_STATUS = (0x02),
  // BIT 7 (CALIBRATE) | BIT6 (OVERFLOW) | - | - | - | - | - | TOUCH
};

/*!
 * @brief   register addresses for Keys
 */

enum {
  AT42QT107_KEY_STATUS =
      (0x03), // BIT 7 Reserved, BIT 6 (KEY 6) | ... | ... | BIT 0 (Key 0)
  AT42QT107_KEY_0_1 = (0x04), // Most Significant byte
  AT42QT107_KEY_0_2 = (0x05), // Least Significant byte
  AT42QT107_KEY_1_1 = (0x06), // MSByte
  AT42QT107_KEY_1_2 = (0x07), // LSByte
  AT42QT107_KEY_2_1 = (0x08),
  AT42QT107_KEY_2_2 = (0x09),
  AT42QT107_KEY_3_1 = (0x0A),
  AT42QT107_KEY_3_2 = (0x0B),
  AT42QT107_KEY_4_1 = (0x0C),
  AT42QT107_KEY_4_2 = (0x0D),
  AT42QT107_KEY_5_1 = (0x0E),
  AT42QT107_KEY_5_2 = (0x0F),
  AT42QT107_KEY_6_1 = (0x10),
  AT42QT107_KEY_6_2 = (0x11),

  AT42QT107_REF_DATA_0_1 = (0x12), // MSByte
  AT42QT107_REF_DATA_0_2 = (0x13), // LSByte
  AT42QT107_REF_DATA_1_1 = (0x14),
  AT42QT107_REF_DATA_1_2 = (0x15),
  AT42QT107_REF_DATA_2_1 = (0x16),
  AT42QT107_REF_DATA_2_2 = (0x17),
  AT42QT107_REF_DATA_3_1 = (0x18),
  AT42QT107_REF_DATA_3_2 = (0x19),
  AT42QT107_REF_DATA_4_1 = (0x1A),
  AT42QT107_REF_DATA_4_2 = (0x1B),
  AT42QT107_REF_DATA_5_1 = (0x1C),
  AT42QT107_REF_DATA_5_2 = (0x1D),
  AT42QT107_REF_DATA_6_1 = (0x1E),
  AT42QT107_REF_DATA_6_2 = (0x1F),

  AT42QT107_NTHR_K0 = (0x20), // negative threshold value.
  AT42QT107_NTHR_K1 = (0x21), // Do not set this value to 0
  AT42QT107_NTHR_K2 = (0x22), // 0 will cause the key to go into detection
  AT42QT107_NTHR_K3 = (0x23),
  AT42QT107_NTHR_K4 = (0x24),
  AT42QT107_NTHR_K5 = (0x25),
  AT42QT107_NTHR_K6 = (0x26),

  AT42QT107_AVE_KS_K0 = (0x27), // BIT 7 - BIT 3: Average factoring
  AT42QT107_AVE_KS_K1 = (0x28), // BIT 2 - BIT 0: Adjacent Key Supression
  AT42QT107_AVE_KS_K2 = (0x29), // AVE values set ADC Sample Number
  AT42QT107_AVE_KS_K3 =
      (0x2A), // AVE can be: 1, 2, 4, 8, 16, 32 ONLY, Default of 8.
  AT42QT107_AVE_KS_K4 = (0x2B), // AKS bits can have a value between 0 and 3
  AT42QT107_AVE_KS_K5 = (0x2C), // AKS value of 0 means key is not part of a
  AT42QT107_AVE_KS_K6 = (0x2D), // AKS group. Default AVE/AKS value 0x01

  AT42QT107_DI_K0 = (0x2E), // Detection integrator
  AT42QT107_DI_K1 = (0x2F), // 8 bit value controls the number of consecutive
  AT42QT107_DI_K2 = (0x30), // measurements that must be confirmed to having
  AT42QT107_DI_K3 =
      (0x31), // passed the key threshold for a key being registered
  AT42QT107_DI_K4 = (0x32),    // as a detect.
  AT42QT107_DI_K5 = (0x33),    // Minimum value for DI filter is 2
  AT42QT107_DI_K6 = (0x34),    // Default of 4
  AT42QT107_FO_MO_GA = (0x35), // FastOutDI/ Max Cal/ Guard Channel
  // Fast Out DI (FO Mode) - BIT 5 is set, filters with integrator of 4.
  // MAX CAL: if cleared, all keys recalibrated after Max On Duration timeout
  // GUARD CHANNEL: bits 0-3 are used to set a key as the guard channel. Valid
  // values 0-6, with any larger value disabling the guard key feature.

  AT42QT107_CAL = (0x38), // Calibrate by writing any value not equal to zero
  AT42QT107_RESET =
      (0x39), // active low reset, write any nonzero value to reset
};

/*!
 * @brief   registers that are related to power consumption
 */

enum power_regs {
  AT42QT107_LP = (0x36), // lower power mode

  // 8 bit value, 0 = 8ms between samples
  // 1 = 8ms | 2 = 16ms | 3 = 24ms | 4 = 32 | 254 = 2.032s | 255 = 2.040s
  // Default value: 2 (16ms)

  AT42QT107_MAX_ON_DUR = (0x37), // maximum on duration

  // 8 bit value to determine how long any key can be in touch before it
  // recalibrates itself 0 = off | 1 = 160ms | 2 = 320ms | 3 = 480ms | 4 = 640ms
  // | 255 = 40.8s Default value: 180(160ms*180 = 28.8s)

};
/*!
 * @brief AT42QT1070 Class object
 */
class ODT_AT42QT1070 {
public:
  // Hardware I2C
  ODT_AT42QT1070();

  bool begin(uint8_t i2caddr = AT42QT1070_ADDRESS);

  uint16_t readRegister16(uint8_t regMSB);
  uint8_t readRegister8(uint8_t reg);
  void writeRegister8(uint8_t reg, uint8_t value);
  bool touched(void);
  uint8_t keyTouched(void);
  void setNegThreshold(uint8_t reg, uint8_t negVal); // CAN NOT BE ZERO

  void setLP(uint8_t value); // will write to the Low Power register directly

private:
  Adafruit_I2CDevice *i2c_dev = NULL;
};

#endif