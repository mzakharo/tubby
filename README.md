# Hot Tub/Spa & Pool Water Quality Sensor

- Solar powered
- ORP & pH (Optional) Sensors
- Estimates Sanitizer ppm (Optional)
- [Home Assistant](https://www.home-assistant.io/) Integration
- [Firmware](https://github.com/mzakharo/tubby/blob/main/tubby.yaml) is using [esphome](https://esphome.io/index.html)

<img src="https://github.com/mzakharo/tubby/blob/main/pictures/esphome.png" width="150" height="400"><img src="https://github.com/mzakharo/tubby/blob/main/pictures/final.jpg" width="250" height="400"> 

## Log
 - Update May 2025: I removed pH probe (3rd broke in 2 years) in December and have been running on just ORP measurements (ORP probe has been much more reliable). Once ORP measurement goes outside the 'green' table range, perform manual pH & alkalinity measurement, balance, then balance ORP with sanitizer. I think pH probe is not worth the cost/hassle in replacement - convenience it adds is marginal, since you still need to measure alkalinity manually. 
 - Update Dec 2024: Replaced worn-out ORP probe and added SMA Panel adapter. Decreased sampling rate to 1/hour to help battery last when there is little sunshine. 


## Hardware  
 - [UM FeatherS2](https://unexpectedmaker.com/shop/feathers2-esp32-s2) ESP32 board from [here](https://www.adafruit.com/product/4769) 
 - [2500 mAh](https://www.adafruit.com/product/328)
 - Atlas Scientific Gravity Analog [ORP](https://atlas-scientific.com/kits/gravity-analog-orp-kit/) and [pH](https://atlas-scientific.com/kits/gravity-analog-ph-kit/) Kits
 - Enclosure: [DS-AT-0811-S](https://www.adafruit.com/product/3931)
 - Waterproof SMA Panel Adapter [SMA-ADP](https://atlas-scientific.com/connectors/sma-adapter/)
 - [2x100 kΩ resistors](https://www.adafruit.com/product/2787) for battery monitoring (optional)
### Solar Panel Components
 - [Adafruit Universal USB / DC / Solar Lithium Ion/Polymer charger - bq24074](https://www.adafruit.com/product/4755)
 - [3.5mm / 1.1mm to 5.5mm / 2.1mm DC Jack Adapter](https://www.adafruit.com/product/4287)
 - [Small 6V 1W Solar Panel](https://www.adafruit.com/product/3809)
 - [JST-PH 2-pin Jumper Cable](https://www.adafruit.com/product/4714)
 
 ## Wiring
  - [Diagram](https://raw.githubusercontent.com/mzakharo/tubby/main/pictures/tubby_wiring.png)
  - NOTE: You can skip the ambient sensor removal step
 
## [Firmware](https://github.com/mzakharo/tubby/blob/main/tubby.yaml)
  - Install [Python](https://www.python.org/downloads/) (Tested 3.13.3)
  - Open Command Prompt (cmd.exe on Windows)
  - `pip install esphome==2024.12.4`
  - copy `wifi_example.yaml` to `wifi.yaml` and edit the new file
  - Connect the board via USB and enter `esphome run tubby.yaml` on the command line. This will build and upload firmware to the board.
  - In Home Assistant, create a helper switch `input_boolean.ota`. Enable this switch, it will prevent device `Deep` sleep.
  - Power cycle the board, Device then enters `Light` sleep for `15 minutes` before it shows up in Home Assistant
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



