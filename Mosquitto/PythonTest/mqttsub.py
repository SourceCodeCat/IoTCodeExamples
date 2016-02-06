#!/usr/bin/python
import paho.mqtt.client as paho
import subprocess

class MqttSub(object):

    def __init__(self):

        self.client = paho.Client()
        self.client.on_message = self.on_message
        self.client.connect("test.mosquitto.org", 1883, 60)

    def on_message(self, mosq, obj, msg):
        print "msg.topic"
	data = msg.topic.split("/")
	command = data[1] + "=" + data[2] + "/" + data[3] + ";"
	send = "python send_command.py --target %s --command %s" % ("00:05:02:03:14:E9",command)
        print send
	subprocess.call(send, shell=True)

    def listen(self):
        self.client.subscribe("IoT/#", 0)
        while self.client.loop() == 0:
            pass
        print "HELLO"
mqttpub = MqttSub()
mqttpub.listen()

# End of File
