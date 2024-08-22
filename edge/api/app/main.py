from fastapi import FastAPI, Request
from fastapi.responses import JSONResponse
import paho.mqtt.client as mqtt
import threading
import json

app = FastAPI()

# MQTT Configuration
MQTT_BROKER = "mqtt"
MQTT_PORT = 1883

# List to store messages
messages = {}

def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    for topic in userdata['topics']:
        client.subscribe(topic)

def on_message(client, userdata, msg):
    topic = msg.topic
    message = json.loads(msg.payload.decode())
    print(f"Received message on {topic}: {message}")
    if topic not in messages:
        messages[topic] = []
    messages[topic].append(message)
    if len(messages[topic]) > 10:  # Keep only the last 10 messages per topic
        messages[topic].pop(0)

def create_thread_for_topic(topic):
    client = mqtt.Client(userdata={'topics': [topic]})
    client.username_pw_set('admin', 'admin')  # Set the username and password
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect(MQTT_BROKER, MQTT_PORT, 60)
    
    thread = threading.Thread(target=client.loop_forever)
    thread.start()
    print(f"MQTT client running for topic: {topic}")
    
create_thread_for_topic("topic/test1")
create_thread_for_topic("topic/test2")

@app.get("/outbox", response_class=JSONResponse)
async def read_messages():
    return {"messages": messages}