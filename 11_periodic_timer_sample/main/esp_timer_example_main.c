/* esp_timer (high resolution timer) example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "esp_timer.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "sdkconfig.h"
#include "timer_application.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char* TAG = "APP_MAIN";
int initial_heartbeat = 1;

int heartbeat_interval = 5;

void app_main(void)
{
    timer_init();

    while (1)
    {
        if ((timer_count_db.heart_beat_timer > 0 || initial_heartbeat == 1) && heartbeat_interval > 0)
        {
            initial_heartbeat = 0;
            if (esp_timer_is_active(heartbeat_timer_handle) == false)
            {
                ESP_LOGI(TAG, "starting heartbeat timer");
                esp_timer_start_periodic(heartbeat_timer_handle, heartbeat_interval * sec_in_us);
            }
            ESP_LOGI(TAG, "sending heartbeat");
            timer_count_db.heart_beat_timer = 0;
        }
        
        vTaskDelay(pdMS_TO_TICKS(150)); 
    }
    
}