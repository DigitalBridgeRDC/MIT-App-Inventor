import paho.mqtt.client as mqtt
import random
import time

# MQTT broker details
broker_address = "test.mosquitto.org"
broker_port = 1883

# MQTT topic to publish to
topic = "test_topic"

# Create MQTT client
client = mqtt.Client()

# Connect to the broker
client.connect(broker_address, broker_port)

# Generate and publish random numbers in a loop
while True:
    # Generate a random number
    random_number = random.randint(1, 100)

    # Publish the random number to the broker
    client.publish(topic, str(random_number))

    # Wait for some time before sending the next random number
    time.sleep(1)

# Disconnect from the broker
client.disconnect()
