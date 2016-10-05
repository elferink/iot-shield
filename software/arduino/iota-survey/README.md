**Survey sketch**

This sketch uses multiple iota's to create a voting system. Flash multiple iota's with different survey\_node\_id's and the same survey_id. 

This still needs a backend to store the voting data, see backend.py for a simple example that forwards data to Adafruit IO.

**MQTT Topics**

| topic  | values  | description  | 
|---|---|---|
| survey/*{uuid}*/actions/enabled  |  0-1 | survey is active  |
| survey/*{uuid}*/actions/vote  |  *{node number}* *{vote value}* | cast a vote |
| survey/*{uuid}*/nodes/*{node number}*/runtime/state  |  0-1 | online or offline  |
| survey/*{uuid}*/nodes/*{node number}*/runtime/vote  |   .* | vote value
| survey/*{uuid}*/nodes/*{node number}*/config/color  |  #000000-#FFFFFF | led color  |
| survey/*{uuid}*/nodes/*{node number}*/config/value  |  .* | vote value  |
