import paho.mqtt.client as mqtt
from prometheus_client import Gauge
from prometheus_client import start_http_server


start_http_server(8000)


def on_connect(client, userdata, flags, result_code):
    print('Connected\n')

    client.subscribe('heim:trash-levels')


gh = Gauge('trash:height', 'Trash level height', ['position'])
gw = Gauge('trash:width', 'Trash level width', ['position'])


def on_message(client, userdata, msg):
    print(f"Message received: {msg.payload}")
    split = msg.payload.decode("utf-8").split(" ")
    height = float(split[0].split(":")[1])
    width = float(split[1].split(":")[1])
    pos = split[2].split(":")[1]

    gh.labels(pos).set(height)
    gw.labels(pos).set(width)


print('Starting mqtt...')

try:
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect('broker.hivemq.com', 1883, 60)

    client.loop_forever()
except KeyboardInterrupt:
    print("\nBye!")
