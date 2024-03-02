# Hot Tub/Spa & Pool Water Quality Sensor

- Solar powered
- ORP & pH Sensors
- Estimates Sanitizer ppm
- [Home Assistant](https://www.home-assistant.io/) Integration
- [Firmware](https://github.com/mzakharo/tubby/blob/main/tubby.yaml) is using [esphome](https://esphome.io/index.html)

<img src="https://github.com/mzakharo/tubby/blob/main/pictures/esphome.png" width="150" height="400"><img src="https://github.com/mzakharo/tubby/blob/main/pictures/final.jpg" width="250" height="400"> 

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
  - Install [esphome](https://esphome.io/guides/installing_esphome) (Tested Version: 2023.12.5)
  - copy `wifi_example.yaml` to `wifi.yaml` and edit the new file
  - Connect the board via USB and enter `esphome run tubby.yaml`
  - In Home Assistant, create a helper switch `input_boolean.ota`. Enable this switch, it will prevent device sleep.
  - Once your esphome device is added to Home Assistant, Use Device's page, Diagnostics section to calibrate the probes:
     - `ORP Cal` : mV ORP calibration offset from raw ADC value. Note: `ORP` mV Sensor value has calibration applied
     - `pH 10 Cal`: mV reading from `pH Raw` sensor while submerged in pH 10 calibration solution
     - `pH 7 Cal`: mV reading from `pH Raw` sensor while submerged in pH 7 calibration solution
     - `pH 4 Cal`: mV reading from `pH Raw` sensor while submerged in pH 4 calibration solution
     - `ppm Factor`: 1 - Chlorine, 3 - Bromine
  - Turn off `input_boolean.ota` to allow the device to save some power.
  - Place the probes in the water, and enjoy!

## Sanitizer ppm Model

- pH + ORP -> Chlorine ppm [Conversion Table](https://github.com/mzakharo/tubby/blob/main/charts/servovendi.png)
- [Machine Learning Notebook](https://github.com/mzakharo/tubby/blob/main/fc_model.ipynb)
- Generate .h file from .tflite: `xxd -i model_fc.tflite > model_fc.h`



