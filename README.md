# Hot Tub Sensor and Automation. 

- Battery powered ORP, PH sensor for Hot Tub/SPA or Pool sensing applications.
- Deep & Light sleep for ~ 1 year battery life @ 2 samples per hour
- MQTT with Home Assistant Auto Discovery
- Remote Logging and OTA over MQTT
- PH ATC (Automatic Temperature Compensation) integrating with [Balboa](https://github.com/mzakharo/pybalboa) temperature sensor
- Free Chlorine/Bromine estimator model from PH and ORP values

# Photos

<img src="https://github.com/mzakharo/tubby/blob/main/pictures/final.jpg" width="250" height="400">  <img src="https://github.com/mzakharo/tubby/blob/main/pictures/probes.jpg" width="250" height="400">  <img src="https://github.com/mzakharo/tubby/blob/main/pictures/cal.jpg" width="250" height="400">

# Hardware
  
 - [UM FeatherS2](https://unexpectedmaker.com/shop/feathers2-esp32-s2) ESP32 board 
 - 3500 mA battery
 - Atlas Scientific Gravity Analog [ORP](https://atlas-scientific.com/kits/gravity-analog-orp-kit/) and [PH](https://atlas-scientific.com/kits/gravity-analog-ph-kit/) Kits
 - Enclosure: https://www.adafruit.com/product/3931
 - 2 resistors for battery sensing

 
# Firmware

- https://github.com/mzakharo/micropython/blob/tubby/ports/esp32/README.me.md
- https://github.com/mzakharo/micropython/blob/tubby/ports/esp32/modules/app.py


# FC (Free Chlorine) ppm Model

Predict Free Chlorine & Bromine ppm from PH and ORP sensors. 

- Data source:  https://jenfitch.com/free-chlorine-orpmv-vs-ph-new/


Build the model: [build_model.py](https://github.com/mzakharo/tubby/blob/main/build_model.py).

Prebuilt models:
- [model_fc.h5](https://github.com/mzakharo/tubby/blob/main/model_fc.h5): model for predicting FC from  ORP/PH

- [model_orp.h5](https://github.com/mzakharo/tubby/blob/main/model_orp.h5): model for predicting ORP from FC/PH. This one can be used to calibrate your ORP sensor by getting your water lab tested

Basic [script](https://github.com/mzakharo/tubby/blob/main/predict.py) to load and run these models. usage:

```bash
python3 ./predict.py  model_fc.h5 666 7.6
-> output:  0.83490694
./predict.py model_orp.h5 7.6 0.85
-> output:  667.04565
```

