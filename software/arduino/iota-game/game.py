#!/usr/bin/python -u
#
# This simple backend forwards MQTT-messages to Adafruit IO
#
import paho.mqtt.client as paho
import os, time, random

game = dict(
    nr = 0
)
mqtt_client = object()
state = dict()

def on_message(mqtt_client, userdata, msg):
    global game
    
    print("Got message, topic {} payload {}".format(msg.topic, str(msg.payload)))
    if msg.topic.startswith("game/clients/") :
        if str(msg.payload) == "0":
            if game['clients'] > 0:
                game['clients']-=1
        elif str(msg.payload) == "1":
            game['clients']+=1    
    if game['state'] == state['GO'] or game['state'] == state['FINISHED']:    
        if msg.topic.startswith("game/"+str(game['nr'])+"/score") :
            curr_player = msg.topic.replace("game/"+str(game['nr'])+"/score/","")
            print "curr_player: %s" % curr_player
            if game['winner'][1] == 0:
                game['winner'][0] = curr_player
                game['winner'][1] = int(msg.payload)
            if int(msg.payload) < game['winner'][1]:
                old_winner = game['winner'][0]
                game['winner'][0] = curr_player
                game['winner'][1] = int(msg.payload)
                print "%s lost to %s" % (old_winner, game['winner'][0])
            
    
def game_new():
    global game
    
    game = dict(
        nr =  game['nr']+1,
        state = state['WAIT_FOR_CLIENTS'],
        clients = 0,
        loop_counter_ready = -1,
        loop_counter_go = 5,
        loop_counter_finished = 10,
        loop_counter_clients = 5,
        winner = ['',0]
    )
    
    mqtt_client.publish("game/number", str(game['nr']), 2, True)
    mqtt_client.subscribe("game/"+str(game['nr'])+"/#")
    mqtt_client.subscribe("game/clients/+")
    
def game_wait_for_clients():
    global game
    if game['loop_counter_clients'] == 0:
        game['state'] = state['COUNTDOWN']
        game['loop_counter_clients'] = 5
        return
    if game['clients'] < 1:
        print "WAIT_FOR_CLIENTS for more clients (%d clients)" % game['clients']
        game['loop_counter_clients'] = 5
    else:
        game['loop_counter_clients']-=1
        print "Starting in %d" % game['loop_counter_clients']
            
def game_countdown():
    if game['loop_counter_ready'] == -1:
        print "COUNTDOWN"
        mqtt_client.publish("game/"+str(game['nr'])+"/status", "COUNTDOWN", 2, True)
        game['loop_counter_ready'] = random.randint(2,4);
        return
    elif game['loop_counter_ready'] == 0:
        game['state'] = state['GO']
        game['loop_counter_ready'] = -1
    else:
        game['loop_counter_ready'] -= 1
            
def game_go():
    if game['loop_counter_go'] == 0:
        print "GO"
        mqtt_client.publish("game/"+str(game['nr'])+"/status", "GO", 2, True)
        game['loop_counter_go']-=1
    elif game['loop_counter_go'] > 0:
        game['loop_counter_go']-=1
    elif game['loop_counter_go'] == -1:
        game['loop_counter_go'] = 5
        game['state'] = state['FINISHED']
    
def game_finished():
    if game['loop_counter_finished'] == 0:
        print "FINISHED"
        mqtt_client.publish("game/"+str(game['nr'])+"/status", "FINISHED", 2, True)
        mqtt_client.publish("game/"+str(game['nr'])+"/winner", game['winner'][0], 2, True)
        print "and the game['winner'] is...... %s" % game['winner'][0]
        game['loop_counter_finished']-=1
        return
    elif game['loop_counter_finished'] > 0:
        game['loop_counter_finished']-=1
    elif game['loop_counter_finished'] == -1:
        game_new()

        
def game_loop():
    game['state']()
    time.sleep(1)


#init code
mqtt_client = paho.Client("gameclient_"+str(os.getpid()), False) # False = nocleanstart
mqtt_client.on_message = on_message
mqtt_client.connect("mqtt.topicusonderwijs.nl", 1883)

state = dict(
    WAIT_FOR_CLIENTS=game_wait_for_clients,
    COUNTDOWN=game_countdown,
    GO=game_go,
    FINISHED=game_finished
)

game_new()

while True:
    game_loop()
    mqtt_client.loop()