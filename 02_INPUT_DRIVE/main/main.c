#include "driver/gpio.h"
#include "hal/gpio_types.h"
#include <stdio.h>
#include <stdbool.h>
#include <sys/unistd.h>
#include <unistd.h>

#define OUT_PIN 2
#define IN_PIN 4

void app_main(void)
{
	//input pin declaration
	gpio_set_direction(IN_PIN, GPIO_MODE_INPUT);
	gpio_pulldown_en(IN_PIN);
	gpio_pullup_dis(IN_PIN);
	int pin_state = 0;
	
	//output pin declaration
	gpio_set_direction(OUT_PIN, GPIO_MODE_OUTPUT);
	
    while (true) {
		pin_state = gpio_get_level(IN_PIN);
    	sleep(1);
    	if(pin_state)
    	{
			gpio_set_level(OUT_PIN, pin_state);
			printf("INPUT detected (*_*) \n");
			sleep(1);	
		}else 
		{
			gpio_set_level(OUT_PIN, 0);
		}
        
    }
}