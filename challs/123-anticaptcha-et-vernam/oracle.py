#!/usr/bin/env python3

from websocket import WebSocket
from json import loads
from sys import argv
from guess import *

L = "e"

ws = WebSocket()
ws.connect("ws://lab.algonics.net/anticaptcha/ws")

# Super
print(ws.recv())


while True:
	msg = " ".join(argv[1:])
	m = "{{\"message\": \"{}\"}}".format(msg)
	ws.send(m)

	r = ws.recv()
	r = loads(r)
	challenge = r["challenge"]
	response = int(challenge, 13)
	# print("Challenge: {}, reponse: {}".format(challenge, response))

	m = "{{\"reponse\": \"{}\"}}".format(response)
	ws.send(m)

	r = ws.recv()
	r = loads(r)
	cipher = r["ciphertext"]

	if cipher[0] == L:
		print(cipher)
		break

ws.close()
