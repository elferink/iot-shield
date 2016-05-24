## Workshop Internet of Things

Volg deze handleiding om snel wat leuks met je iota bordje te kunnen ontwikkelen! 

**Voor de workshop**

Installeer de volgende software **voordat de workshop begint**:

- Download en installeer de laatste Arduino IDE (nu 1.6.9) voor jouw OS. Link: [installs@Google Drive](https://drive.google.com/folderview?id=0BySKoKNET9qkZlQxTGVXdlo1b0k)
- Installeer de driver voor de USB-chip van het ESP8266 bordje (alleen nodig voor Mac en Windows). Deze staan in dezelfde directory als de Arduino IDE.
- Start de Arduino IDE en ga `Arduino`, `Preferences` en vul bij `Additional Boards Manager URLs` dit in: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
- Ga naar `Tools`, `Board: ..`, `Boards Manager` en zoek hier op 'esp8266'. Installeer de laatste versie (2.2.0).
- Selecteer onder `Tools`, `Board`, `WeMoS D1 R2 & mini`
- Nu heb je een aantal libraries nodig. Download de *3* ZIP-files uit de directory en voeg deze toe aan de Arduino IDE via `Sketch`, `Include library`, `Add .ZIP Library`. 
	- [Libraries@Google Drive](https://drive.google.com/folderview?id=0B8pTpNZu7QutWDUyU2FjX2xZT2M)
- We hebben een testsketch gemaakt, download deze hier: [iota-workshop.zip](https://drive.google.com/uc?export=download&id=0B8pTpNZu7QutcUxvRGRIRVBrdFU). Pak de ZIP-file uit en open het `iota-workshop.ino` bestand met de Arduino IDE.
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
