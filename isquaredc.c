#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define MPU6050_ADDR 0x68
#define I2C_PORT i2c0

void mpu6050_init(void) {
    sleep_ms(1000); // Allow MPU6050 to power up

    // WHO_AM_I check
    uint8_t who_am_i_reg = 0x75;
    uint8_t who_am_i = 0;
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, &who_am_i_reg, 1, true);
    i2c_read_blocking(I2C_PORT, MPU6050_ADDR, &who_am_i, 1, false);

    if (who_am_i != 0x68) {
        while (1) {
            printf("MPU6050 not found! WHO_AM_I = 0x%02X\n", who_am_i);
            sleep_ms(2000);
        }
    }

    // Wake up device (write 0 to PWR_MGMT_1)
    uint8_t init_data[] = {0x6B, 0x00};
    i2c_write_blocking(I2C_PORT, MPU6050_ADDR, init_data, 2, false);
    printf("MPU6050 initialized successfully\n");
}

int main(void) {
    stdio_init_all();
    sleep_ms(1000); // Wait for USB serial to connect

    i2c_init(I2C_PORT, 400000);
    gpio_set_function(4, GPIO_FUNC_I2C); // SDA
    gpio_set_function(5, GPIO_FUNC_I2C); // SCL
    gpio_pull_up(4);
    gpio_pull_up(5);

    mpu6050_init();

    uint8_t reg = 0x3B; // Start of accelerometer data
    uint8_t accel_data[6];
    int16_t accelX, accelY, accelZ;
    float f_accelX, f_accelY, f_accelZ;

    while (1) {
        i2c_write_blocking(I2C_PORT, MPU6050_ADDR, &reg, 1, true);
        i2c_read_blocking(I2C_PORT, MPU6050_ADDR, accel_data, 6, false);

        accelX = (accel_data[0] << 8) | accel_data[1];
        accelY = (accel_data[2] << 8) | accel_data[3];
        accelZ = (accel_data[4] << 8) | accel_data[5];

        f_accelX = accelX / 16384.0;
        f_accelY = accelY / 16384.0;
        f_accelZ = accelZ / 16384.0;

        printf("X: %6.2f g   Y: %6.2f g   Z: %6.2f g\n", f_accelX, f_accelY, f_accelZ);
        sleep_ms(300);
    }
}
