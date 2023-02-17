# Hot Tub Water Quality Sensor

- Battery powered ORP, pH sensor for Hot Tub/SPA
- ~ 1 year battery life @ 2 samples per hour
- Sensor externally mounted, probes placed under the skimmer cover
- [Home Assistant](https://www.home-assistant.io/) Integration
- pH ATC (Automatic Temperature Compensation) integrating with [Balboa](https://github.com/mzakharo/pybalboa) temperature sensor
- Free Chlorine/Bromine estimate model from PH and ORP values

![image](https://user-images.githubusercontent.com/567867/219641155-691258fb-7b6d-4ead-90d6-9f79a9f34092.png)

<img src="https://github.com/mzakharo/tubby/blob/main/pictures/final.jpg" width="250" height="400">  <img src="https://github.com/mzakharo/tubby/blob/main/pictures/probes.jpg" width="250" height="400">  <img src="https://github.com/mzakharo/tubby/blob/main/pictures/cal.jpg" width="250" height="400">

## Hardware
  
 - [UM FeatherS2](https://unexpectedmaker.com/shop/feathers2-esp32-s2) ESP32 board from [here](https://www.adafruit.com/product/4769) 
 - 3500 mAh battery or [2500 mAh](https://www.adafruit.com/product/328)
 - Atlas Scientific Gravity Analog [ORP](https://atlas-scientific.com/kits/gravity-analog-orp-kit/) and [pH](https://atlas-scientific.com/kits/gravity-analog-ph-kit/) Kits
 - Enclosure: [DS-AT-0811-S](https://www.adafruit.com/product/3931)
 - 2 resistors for battery monitoring (optional)

 
## Firmware

- micropython. OTA & Logging over MQTT
- deep (50µA) & light (7mA) sleep
- [Build instructions](https://github.com/mzakharo/micropython/blob/tubby/ports/esp32/README.me.md)
- [Code](https://github.com/mzakharo/micropython/blob/tubby/ports/esp32/modules/app.py)


## FC (Free Chlorine) ppm Model

Predict Free Chlorine & Bromine ppm from pH and ORP sensors. 

- Data source:  https://jenfitch.com/free-chlorine-orpmv-vs-ph-new/


Build the model: [build_model.py](https://github.com/mzakharo/tubby/blob/main/build_model.py).

Prebuilt models:
- [model_fc.h5](https://github.com/mzakharo/tubby/blob/main/model_fc.h5): model for predicting FC from  ORP/pH

- [model_orp.h5](https://github.com/mzakharo/tubby/blob/main/model_orp.h5): model for predicting ORP from FC/PH. This one can be used to calibrate your ORP sensor by getting your water lab tested

Basic [script](https://github.com/mzakharo/tubby/blob/main/predict.py) to load and run these models. usage:

```bash
python3 ./predict.py  model_fc.h5 666 7.6
-> output:  0.83490694
./predict.py model_orp.h5 7.6 0.85
-> output:  667.04565
```

