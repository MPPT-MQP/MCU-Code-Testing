/*
 *  Include Generic Header Files Here
 */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "mcu.h"

#include "pico/stdlib.h"
#include "hardware/i2c.h"

/*
 *  Include MCU Specific Header Files Here
 */

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
//#define I2C_SDA 4
//#define I2C_SCL 5

#define I2C_SDA 4
#define I2C_SCL 5


/*
 *  Include MCU Specific Header Files Here
 */

/********* MCU SPECIFIC I2C CODE STARTS HERE **********/

void mcu_i2cInit(uint8_t busId)
{
    /* Add MCU specific init necessary for I2C to be used */
    i2c_init(i2c0, 400*1000);
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
}

int8_t mcu_i2cTransfer( uint8_t busId, uint8_t i2cAddr,
                        uint8_t *dataToWrite, uint8_t writeLength,
                        uint8_t *dataToRead,  uint8_t readLength)
{
    /*
     *  Add MCU specific I2C read/write code here.
     */
    if(dataToWrite){
        i2c_write_blocking(i2c0, i2cAddr, dataToWrite, writeLength, true);
    } 
    
    if (dataToRead){
        i2c_read_blocking(i2c0, i2cAddr, dataToRead, readLength, false);
     }
    /*
     *  Add MCU specific return code for error handling
     */

    return (0);
}
/********* MCU SPECIFIC I2C CODE ENDS HERE **********/




/********* MCU SPECIFIC DELAY CODE STARTS HERE ************/
void mcu_msWait(uint16_t msWait)
{
    sleep_ms(msWait);/*
     *  Add MCU specific wait loop for msWait. The unit is in milli-seconds
     */
}

void mcu_usWait(uint16_t usWait)
{
    sleep_us(usWait);
    /*
     *  Add MCU specific wait loop for usWait. The unit is in micro-seconds
     */
}
/********* MCU SPECIFIC DELAY CODE ENDS HERE ************/
