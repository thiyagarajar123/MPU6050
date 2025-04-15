#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "mpu6050.h"

int main(void) {
    stdio_init_all();
    
    // Initialize I2C on GPIO4 (SDA) and GPIO5 (SCL)
    i2c_init(MPU6050_I2C_PORT, 400000);
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(4);
    gpio_pull_up(5);

    // Initialize MPU6050
    mpu6050_init();
    printf("MPU6050 initialized successfully.\n");

    float accelX, accelY, accelZ;

    while (1) {
        mpu6050_read_accel(&accelX, &accelY, &accelZ);

        printf("Accel X: %6.2f g | Y: %6.2f g | Z: %6.2f g\n", accelX, accelY, accelZ);
        sleep_ms(500);
    }

    return 0;
}
