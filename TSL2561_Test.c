#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <math.h>

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_I2C0 i2c0
#define I2C_SDA 4
#define I2C_SCL 5

#define TSL2561_ADDRESS 0x39
#define TSL2561_CONTROL 0x00
#define TSL2561_TIMING 0x01
#define TSL2561_CHAN0_LOW 0xAC
#define TSL2561_CHAN1_LOW 0x0E

int main()
{
    stdio_init_all();
    sleep_ms(5000);

   // Initialize I2C (assuming I2C0 on GPIO0 and GPIO1)
    i2c_init(I2C_I2C0, 100 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Power on the sensor
    uint8_t power_on[2] = {0};
    power_on[0] = TSL2561_CONTROL | 0x80;
    power_on[1] = 0x03;
    i2c_write_blocking(I2C_I2C0, TSL2561_ADDRESS, power_on, 2, false);

    // Set integration time and gain
    uint8_t timing[2] = {0};
    timing[0] = TSL2561_TIMING | 0x80;
    timing[1] = 0x02; 
    i2c_write_blocking(I2C_I2C0, TSL2561_ADDRESS, timing, 2, false);
    sleep_ms(1000);

while(true) {
    // Read data from the sensor
    uint8_t reg_addr[1] = {TSL2561_CHAN0_LOW | 0x80};
    i2c_write_blocking(I2C_I2C0, TSL2561_ADDRESS, reg_addr, 1, false);
    uint8_t data[4] = {0};
    i2c_read_blocking(I2C_I2C0, TSL2561_ADDRESS, data, 4, false);

    // Calculate lux
    float ch0 = (data[1] * 256 + data[0]);
    float ch1 = (data[3] * 256 + data[2]);

    // TODO: Implement lux calculation based on datasheet
    printf("Lux: %.2f\n", ch0);
    sleep_ms(1000);
}

}

