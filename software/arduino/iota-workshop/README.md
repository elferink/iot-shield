## Workshop Internet of Things

Volg deze handleiding om snel wat leuks met je iota bordje te kunnen ontwikkelen! 

**Voor de workshop**

Installeer de volgende software **voordat de workshop begint**:

- Download en installeer de laatste Arduino IDE (nu 1.6.9) voor jouw OS. Link: [https://www.arduino.cc/en/Main/Software](https://www.arduino.cc/en/Main/Software)
- Installeer de driver voor de USB-chip van het ESP8266 bordje (alleen Mac en Windows). Deze zijn hier te vinden: [http://www.wemos.cc/downloads/](http://www.wemos.cc/downloads/)
- Start de Arduino IDE en ga `Arduino`, `Preferences` en vul bij `Additional Boards Manager URLs` dit in: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
- Ga naar `Tools`, `Board: ..`, `Boards Manager` en zoek hier op 'esp8266'. Installeer de laatste versie (2.2.0).
- We hebben een testsketch gemaakt, download deze hier: [iota-workshop.zip](../../../assets/iota-workshop.zip?raw=true). Pak de ZIP-file uit en open het `iota-workshop.ino` bestand met de Arduino IDE.
- Voor deze sketch heb je een aantal libraries nodig. Download de volgende ZIP-files en voeg deze toe aan de Arduino IDE via `Sketch`, `Include library`, `Add .ZIP Library`. 
	- [LM75 Arduino Library](https://github.com/thefekete/LM75/archive/master.zip)
	- [FastLED](https://github.com/FastLED/FastLED/archive/87211a5a7c2e143b9d172d9ce62151049eb7b7b2.zip)
	- [OneButton](https://github.com/mathertel/OneButton/archive/master.zip)
- Compile de sketch via `Sketch`, `Verify/Compile`. Dit zou nu moeten lukken!
- Tot op de workshop!

**Tijdens de workshop**

Als je eenmaal in het bezit bent van een iota bordje sluit je deze via USB aan. Selecteer vervolgens onder `Tools` de volgende opties (vanaf `Board`):

![Alt text](../../../assets/settings-tools.png?raw=true)

De waarde voor `port` zal per OS verschillen. 

Vervolgens kun je via `Sketch`, `Upload` je code in de ESP8266 laden. 

De testsketch verbindt met wifi en toont initieel de waarde van de twee sensoren. Met de knop je kun je het volgende:

* 1x klikken: led aan/uit
* dubbelklikken: rgb leds aan/uit
* vasthouden: sensorwaarden tonen

Succes!

**Tips**

In de Arduino IDE vind je onder `File`, `Examples` meer voorbeelden van de gebruikte libraries. O.a. `ESP8266HTTPClient` is handig om simpele HTTP requests te doen.