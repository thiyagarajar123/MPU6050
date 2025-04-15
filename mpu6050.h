#ifndef MPU6050_H
#define MPU6050_H

#include "hardware/i2c.h"

// MPU6050 default I2C address
#define MPU6050_ADDR             0x68

// MPU6050 register addresses
#define MPU6050_REG_PWR_MGMT_1   0x6B
#define MPU6050_REG_WHO_AM_I     0x75
#define MPU6050_REG_ACCEL_XOUT_H 0x3B

// Sensitivity scale factor for ±2g (default)
#define MPU6050_ACCEL_SCALE      16384.0

// I2C port used
#define MPU6050_I2C_PORT i2c0

// Function to initialize MPU6050
void mpu6050_init(void);

// Function to read raw accelerometer data
void mpu6050_read_accel(float *x, float *y, float *z);

#endif
