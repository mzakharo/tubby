#!/usr/bin/env python3
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3' 
import sys

fmodel = sys.argv[1]
p0 = float(sys.argv[2])
p1 = float(sys.argv[3])

if fmodel.endswith('tflite'):
    import tensorflow as tf
    import numpy as np
    interpreter = tf.lite.Interpreter(model_path=fmodel)
    input_details = interpreter.get_input_details()
    output_details = interpreter.get_output_details()
    interpreter.allocate_tensors()
    input_data = np.array([[p0,p1]], dtype=np.float32)
    interpreter.set_tensor(input_details[0]['index'], input_data)
    interpreter.invoke()
    v = interpreter.get_tensor(output_details[0]['index'])[0][0]
else:
    import keras
    model = keras.models.load_model(fmodel)
    model.summary()
    v = model.predict([(p0, p1)], verbose=0)[0][0]

print('output: ', v)
