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
#define IN_PIN 4

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
	bool start_INTR = 0;
	
	while(true)
	{
		start_INTR = 1;
		if ((xQueueReceive(interruptQueue, &pinNumber, portMAX_DELAY)) && (start_INTR))  
		{
			start_INTR = 0;
			printf("GPIO %d is pressed %d times, pin state %d\n",pinNumber, count++, gpio_get_level(IN_PIN));
		}
	}	
}

void app_main(void)
{
	//gpio configuration
	gpio_set_direction(IN_PIN, GPIO_MODE_INPUT);
	gpio_pulldown_en(IN_PIN);
	gpio_pullup_dis(IN_PIN);
	gpio_set_intr_type(IN_PIN, GPIO_INTR_POSEDGE);
	
	
	//declaring size for the interrupt Queue
	interruptQueue = xQueueCreate(10, sizeof(int));
	xTaskCreate(buttonPushedTask, "buttonPushedTask", 2048, NULL, 1, NULL);
	
	//ISR configuration for GPIO interrupt
	gpio_install_isr_service(0);
	gpio_isr_handler_add(IN_PIN, gpio_isr_handler, (void *)IN_PIN);
	
    while (true) {
        printf("Hello from app_main!\n");
        sleep(2);
    }
}
