import paho.mqtt.client as mqtt

# MQTT broker details
broker_address = "test.mosquitto.org" #URL 
broker_port = 1883

# MQTT topic to publish to
topic = "test_topic"

# Create MQTT client
client = mqtt.Client()

# Connect to the broker
client.connect(broker_address, broker_port)

# Publish data to the broker
message = "24C"
client.publish(topic, message)

# Disconnect from the broker
client.disconnect()
