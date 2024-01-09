# Hot Tub Water Quality Sensor

- Solar powered ORP, pH sensor for Hot Tub/Pool
- Sanitizer ppm model estimate from pH and ORP values
- [Home Assistant](https://www.home-assistant.io/) Integration
- [Firmware](https://github.com/mzakharo/tubby/blob/main/tubby.yaml) is written using [esphome](https://esphome.io/index.html)

<img src="https://github.com/mzakharo/tubby/blob/main/pictures/ha.png" width="800" height="400"> 
<img src="https://github.com/mzakharo/tubby/blob/main/pictures/final.jpg" width="250" height="400"> 

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
  - In Home Assistant, create a helper switch named `ota`. When this switch is enabled, device will not sleep between measurements and can be updated.
  - Once your esphome device is added to Home Assistant, calibrate it with reference solutions `PH_MID_CAL` (pH 7), `PH_LOW_CAL` (pH 4), `PH_HIGH_CAL` (pH 10), `ORP_CAL_OFFSET` (ORP 225) in `tubby.yaml`
  - Reflash your calibrated settings again with `esphome run tubby.yaml`
  - Attach the unit to the Hot Tub, place the probes in the water, and enjoy!

## Sanitizer ppm Model

- Data source:  https://jenfitch.com/free-chlorine-orpmv-vs-ph-new/
- Table Ideal values:  1.0 - 1.5 ppm
- [Notebook](https://github.com/mzakharo/tubby/blob/main/fc_model.ipynb).



