# WeMos IoT shield

<img src="assets/top.png?raw=true" alt="top" width="300"/><img src="assets/bottom.png?raw=true" alt="bottom" width="300"/>

## Features

* Ambient Light Sensor ([TEMT6000X01](http://www.vishay.com/docs/81579/temt6000.pdf))
* Digital temperature sensor ([LM75B](http://www.nxp.com/documents/data_sheet/LM75B.pdf))
* Two [APA102C](https://cpldcpu.files.wordpress.com/2014/08/apa-102c-super-led-specifications-2014-en.pdf) RGB LED
* Yellow LED ([APT2012YC](http://www.kingbrightusa.com/images/catalog/SPEC/APT2012YC.pdf))
* Pushbutton Switch [B3F-4055](https://www.omron.com/ecb/products/pdf/en-b3f.pdf)

## Reference
| Shield     | [WeMos D1 Mini](http://www.wemos.cc/wiki/doku.php?id=en:d1_mini#diagram) | [ESP8266 Arduino Core](https://github.com/esp8266/Arduino) |
|------------|---------------|----------------------|
| TEMT6000X01| A0            | ADC                  |
| nc         | D0            | D16~                 |
| LM75B SCL  | D1            | D5~ SCL              |
| LM75B SDA  | D2            | D4~ SDA              |
| Button     | D3            | D0~                  |
| Yellow LED | D4            | D2~                  |
| APA102 SCK | D5            | D14~ SCK             |
| nc         | D6            | D12~ MISO            |
| APA102 MOSI| D7            | D13~ MOSI            |
| nc         | D8            | D15~ SS              |
