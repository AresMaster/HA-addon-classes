import subprocess
from paho.mqtt import client as mqtt_client

broker = '192.168.1.24'
port = 1883
topic_orno = "switch/orno"
topic_makegood = "switch/makegood"
topic_makegood = "switch/orno_dimmer"
# generate client ID with pub prefix randomly
client_id = f'monitoring-mqtt'
username = 'student'
password = 'student123'

def on_message(client, userdata, msg):
    print(f"Received `{msg.payload.decode()}` from `{msg.topic}` topic")
    if msg.topic == topic_orno:
        subprocess.run(["./orno", "1"+msg.payload.decode()])
            
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker! \n")
    else:
        print("Failed to connect, return code "+str(rc)+"\n")
def connect_mqtt() -> mqtt_client:
    client = mqtt_client.Client(client_id)
    client.connect(broker, port)
    client.username_pw_set(username, password)
    client.on_connect = on_connect
    return client


def subscribe(client: mqtt_client):
    #MQTT_TOPIC = [("Server1/kpi1",0),("Server2/kpi2",0),("Server3/kpi3",0)]
    client.subscribe(topic_orno)
    client.on_message = on_message


def run():
    client = connect_mqtt()
    subscribe(client)
    client.loop_forever()


if __name__ == '__main__':
    subprocess.run(["./orno", "11"])
    print("START MAIN")
    run()