# esp_network_mqtt

Sketch for send and receive data over mqtt. Also has small webserver for manual handling of ESP

For self check use python or any GUI mqtt client. Below is sample code to sub/pub from python.

Execute code below BEFORE esp is up to see wether you can receive data FROM esp.

```py
import time
import paho.mqtt.client as paho
import random

broker="broker.emqx.io"

def on_message(client, userdata, message):
    time.sleep(1)
    data = str(message.payload.decode("utf-8"))
    print("received message =", data)

client= paho.Client("isu100123") 
client.on_message=on_message

print("Connecting to broker",broker)
client.connect(broker) 
client.loop_start() 
print("Subcribing")
client.subscribe("lab/leds/strip/state")
time.sleep(1800)
client.disconnect()
client.loop_stop()
```

Execute code below AFTER ESP is up to see wether you can receive data ON esp.
```py
import time
import paho.mqtt.client as client
import random

broker="broker.emqx.io"

client= client.Client('isu10012300')

print("Connecting to broker",broker)
print(client.connect(broker))
client.loop_start() 
print("Publishing")

for i in range(10):
    state = "255000000000255000255000000000255000000000255"
    state = state[i:] + state[:i]
    print(f"state is {state}")
    client.publish("lab/leds/strip/set_leds", state)
    time.sleep(2)
    
client.disconnect()
client.loop_stop()
```

