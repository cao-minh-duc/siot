from dotenv import load_dotenv
import os
from mqtt.database import get_mqtt_topics, get_db

# Load environment variables from .env file (for broker settings)
load_dotenv()

MQTT_BROKER = os.getenv("MQTT_BROKER", "mqtt")
MQTT_PORT = int(os.getenv("MQTT_PORT", 1883))
MQTT_USERNAME = os.getenv("MQTT_USERNAME", "admin")
MQTT_PASSWORD = os.getenv("MQTT_PASSWORD", "admin")

# Fetch topics from the database
def load_topics():
    with next(get_db()) as db:
        return ["edges/3fd7ae10-80f4-462f-8399-8ee8b1c09e23"]
