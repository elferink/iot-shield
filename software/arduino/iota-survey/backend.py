#!/usr/bin/python -u
#
# This simple backend forwards MQTT-messages to Adafruit IO
#
import os
import paho.mqtt.client as paho
from Adafruit_IO import *

broker = ""
username = ""
password = ""
port = 0
survey_id = ""  # Example: c933f812-2c71-4bd1-8780-b22e00de42eb

def on_connect(client, userdata, flags, rc):
    topic = "survey/" + survey_id + "/actions/vote"
    client.subscribe(topic)

def on_message(client, userdata, msg):
    parts = msg.payload.split(" ")
    value = parts[1]
    aio.send('survey', value)

aio = Client('') # Insert Adafruit IO key

mypid = os.getpid()
client_uniq = "pubclient_"+str(mypid)
mqttc = paho.Client(client_uniq, False) # False = nocleanstart
mqttc.on_connect = on_connect
mqttc.on_message = on_message
mqttc.username_pw_set(username, password)
mqttc.connect(broker, port)