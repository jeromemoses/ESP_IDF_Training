#ifndef timer_application_H
#define timer_application_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "sdkconfig.h"
#include "esp_timer.h"

#define ms_in_us 1000 //1 ms
#define sec_in_us 1000000 //1 sec
#define LED_STATE_NOT_PROVISIONED_TIMER 10
#define LED_TIMER_TIME_OUT 100000 // .1 sec

static void heartbeat_timer_callback(void* arg);
void timer_init(void);

typedef struct timer_count 
{
    uint8_t heart_beat_timer;
    uint8_t LED_timer;
}timer_count_t;

extern timer_count_t timer_count_db;
extern esp_timer_handle_t heartbeat_timer_handle;

#endif