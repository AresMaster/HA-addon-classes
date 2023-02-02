from paho.mqtt import client as mqtt_client

broker = 'localhost'
port = 1883
topic_orno = "switch/orno"
topic_makegood = "switch/makegood"
topic_makegood = "switch/orno_dimmer"
# generate client ID with pub prefix randomly
client_id = f'monitoring-mqtt'
# username = 'emqx'
# password = 'public'

def on_message(client, userdata, msg):
    print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
    else:
        print("Failed to connect, return code %d\n", rc)
def connect_mqtt() -> mqtt_client:
    client = mqtt_client.Client(client_id)
	client.connect(broker, port)
    client.username_pw_set(username, password)
    client.on_connect = on_connect
    return client


def subscribe(client: mqtt_client):
    client.subscribe(topic)
    client.on_message = on_message


def run():
    client = connect_mqtt()
    subscribe(client)
    client.loop_forever()


if __name__ == '__main__':
    print("START MAIN")
    run()