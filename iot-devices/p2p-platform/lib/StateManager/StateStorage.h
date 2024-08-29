#ifndef STATE_STORAGE_H
#define STATE_STORAGE_H

#include <ArduinoJson.h>

class StateStorage
{
private:
    JsonDocument storageDoc;

public:
    // Constructor
    StateStorage(size_t capacity) : storageDoc() {}

    // Method to add sensor state to the storage
    void addState(const char *sensorName, JsonDocument &stateObject);

    // Method to serialize all stored data to a JSON string
    String serializeStorage();

    // Method to clear all stored data
    void clearStorage();

    // Debugging function to print the storage state
    void printStorage();
};

#endif // STATE_STORAGE_H
