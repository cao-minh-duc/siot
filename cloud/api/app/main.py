from fastapi import FastAPI, Request
from fastapi.responses import JSONResponse
import json
from mqtt.client import start_mqtt_clients

start_mqtt_clients()
app = FastAPI()

@app.get("/outbox", response_class=JSONResponse)
async def read_messages():
    return {"messages": messages}