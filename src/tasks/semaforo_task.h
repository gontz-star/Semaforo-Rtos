#ifndef GCODE_TASKS_H
#define GCODE_TASKS_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <task.h>
#include "DEBUG_things.h"
//#include "buttons/buttons.h"
#include "common_defs.h"

void taskTouchscreenMenu(void* pvParameters);
void taskSemaforo(void* pvParameters);
void taskDisplaySeg(void* pvParameters);

#endif