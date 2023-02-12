#!/usr/bin/env python3
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3' 
import keras
import sys

fmodel = sys.argv[1]
p0 = float(sys.argv[2])
p1 = float(sys.argv[3])
model = keras.models.load_model(fmodel, compile=False)
model.layers[-1].invert = True #Bug in Keras https://github.com/keras-team/keras/issues/17556

v = model.predict([(p0, p1)], verbose=0)[0][0]
print('output: ', v)
