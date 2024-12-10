#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"


#define LED_PIN 22

/*
 *  ======== main.c ========
 *  Simple example that uses the Sensors APIs
 */
#include "INA740.h"
#include "config.h" /* for sensor handle names */
#include "mcu.h"


int main()
{
    stdio_init_all();

    float current;
    float power;
    float voltage;

    // I2C Initialisation. Using it at 400Khz.
   
    //gpio_pull_up(I2C_SDA);
    //gpio_pull_up(I2C_SCL);
    // For more examples of I2C use see https://github.com/raspberrypi/pico-examples/tree/master/i2c

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_put(LED_PIN, 1);
 
    INA740_config(INA740_0);
    
    while (true) {

        current = INA740_getCURRENT_A(INA740_0);
        voltage = INA740_getVBUS_V(INA740_0); 
        power = INA740_getPOWER_W(INA740_0);

        printf("Current: %0.2f, Voltage: %0.2f, Power: %0.2f\n", current, voltage, power);
        sleep_ms(1000);
    }
}
