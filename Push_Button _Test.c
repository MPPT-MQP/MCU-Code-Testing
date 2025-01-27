#include <stdio.h>
#include "pico/stdlib.h"

#define LED_PIN 18
#define BUTTON_PIN 16

int main() {
    // Initialize GPIO pins
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN); // Enable internal pull-up resistor

    bool led_state = false;

    while (true) {
        // Check if the button is pressed
        if (gpio_get(BUTTON_PIN) == 0) {
            // Toggle LED state
            led_state = !led_state;
            gpio_put(LED_PIN, led_state);

            // Wait for button release
            while (gpio_get(BUTTON_PIN) == 0);
        }

        sleep_ms(10); // Debounce delay
    }

    return 0;
}
