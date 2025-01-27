#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"


int main()
{
    gpio_set_function(0, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(0);

    pwm_set_enabled(slice_num, true);

    pwm_set_wrap(slice_num, 3125);

    pwm_set_chan_level(slice_num, PWM_CHAN_A, 1562);


    while (true) {
        tight_loop_contents();;
    }
}
