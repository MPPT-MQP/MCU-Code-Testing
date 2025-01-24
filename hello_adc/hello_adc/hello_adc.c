// /**
//  * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
//  *
//  * SPDX-License-Identifier: BSD-3-Clause
//  */

// #include <stdio.h>
// #include "pico/stdlib.h"
// #include "hardware/gpio.h"
// #include "hardware/adc.h"
// #include <math.h>


// #define tmp_offset 0.5
// #define tmp_scaling 0.01


// int main() {
//     stdio_init_all();
//     printf("ADC Measurements: \n");

//     adc_init(); 

//     // Make sure GPIO is high-impedance, no pullups etc
//     adc_gpio_init(26);
//     // Select ADC input 0 (GPIO26)
//     adc_select_input(0);

//     while (1) {
//         // 12-bit conversion, assume max value == ADC_VREF == 3.3 V
//         const float conversion_factor = 3.3f / (1 << 12);

        
//         // ADC reading of raw input
//         uint16_t result = adc_read();
        

//         // voltage = result * 3.3 / 4095, temperature = (voltage - offset) / scaling -> offset = 0.5 Volts & scaling = 0.1 mV/Celsius
//         printf("Raw value: 0x%03x, voltage: %f V, temperature: %f\n", result, result * conversion_factor, ((result * conversion_factor) - tmp_offset) / tmp_scaling );
//         sleep_ms(500); 
//     }
// }


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

#define tmp_offset 0.5
#define tmp_scaling 0.01
#define NUM_SAMPLES 20 // Number of samples to average

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

        uint32_t sum = 0; // Variable to store the sum of ADC readings

        // Take multiple ADC readings and sum them
        for (int i = 0; i < NUM_SAMPLES; i++) {
            sum += adc_read();
            sleep_ms(10); // Small delay between samples
        }

        // Calculate the average result
        uint16_t avg_result = sum / NUM_SAMPLES;

        // Calculate voltage and temperature using the averaged result
        float voltage = avg_result * conversion_factor;
        float temperature = (voltage - tmp_offset) / tmp_scaling;

        // Print the averaged values
        printf("Average Raw value: 0x%03x, voltage: %f V, temperature: %f °C\n", avg_result, voltage, temperature);

        sleep_ms(500); // Main delay

        
    }
}
