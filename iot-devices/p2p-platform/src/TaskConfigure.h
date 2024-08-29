#ifndef TASK_CONFIGURE_H
#define TASK_CONFIGURE_H

#include <TaskScheduler.h>

// External declarations for global variables used in tasks
extern Scheduler runner;

// Task function declarations
void storeState_FlameSensor();
void storeState_DHTSensor();
void storeState_Relays();
void logAndClearState();

// Task objects
Task tStoreState_FlameSensor(1000, TASK_FOREVER, &storeState_FlameSensor);
Task tStoreState_DHTSensor(2000, TASK_FOREVER, &storeState_DHTSensor);
Task tStoreState_Relays(1000, TASK_FOREVER, &storeState_Relays);
Task tLogAndClearState(10000, TASK_FOREVER, &logAndClearState);

// Function to configure and add tasks to the scheduler
void configureTasks()
{
    runner.addTask(tStoreState_FlameSensor);
    runner.addTask(tStoreState_DHTSensor);
    runner.addTask(tStoreState_Relays);
    runner.addTask(tLogAndClearState);

    // Start tasks
    tStoreState_FlameSensor.enable();
    tStoreState_DHTSensor.enable();
    tStoreState_Relays.enable();
    tLogAndClearState.enable();
}

#endif
