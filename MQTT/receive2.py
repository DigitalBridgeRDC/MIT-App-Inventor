import paho.mqtt.client as mqtt

# MQTT broker details
broker_address = "test.mosquitto.org"
broker_port = 1883

# MQTT topic to subscribe to
topic = "test2"

# Callback function when a new message is received
def on_message(client, userdata, message):
    print("Received message:", message.payload.decode())

# Create MQTT client
client = mqtt.Client()

# Set the message callback
client.on_message = on_message

# Connect to the broker
client.connect(broker_address, broker_port)

# Subscribe to the topic
client.subscribe(topic)

# Start the MQTT loop to process incoming messages
client.loop_start()

# Keep the program running to receive messages
while True:
    pass

# Disconnect from the broker
client.disconnect()
