#include "driver/gpio.h"
#include "hal/gpio_types.h"
#include <stdio.h>
#include <stdbool.h>
#include <sys/unistd.h>
#include <unistd.h>

#define OUT_PIN 2

void app_main(void)
{
	bool LED_STATE = 0;
	printf("HI from esp32 :)\n");
	gpio_set_direction(OUT_PIN, GPIO_MODE_OUTPUT);
    
    while (true) {
		gpio_set_level(OUT_PIN, LED_STATE);
		sleep(2);
		LED_STATE = !LED_STATE;
    }
}