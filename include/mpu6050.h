/*
    A lightweight library for reading and processing motion information
    from a MPU-6050 sensor.
    Copyright (C) 2016  Sakari Kapanen

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <stdint.h>

#include "MadgwickAHRS.h"
#include "MadgwickAHRS_fix.h"

// Register addresses and bits as per the MPU-6050 datasheet
// http://43zrtwysvxb2gf29r5o0athu.wpengine.netdna-cdn.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf

#define MPU_PWR_MGMT_1 0x6B
#define MPU_TEMP_DIS (1 << 3)
#define MPU_CLK_PLL_ZGYRO 3

#define MPU_CONFIG 0x1A
#define MPU_SMPRT_DIV 0x19

#define MPU_GYRO_CONFIG 0x1B
#define MPU_ACCEL_CONFIG 0x1C

#define MPU_INT_PIN_CFG 0x37
#define MPU_INT_LEVEL (1 << 7)
#define MPU_INT_OPEN (1 << 6)
#define MPU_INT_RD_CLEAR (1 << 4)

#define MPU_INT_ENABLE 0x38
#define MPU_DATA_RDY_EN 1
#define MPU_MOT_EN (1 << 6)

#define MPU_INT_STATUS 0x3A
#define MPU_DATA_RDY_INT 1

#define MPU_ACCEL_XOUT_H 0x3B
#define MPU_ACCEL_XOUT_L 0x3C
#define MPU_ACCEL_YOUT_H 0x3D
#define MPU_ACCEL_YOUT_L 0x3E
#define MPU_ACCEL_ZOUT_H 0x3F
#define MPU_ACCEL_ZOUT_L 0x40

#define MPU_TEMP_OUT_H 0x41
#define MPU_TEMP_OUT_L 0x42

#define MPU_GYRO_XOUT_H 0x43
#define MPU_GYRO_XOUT_L 0x44
#define MPU_GYRO_YOUT_H 0x45
#define MPU_GYRO_YOUT_L 0x46
#define MPU_GYRO_ZOUT_H 0x47
#define MPU_GYRO_ZOUT_L 0x48

#define MPU_WHO_AM_I 0x75

#define MPU_ACC_X 0
#define MPU_ACC_Y 1
#define MPU_ACC_Z 2
#define MPU_GYRO_X 3
#define MPU_GYRO_Y 4
#define MPU_GYRO_Z 5

typedef struct {
    // Lowpass filter bandwidth
    // 0 = 260 Hz
    // 1 = 184 Hz
    // 2 = 94 Hz
    // 3 = 44 Hz
    // 4 = 21 Hz
    // 5 = 10 Hz
    // 6 = 5 Hz
    uint8_t lowpass;
    uint8_t sampleRateDivider;
    // Gyro full scale range
    // 0 = +- 250 deg/s
    // 1 = +- 500 deg/s
    // 2 = +- 1000 deg/s
    // 3 = +- 2000 deg/s
    uint8_t gyroRange;
    // Accelerometer full scale range
    // 0 = +- 2 g
    // 1 = +- 4 g
    // 2 = +- 8 g
    // 3 = +- 16 g
    uint8_t accelRange;
    bool enableInterrupt;
    bool intActiveLow;
    bool intOpenDrain;
    float beta;
    float gyroScale;
    float gyroIntegrationFactor;
    float correctedBeta;
    q16 beta_fix;
    q16 correctedBeta_fix;
    q16 gyroIntegrationFactor_fix;
} mpuconfig;

/* mpuconfig mpuDefaultConfig = {
    .lowpass = 3,
    .sampleRateDivider = 4,
    .gyroRange = 3,
    .accelRange = 0,
    .enableInterrupt = true,
    .intActiveLow = false,
    .intOpenDrain = false,
    .beta = 0.1f
}; */

#ifndef M_PI
    #define M_PI 3.14159265358979323846f
#endif

int mpuReadIntStatus(const uint8_t addr);
int mpuReadRawData(const uint8_t addr, int16_t * const data);
void mpuApplyOffsets(int16_t * const data, const int16_t * const offsets);
int mpuSetup(const uint8_t addr, mpuconfig * const config);
void mpuUpdateQuaternion(const mpuconfig * const config, int16_t * const data,
    quaternion * const q);
void mpuUpdateQuaternion_fix(const mpuconfig * const config, int16_t * const data,
    quaternion_fix * const q);

