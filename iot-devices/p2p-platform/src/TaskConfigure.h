#ifndef TASK_CONFIGURE_H
#define TASK_CONFIGURE_H

#include <TaskScheduler.h>
#include <NetworkConfigure.h>

// TaskScheduler
Scheduler runner;

// Task function declarations
void network_CheckWiFiConnection();
void network_CheckMQTTConnection();
void storeState_FlameSensor();
void storeState_DHTSensor();
void storeState_Relays();
void network_PublishStatisticData();

// Task objects
Task tNetwork_CheckWiFiConnection(WIFI_RETRY_INTERVAL, TASK_FOREVER, &network_CheckWiFiConnection);
Task tNetwork_CheckMQTTConnection(MQTT_RETRY_INTERVAL, TASK_FOREVER, &network_CheckMQTTConnection);
Task tStoreState_FlameSensor(1000, TASK_FOREVER, &storeState_FlameSensor);
Task tStoreState_DHTSensor(2000, TASK_FOREVER, &storeState_DHTSensor);
Task tStoreState_Relays(1000, TASK_FOREVER, &storeState_Relays);
Task tLogAndClearState(10000, TASK_FOREVER, &network_PublishStatisticData);

// Function to configure and add tasks to the scheduler
void configureTasks()
{
    runner.addTask(tNetwork_CheckWiFiConnection);
    runner.addTask(tNetwork_CheckMQTTConnection);
    runner.addTask(tStoreState_FlameSensor);
    runner.addTask(tStoreState_DHTSensor);
    runner.addTask(tStoreState_Relays);
    runner.addTask(tLogAndClearState);

    // Start tasks
    tNetwork_CheckWiFiConnection.enable();
    tNetwork_CheckMQTTConnection.enable();
    tStoreState_FlameSensor.enable();
    tStoreState_DHTSensor.enable();
    tStoreState_Relays.enable();
    tLogAndClearState.enable();
}

#endif
