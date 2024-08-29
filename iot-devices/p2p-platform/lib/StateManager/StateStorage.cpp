#include "StateStorage.h"

// Method to add sensor state to the storage
void StateStorage::addState(const char *moduleName, JsonDocument &stateObject)
{
    storageDoc[moduleName].add(stateObject);
}

// Method to serialize all stored data to a JSON string
String StateStorage::serializeStorage()
{
    String output;
    serializeJson(storageDoc, output);
    return output;
}

// Method to clear all stored data
void StateStorage::clearStorage()
{
    storageDoc.clear();
}

// Debugging function to print the storage state
void StateStorage::printStorage()
{
    serializeJsonPretty(storageDoc, Serial);
    Serial.println();
}
