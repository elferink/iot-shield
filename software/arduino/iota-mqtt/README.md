# MQTT & openHAB sketch

This Arduino sketch makes all functionality of the board available through MQTT. This can then be used in openHAB. 

![screenshot](https://www.dropbox.com/s/l0cusurif48ue1f/Screenshot_20160320-132256.png?raw=1
"Screenshot")

## Dependencies

* Arduino Client for MQTT: https://github.com/knolleary/pubsubclient
* LM75 Arduino Library: https://github.com/thefekete/LM75
* FastLED library: https://github.com/FastLED/FastLED

## Topics

Format: ```actuator/<mac>/<item>```

| Topic | Values | Mode | Description |
|---|---|---|---|
| actuator/18-FE-00-01-02-03/state | ON or OFF | Read | Device connected to mqtt server |
| actuator/18-FE-00-01-02-03/light | 0 to 660 | Read | Amount of light, in lux |
| actuator/18-FE-00-01-02-03/temperature | -55 to 125 | Read  |Temperature, in degrees Celsius |
| actuator/18-FE-00-01-02-03/button | ON | Read | Switch button pressed |
| actuator/18-FE-00-01-02-03/led | ON or OFF | Write |Controls the onboard led |
| actuator/18-FE-00-01-02-03/rgb/0 | h,s,v (0-360,0-100,0-100) | Write | Controls first RGB led |
| actuator/18-FE-00-01-02-03/rgb/1 | h,s,v (0-360,0-100,0-100) | Write | Controls second RGB led |
 
## openHAB 

Configure openHAB with the [MQTT binding](https://github.com/openhab/openhab/wiki/MQTT-Binding). Name of the broker = 'home' in this example. 


**Items**

```
Number 	Iota_Temperature	"Temperature [%.1f °C]" <temperature>	{mqtt="<[home:actuator/18-FE-00-01-02-03/temperature:state:default]"}
Number 	Iota_Light			"Light [%.1f lux]"  	<sun>			{mqtt="<[home:actuator/18-FE-00-01-02-03/light:state:default]"}
Switch	Iota_Button			"Button [%s]" 	  						{mqtt="<[home:actuator/18-FE-00-01-02-03button:state:default]"}

Color	Iota_Rgb0			"RGB led 0" 			<hue>  			{mqtt=">[home:actuator/5c-cf-7f-10-7e-2d/rgb/0:command:*:default]"}
Color 	Iota_Rgb1			"RGB led 1" 			<hue>   		{mqtt=">[home:actuator/5c-cf-7f-10-7e-2d/rgb/1:command:*:default]"}

Switch 	Iota_Led			"Led"  					<switch>		{mqtt=">[home:actuator/18-FE-00-01-02-03led:command:*:default]"}

``` 

**Sitemap**

```
sitemap iota label="iota"
{
	Frame {
		Text item=Iota_Button
		Switch item=Iota_Led
		Colorpicker item=Iota_Rgb0
		Colorpicker item=Iota_Rgb1
		Text item=Iota_Light
		Text item=Iota_Temperature
	}
}
```

**Rules**

```
import org.openhab.core.library.types.*
import java.awt.Color

rule "iota button"
when
	Item Iota_Button received update ON 
then
	sendCommand(Toggle_Lamp, ON)
end
```

