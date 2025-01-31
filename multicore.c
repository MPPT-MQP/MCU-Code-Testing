// /**
//  * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
//  *
//  * SPDX-License-Identifier: BSD-3-Clause
//  */

// #include <stdio.h>
// #include "pico/stdlib.h"
// #include "pico/multicore.h"

// #define FLAG_VALUE 123

// void core1_entry() {

//     multicore_fifo_push_blocking(FLAG_VALUE);

//     uint32_t g = multicore_fifo_pop_blocking();

//     if (g != FLAG_VALUE)
//         printf("Hmm, that's not right on core 1!\n");
//     else
//         printf("Its all gone well on core 1!");

//     while (1)
//         tight_loop_contents();
// }

// int main() {
//     stdio_init_all();

//     while(true)
//     {

//         printf("Hello, multicore!\n");

//     /// \tag::setup_multicore[]

//     multicore_launch_core1(core1_entry);

//     // Wait for it to start up

//     uint32_t g = multicore_fifo_pop_blocking();

//     if (g != FLAG_VALUE)
//         printf("Hmm, that's not right on core 0!\n");
//     else {
//         multicore_fifo_push_blocking(FLAG_VALUE);
//         printf("It's all gone well on core 0!");
//     }

//     }
//     sleep_ms(500);
//     /// \end::setup_multicore[]
// }



#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/irq.h"
#include "hardware/adc.h"

// Core 1 Interrupt Handler
void core1_interrupt_handler() {
    while (multicore_fifo_rvalid()) {
        uint16_t intpart = multicore_fifo_pop_blocking();
        uint16_t decpart = multicore_fifo_pop_blocking();
        
        float raw = intpart + (decpart / 1000.0);
        float far_temp = raw * 1.8 + 32;
        printf("Core 1: Temp = %.2f F\n", far_temp);
    }

    multicore_fifo_clear_irq(); // Clear the interrupt
}

// Core 1 Main Code
void core1_entry() {
    // Configure Core 1 Interrupt
    multicore_fifo_clear_irq();
    irq_set_exclusive_handler(SIO_FIFO_IRQ_NUM(1), core1_interrupt_handler);
    irq_set_enabled(SIO_FIFO_IRQ_NUM(1), true);

    // Infinite loop waiting for interrupt
    while (1) {
        tight_loop_contents();
    }
}

// Core 0 Main Code
int main() {
    stdio_init_all();
    sleep_ms(2000);  // Allow time for serial initialization

    multicore_launch_core1(core1_entry); // Start Core 1 before sending data

    // Configure ADC for temperature sensor
    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);

    while (1) {
        // Read raw ADC value
        uint16_t raw = adc_read();

        // Convert raw value to Celsius
        const float conversion_factor = 3.3f / (1 << 12);
        float voltage = raw * conversion_factor;
        float temp_c = 27.0f - (voltage - 0.706f) / 0.001721f;

        // Split temperature into integer and decimal parts
        uint16_t intpart = (uint16_t)temp_c;
        uint16_t decpart = (uint16_t)((temp_c - intpart) * 1000);

        printf("Core 0: Temp = %.2f C\n", temp_c);

        // Send data to Core 1
        multicore_fifo_push_blocking(intpart);
        multicore_fifo_push_blocking(decpart);

        // Trigger interrupt on Core 1
        multicore_fifo_drain();

        sleep_ms(1000); // Wait before next reading
    }
}
