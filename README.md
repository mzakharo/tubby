# tubby
Hot Tub Sensor and Automation. 

- Battery powered ORP, PH sensor for Hot Tub or Pool sensing applications.
- Deep & Light sleep for extended battery life
- MQTT with Home Assistant Auto Discovery
- Remote Logging and OTA over MQTT
- PH ATC (Automatic Temperature Compensation) integrating with [Balboa](https://github.com/mzakharo/pybalboa) temperature sensor
- Free Chlorine/Bromine estimator model from PH and ORP values

# Photos

- The unit: https://photos.app.goo.gl/cud7ST96oGnMVKvp7
- Grafana view: https://photos.app.goo.gl/5XL6RLwuQzMN658Q7

# Hardware
  
 - Ultimate-Maker FeatherS2 ESP32 board (has an extra regulator that shuts off power to the Analog sensors). 
 - 3500 mA battery
 - Atlas Scientific Analog Kits
 - Enclosure: https://www.adafruit.com/product/3931

 
# Firmware

- https://github.com/mzakharo/micropython/blob/tubby/ports/esp32/README.me.md


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

