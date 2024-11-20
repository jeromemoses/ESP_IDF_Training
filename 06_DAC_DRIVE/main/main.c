#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "driver/dac_continuous.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/dac.h"
#include "hal/dac_types.h"
#include "portmacro.h"

void app_main(void)
{
    dac_output_enable(DAC_CHAN_0);
    while (1) 
    {
		for (int i = 0; i<=255; i++) 
		{	
			dac_output_voltage(DAC_CHAN_0, i);
			vTaskDelay(10 / portTICK_PERIOD_MS);
		}
		for (int i = 255; i>=0; i--) 
		{
			dac_output_voltage(DAC_CHAN_0, i);
			vTaskDelay(10 / portTICK_PERIOD_MS);
		}
	}
}
