#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "display.cpp"

int main() {
    stdio_init_all();

    display_gpio_init();
    display_spi_init();
    display_init();

    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(250);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(250);

        printf("Hello, world!\r\n");
    }
}
