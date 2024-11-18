#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "esp_attr.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "hal/gpio_types.h"
#include "portmacro.h"

//Input pin definition
#define IN_PIN 16

//setting a interrupt queue
QueueHandle_t interruptQueue;

static void IRAM_ATTR gpio_isr_handler(void *args)
{
	int pinNumber = (int)args;
	xQueueSendFromISR(interruptQueue, &pinNumber, NULL);
}

void buttonPushedTask (void *parmas)
{
	int pinNumber, count = 0;
	while (true) 
	{
		if (xQueueReceive(interruptQueue, &pinNumber, portMAX_DELAY)) 
		{	
			//disables the interrupt by removing the pin from ISR
			gpio_isr_handler_remove(IN_PIN);
			
			//wait and check for the button to be released
			do {
					vTaskDelay(20 / portTICK_PERIOD_MS);
				}while (gpio_get_level(IN_PIN) == 1);
			
			//print the states on serial
			printf("GPIO %d is pressed %d times, pin state %d\n",pinNumber, count++, gpio_get_level(IN_PIN));	
			
			//re enable the interrupt by adding the gpio into ISR (Interrupt Service Routine)
			gpio_isr_handler_add(IN_PIN, gpio_isr_handler, (void *) pinNumber);				
		}
	}
}

void app_main(void)
{
	//gpio configuration
	// gpio_set_direction(IN_PIN, GPIO_MODE_INPUT);
	// gpio_pulldown_en(IN_PIN);
	// gpio_set_pull_mode(IN_PIN, GPIO_PULLDOWN_ENABLE);
	// gpio_pullup_dis(IN_PIN);
	// gpio_set_intr_type(IN_PIN, GPIO_INTR_POSEDGE);
	
	gpio_config_t config = {
		.intr_type = GPIO_INTR_POSEDGE,
		.mode = GPIO_MODE_INPUT,
		.pull_down_en = 1,
		.pull_up_en = 0,
		.pin_bit_mask = (1ULL << IN_PIN) | (1ULL << 12)};
		
	gpio_config(&config);
	
	
	//declaring size for the interrupt Queue
	interruptQueue = xQueueCreate(10, sizeof(int));
	xTaskCreate(buttonPushedTask, "buttonPushedTask", 2048, NULL, 1, NULL);
	
	//ISR configuration for GPIO interrupt
	gpio_install_isr_service(0);
	gpio_isr_handler_add(IN_PIN, gpio_isr_handler, (void *)IN_PIN);
	
    while (true) {
        printf("RTOS test, Hi from app_main (^._.^) \n");
        sleep(2);
    }
}
