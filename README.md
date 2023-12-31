# Hot Tub Water Quality Sensor

- Battery powered ORP, pH sensor for Hot Tub/SPA
- Free Chlorine/Total Bromine estimate from pH and ORP values
- [Home Assistant](https://www.home-assistant.io/) Integration
- pH ATC (Automatic Temperature Compensation)
- `2024 update`: Added Solar Panel


<img src="https://github.com/mzakharo/tubby/blob/main/pictures/ha.png" width="800" height="400"> 

<img src="https://github.com/mzakharo/tubby/blob/main/pictures/final.jpg" width="250" height="400">  <img src="https://github.com/mzakharo/tubby/blob/main/pictures/probes.jpg" width="250" height="400">  <img src="https://github.com/mzakharo/tubby/blob/main/pictures/cal.jpg" width="250" height="400">

## Hardware
  
 - [UM FeatherS2](https://unexpectedmaker.com/shop/feathers2-esp32-s2) ESP32 board from [here](https://www.adafruit.com/product/4769) 
 - [2500 mAh](https://www.adafruit.com/product/328)
 - Atlas Scientific Gravity Analog [ORP](https://atlas-scientific.com/kits/gravity-analog-orp-kit/) and [pH](https://atlas-scientific.com/kits/gravity-analog-ph-kit/) Kits
 - Enclosure: [DS-AT-0811-S](https://www.adafruit.com/product/3931)
 - [2x100 kΩ resistors](https://www.adafruit.com/product/2787) for battery monitoring (optional)
### Optional Solar Panel Components
 - [Adafruit Universal USB / DC / Solar Lithium Ion/Polymer charger - bq24074](https://www.adafruit.com/product/4755)
 - [3.5mm / 1.1mm to 5.5mm / 2.1mm DC Jack Adapter](https://www.adafruit.com/product/4287)
 - [Small 6V 1W Solar Panel](https://www.adafruit.com/product/3809)
 - [JST-PH 2-pin Jumper Cable](https://www.adafruit.com/product/4714)
 
 ## Wiring
  - [Diagram](https://raw.githubusercontent.com/mzakharo/tubby/main/pictures/tubby_wiring.png)
 
## Firmware

- micropython. OTA & Logging over MQTT
- deep (50µA) & light (7mA) sleep
- [Build instructions](https://github.com/mzakharo/micropython/blob/tubby/ports/esp32/README.me.md)
- [Code](https://github.com/mzakharo/micropython/blob/tubby/ports/esp32/modules/app.py)


## FC (Free Chlorine) ppm Model

Predict Free Chlorine/Total Bromine ppm from pH and ORP sensors. 

- Data source:  https://jenfitch.com/free-chlorine-orpmv-vs-ph-new/


Build the model: [fc_model.ipynb](https://github.com/mzakharo/tubby/blob/main/fc_model.ipynb).

Prebuilt model:
- [model_fc.h5](https://github.com/mzakharo/tubby/blob/main/model_fc.h5): model for predicting FC from  ORP/pH

Basic [script](https://github.com/mzakharo/tubby/blob/main/predict.py) to load and run the model. usage:

```bash
python3 predict.py  model_fc.h5 ORP_VALUE PH_VALUE
```

Convert tflite model to tflite-micro
```
make gen
```

Execute tflite-micro model on Native Hardware
```
make tflite
make
./a.out
```

