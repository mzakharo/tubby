# tubby
Hot Tub Sensor and Automation. 

- Battery powered ORP, PH sensor for Hot Tub or Pool sensing applications.
- Hardware: UM Feather S2,  Atlas Scientific Analog PH and ORP probes
- Deep & Light sleep for extended battery life
- MQTT with Home Assistant Auto Discovery
- Remote Logging and OTA over MQTT
- PH ATC (Atomatic Temperature Compensation)
- Free Chlorine/Bromine estimator model from PH and ORP values


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

