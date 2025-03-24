#include "timer_application.h"
#include "esp_log.h"

timer_count_t timer_count_db;
esp_timer_handle_t heartbeat_timer_handle;

char *TIMER_TAG = "TIMER_APPLICATION";

static void heartbeat_timer_callback(void* arg)
{
    timer_count_db.heart_beat_timer++;
    ESP_LOGI(TIMER_TAG, "heartbeat timer called");
}

void timer_init()
{
    const esp_timer_create_args_t heartbeat_timer_args = {
        .callback = &heartbeat_timer_callback,
        /* name is optional, but may help identify the timer when debugging */
        .name = "heartbeat"};

    ESP_ERROR_CHECK(esp_timer_create(&heartbeat_timer_args, &heartbeat_timer_handle));
    /* The timer has been created but is not running yet */
}