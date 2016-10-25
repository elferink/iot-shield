**Game sketch**

Simple game using multiple Iota's. Who's the fastest when the light turns green?

**MQTT Topics**

| topic  | values  | description  | 
|---|---|---|
| game/number | Integer | Game number that is currently active | 
| game/clients/*{mac}* | 0-1 | Active (1) or inactive (0) client | 
| game/*{game number}*/status|  WAITING,COUNTDOWN,GO,FINISHED | Status  |
| game/*{game number}*/score/*{mac}* |  Integer  | Respone time (ms)
| game/*{game number}*/winner  |  xx-xx-xx-xx-xx-xx | Mac address of winning node

