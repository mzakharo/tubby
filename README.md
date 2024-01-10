# Hot Tub Water Quality Sensor

- Solar powered ORP, pH sensor for Hot Tub/Pool
- Sanitizer ppm model estimate from pH and ORP values
- [Home Assistant](https://www.home-assistant.io/) Integration
- [Firmware](https://github.com/mzakharo/tubby/blob/main/tubby.yaml) is written using [esphome](https://esphome.io/index.html)

<img src="https://github.com/mzakharo/tubby/blob/main/pictures/esphome.png" width="205" height="400"><img src="https://github.com/mzakharo/tubby/blob/main/pictures/final.jpg" width="250" height="400"> 

## Hardware  
 - [UM FeatherS2](https://unexpectedmaker.com/shop/feathers2-esp32-s2) ESP32 board from [here](https://www.adafruit.com/product/4769) 
 - [2500 mAh](https://www.adafruit.com/product/328)
 - Atlas Scientific Gravity Analog [ORP](https://atlas-scientific.com/kits/gravity-analog-orp-kit/) and [pH](https://atlas-scientific.com/kits/gravity-analog-ph-kit/) Kits
 - Enclosure: [DS-AT-0811-S](https://www.adafruit.com/product/3931)
 - [2x100 kΩ resistors](https://www.adafruit.com/product/2787) for battery monitoring (optional)
### Solar Panel Components
 - [Adafruit Universal USB / DC / Solar Lithium Ion/Polymer charger - bq24074](https://www.adafruit.com/product/4755)
 - [3.5mm / 1.1mm to 5.5mm / 2.1mm DC Jack Adapter](https://www.adafruit.com/product/4287)
 - [Small 6V 1W Solar Panel](https://www.adafruit.com/product/3809)
 - [JST-PH 2-pin Jumper Cable](https://www.adafruit.com/product/4714)
 
 ## Wiring
  - [Diagram](https://raw.githubusercontent.com/mzakharo/tubby/main/pictures/tubby_wiring.png)
 
## [Firmware](https://github.com/mzakharo/tubby/blob/main/tubby.yaml)
  - Install [esphome](https://esphome.io/guides/installing_esphome)
  - copy `wifi_example.yaml` to `wifi.yaml` and edit the new file
  - Connect the board via USB and enter `esphome run tubby.yaml`
  - In Home Assistant, create a helper switch `input_boolean.ota`. Enable this switch, it will prevent device sleep.
  - Once your esphome device is added to Home Assistant, Use Device's page, Diagnostics section to calibrate the probes
  - Turn off `input_boolean.ota` to allow the device to save some power.
  - Attach the unit to the Hot Tub, place the probes in the water, and enjoy!

## Sanitizer ppm Model

- pH + ORP -> Chlorine ppm [Conversion Table](https://github.com/mzakharo/tubby/blob/main/charts/servovendi.png)- 
- [Machine Learning Notebook](https://github.com/mzakharo/tubby/blob/main/fc_model.ipynb)
- Generate .h file from .tflite: `xxd -i model_fc.tflite > model_fc.h`- 
- Note: Sanitizer Sensor in `tubby.yaml` outputs ppm values multipled by 3 for Bromine



