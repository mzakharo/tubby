#!/usr/bin/env python3
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3' 
import tensorflow as tf
from tensorflow.python.keras.saving import hdf5_format
import keras
import h5py
import sys

def load(model_path):
  # Load model
  with h5py.File(model_path, mode='r') as f:
      omean = f.attrs['omean']
      ovar = f.attrs['ovar']
      model = keras.models.load_model(f)
      denorm = tf.keras.layers.Normalization(mean=omean, variance=ovar, invert=True)
      return model, denorm

fmodel = sys.argv[1]
p0 = float(sys.argv[2])
p1 = float(sys.argv[3])
model, denorm = load(fmodel)

v = model.predict([(p0, p1)], verbose=0)[0]
print('output: ', denorm(v).numpy()[0])
