#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <time.h>
#include <string.h>


// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C1_PORT i2c0
#define I2C_SDA 4
#define I2C_SCL 5

// PCF8523 RTC Address Define
#define PCF8523_ADDRESS 0x68

/* PCF8523 RTC Functions*/
// From https://github.com/a-mueller/pgico-lib-pcf8523/tree/main

// Time Struct for PCF8523 RTC
struct pcf8523_time_t {
  int8_t second;
  int8_t minute;
  int8_t hour;
  int8_t day;
  int8_t month;
  // last two digits of the year eg 23 for 2023
  // this will fall over in 2100
  int8_t year;
  //0..6, 0 is Sunday
  int8_t dotw;
};

void pcf8523_reset() {
  //write reset to control 1
  uint8_t buf[] = {0x00, 0x58};
  i2c_write_blocking(I2C1_PORT, PCF8523_ADDRESS, buf, 2, false);

  //write to control 3
  uint8_t buf2[] = {0x02, 0x80}; //0x80 is default control3 and setting 100 to turn on battery switch-over function is enabled in standard mode;
                                 //battery low detection function is disabled
 i2c_write_blocking(I2C1_PORT, PCF8523_ADDRESS, buf2, 2, false);
}

/* Convert the time from somewhere into raw bytes the RTC can understand */
void pcf8523_time_to_raw(struct pcf8523_time_t *time, uint8_t *raw) {
  raw[0] = ((time -> second / 10) << 4) | ((time -> second % 10) & 0x0F);
  raw[1] = ((time -> minute / 10) << 4) | ((time -> minute % 10) & 0x0F);
  raw[2] = ((time -> hour / 10) << 4) | ((time -> hour %10) & 0x0F);
  raw[3] = ((time -> day / 10) << 4) | ((time -> day % 10) & 0x0F);
  raw[4] = time -> dotw & 0x07;
  raw[5] = ((time -> month / 10) << 4) | ((time -> month % 10) & 0x0F);
  raw[6] = ((time -> year / 10) << 4) | ((time -> year % 10) & 0x0F);
}

void pcf8523_write(struct pcf8523_time_t *time) {
    // buf[0] is the register to write to
    // buf[1] is the value that will be written to the register
    uint8_t buf[2];

    //Write values for the current time in the array
    //index 0 -> second: bits 4-6 are responsible for the ten's digit and bits 0-3 for the unit's digit
    //index 1 -> minute: bits 4-6 are responsible for the ten's digit and bits 0-3 for the unit's digit
    //index 2 -> hour: bits 4-5 are responsible for the ten's digit and bits 0-3 for the unit's digit
    //index 3 -> day of the month: bits 4-5 are responsible for the ten's digit and bits 0-3 for the unit's digit
    //index 4 -> day of the week: where Sunday = 0x00, Monday = 0x01, Tuesday... ...Saturday = 0x06
    //index 5 -> month: bit 4 is responsible for the ten's digit and bits 0-3 for the unit's digit
    //index 6 -> year: bits 4-7 are responsible for the ten's digit and bits 0-3 for the unit's digit

    //NOTE: if the value in the year register is a multiple for 4, it will be considered a leap year and hence will include the 29th of February

    uint8_t current_val[7];
    pcf8523_time_to_raw(time, current_val);

    for (int i = 3; i < 10; ++i) {
        buf[0] = i;
        buf[1] = current_val[i - 3];
        i2c_write_blocking(I2C1_PORT, PCF8523_ADDRESS, buf, 2, false);
    }
}

void pcf8523_read_raw(uint8_t *buffer) {
    // For this particular device, we send the device the register we want to read
  // first, then subsequently read from the device. The register is auto incrementing
  // so we don't need to keep sending the register we want, just the first.

  // Start reading acceleration registers from register 0x3B for 6 bytes
  uint8_t val = 0x03;
   i2c_write_blocking(I2C1_PORT, PCF8523_ADDRESS, &val, 1, true); // true to keep master control of bus
  int result = i2c_read_blocking(I2C1_PORT, PCF8523_ADDRESS, buffer, 7, false);
  //return (result == 7);

}

/* Convert the raw bytes from the RTC into numbers we can understand */
void pcf8523_raw_to_time(uint8_t *raw_time, struct pcf8523_time_t *time) {
  time -> second = (10 * (int8_t) ((raw_time[0] & 0x70) >> 4)) + ((int8_t) (raw_time[0] & 0x0F));
  time -> minute = (10 * (int8_t) ((raw_time[1] & 0x70) >> 4)) + ((int8_t) (raw_time[1] & 0x0F));
  time -> hour = (10 * (int8_t) ((raw_time[2] & 0x30) >> 4)) + ((int8_t) (raw_time[2] & 0x0F));
  time -> day = (10 * (int8_t) ((raw_time[3] & 0x30) >> 4)) + ((int8_t) (raw_time[3] & 0x0F));
  time -> dotw = (int8_t) (raw_time[4] & 0x07);
  time -> month = (10 * (int8_t) ((raw_time[5] & 0x10) >> 4)) + ((int8_t) (raw_time[5] & 0x0F));
  time -> year = (10 * (int8_t) ((raw_time[6] & 0xF0) >> 4)) + ((int8_t) (raw_time[6] & 0x0F));
}

/* Reads the current time from the RTC */
void pcf8523_read(struct pcf8523_time_t *time) {
  uint8_t raw_time[7];
  pcf8523_read_raw(raw_time);
  pcf8523_raw_to_time(raw_time, time);
}
/*End PCF8523 Functions*/


int main()
{
    stdio_init_all();

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C1_PORT, 400*1000);
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    // For more examples of I2C use see https://github.com/raspberrypi/pico-examples/tree/master/i2c
    struct pcf8523_time_t test;
  
 // time_t rawtime;
 // struct tm * timeinfo;

  int years, months, days, hours, minutes, seconds;

   pcf8523_reset();
   //pcf8523_write(&test);

  char time_buffer[20];

  fgets(time_buffer, sizeof(time_buffer), stdin);
  time_buffer[strcspn(time_buffer, "\n")] = 0; // Remove trailing newlin
  
  sscanf(time_buffer, "%d-%d-%d %d:%d:%d", &years, &months, &days, &hours, &minutes, &seconds);

    test.second = seconds+1;
    test.minute = minutes;
    test.hour = hours;
    test.day = days;
    test.month = months;
    test.year = years-2000;
    //test.dotw = 2;

   pcf8523_write(&test);
 
    while (true) {
 
    pcf8523_read(&test);
    printf("%d-%d-%d %d:%d:%d\n", 
          test.year+2000, test.month, test.day, test.hour, test.minute, test.second);
        //printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
