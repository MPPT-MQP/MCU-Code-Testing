/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include <math.h>

int main() {
    stdio_init_all();
    printf("ADC Measurements: \n");

    adc_init(); 

    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(26);
    // Select ADC input 0 (GPIO26)
    adc_select_input(0);

    while (1) {
        // 12-bit conversion, assume max value == ADC_VREF == 3.3 V
        const float conversion_factor = 3.3f / (1 << 12);
        const float voltage_multiplier = 427.8;

        // ADC reading of raw input
        uint16_t result = adc_read();
        float voltage = result * conversion_factor;
        float watts_per_meter = voltage * voltage_multiplier;
        
        // voltage = result * 3.3 / 4095, temperature = (voltage - offset) / scaling -> offset = 0.5 Volts & scaling = 0.1 mV/Celsius
        printf("Voltage: %f, Watts Per Meter: %f\n", voltage, watts_per_meter);
        sleep_ms(1000); 
    }
}
