#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

TaskHandle_t one_handle;
TaskHandle_t two_handle;
TaskHandle_t three_handle;

void *const timer_Id;
TimerHandle_t my_timer_handle;

void myTimerCallback(TimerHandle_t xTimer)
{
    printf("Inside OneShot Timer callback\n");
}

void task_one(void *argument)
{
    while(1)
    {
        printf("IN Task 2\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS );
    }
}

void task_two(void *argument)
{
    while(1)
    {
        printf("IN Task 3\n");
        vTaskDelay(2000 / portTICK_PERIOD_MS );
    }
}

void task_three(void *data)
{

    printf("Created task 3, Periodicity = 5000ms\n");
    my_timer_handle = xTimerCreate(/*timer name*/ "my_timer",
                                   /*timer tick period*/ (10000 / portTICK_PERIOD_MS),
                                   /*autoreload*/ pdFALSE,
                                   /*timer id*/ timer_Id,
                                   /*timer callback function*/ myTimerCallback);

    xTimerStart(my_timer_handle, 1); //here we start the timer
    while (1)
    {
        printf("task3\n");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}


void app_main(void)
{
    
    xTaskCreate(task_one, "tsk_1", 2048, NULL, 5, &one_handle);
    xTaskCreate(task_two, "tsk_2", 2028, NULL, 6, &two_handle);
    xTaskCreate(task_three, "tsk_3", 2028, NULL, 7, &three_handle);
    while (1) 
    {
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
