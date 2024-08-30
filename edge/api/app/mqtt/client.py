import paho.mqtt.client as mqtt
import threading
import json
from mqtt.config import MQTT_BROKER, MQTT_PORT, MQTT_USERNAME, MQTT_PASSWORD, load_topics
import time

# Dictionary to store messages per topic and thread references
messages = {}
threads = {}
clients = {}

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
    
    # Keep only the last 10 messages per topic
    if len(messages[topic]) > 10:
        messages[topic].pop(0)

def start_mqtt_thread(topic):
    client = mqtt.Client(userdata={'topics': [topic]})
    client.username_pw_set(MQTT_USERNAME, MQTT_PASSWORD)  # Set MQTT credentials
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect(MQTT_BROKER, MQTT_PORT, 60)
    
    thread = threading.Thread(target=client.loop_forever)
    threads[topic] = thread
    clients[topic] = client
    thread.start()
    
    print(f"MQTT client running for topic: {topic}")

def stop_mqtt_thread(topic):
    if topic in clients:
        clients[topic].disconnect()
        threads[topic].join()
        del clients[topic]
        del threads[topic]
        print(f"MQTT client stopped for topic: {topic}")

def update_mqtt_clients():
    current_topics = set(load_topics())
    active_topics = set(threads.keys())
    
    # Stop clients for removed topics
    for topic in active_topics - current_topics:
        stop_mqtt_thread(topic)
    
    # Start clients for new topics
    for topic in current_topics - active_topics:
        start_mqtt_thread(topic)

def start_mqtt_clients():
    update_mqtt_clients()
