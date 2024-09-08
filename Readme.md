Activity

```
Publish Activity for Publish Data
{
    "id": "" #uuid
    "type": "Publish" # activity types
    "controller_id": "" #controller_uuid
    "device_type": "" # temperature, flame, humidity,...
    "device_id": "" # device_uuid
    "value":  # depend_ons device type 
    "to": [] # multiple gateways {edge_ip}:1883/{collection_type}/{collection_uuid} or {cloud_hostname}:443/{collection_type}/{collection_uuid}
}

Enable/Disable Activity 
{
    "id": "" #uuid
    "type": "Enable" # activity types
    "controller_id": "" #controller_uuid
    "device_type": "" # temperature, flame, humidity,...
    "device_id": "" # device_uuid
    "value":  # depend_ons device type 
    "to": [] # multiple gateways {edge_ip}:1883/{collection_type}/{collection_uuid} or {cloud_hostname}:443/{collection_type}/{collection_uuid}
}
```

ActivitiesCollection 
```
{
    "id": "" #uuid
    "type": "" #collection_type SensorCollection, ActuatorCollectio, ControllerCollection,...
    "items": [] # array of activties
}
```