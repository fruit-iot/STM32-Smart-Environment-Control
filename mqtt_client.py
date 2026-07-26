import paho.mqtt.client as mqtt
import json


BROKER="localhost"

PORT=1883


def on_message(client,userdata,msg):


    data=json.loads(
        msg.payload.decode()
    )


    print(
        "收到控制:",
        data
    )



client=mqtt.Client()


client.on_message=on_message


client.connect(
    BROKER,
    PORT,
    60
)



client.subscribe(
    "environment/control"
)


client.loop_forever()