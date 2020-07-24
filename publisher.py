import paho.mqtt.client as mqtt


def on_connect(client, userdata, flags, result_code):
    print('Connected')


def get_in():
    print()

    height = float(input('Height level (0-1): '))
    width = float(input('Width level (0-1): '))
    pos = input('Pos (coords): ')

    return height, width, pos


print('Starting mqtt...')

try:
    client = mqtt.Client()
    client.on_connect = on_connect
    client.connect('broker.hivemq.com', 1883, 60)

    height, width, pos = get_in()

    while True:
        print("Sending values..")
        client.publish('heim:trash-levels', str(f"h:{height} w:{width} p:{pos}"))
        height, width, pos = get_in()
except KeyboardInterrupt:
    print("\nBye!")
