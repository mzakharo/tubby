import numpy as np
import pandas as pd
import sys
import matplotlib.pyplot as plt
import seaborn as sns
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers

TARGET = sys.argv[1] if len(sys.argv) == 2 else 'fc'

print(tf.__version__)
np.set_printoptions(precision=3, suppress=True)

#Data from https://jenfitch.com/free-chlorine-orpmv-vs-ph-new/
df = pd.read_csv('https://raw.githubusercontent.com/mzakharo/micropython/tubby/ports/esp32/orp.csv')
print(df)
labels = df.pop('ppm CL')

def plot_loss(history):
  plt.plot(history.history['loss'], label='loss')
  plt.plot(history.history['val_loss'], label='val_loss')
  #plt.ylim([0, 10])
  plt.xlabel('Epoch')
  plt.ylabel('Error')
  plt.legend()
  plt.grid(True)

vs = []
for column in df:
    vals= df[column].to_numpy()
    c = float(column)
    for i, v in enumerate(vals):
        vs.append((v, c, labels[i]))
dataset = pd.DataFrame(vs, columns= ('orp', 'ph', 'fc'))

train_dataset = dataset.sample(frac=0.9, random_state=0)
test_dataset = dataset.drop(train_dataset.index)

train_features = train_dataset.copy()
train_labels = train_features.pop(TARGET)

test_features = test_dataset.copy()
test_labels = test_features.pop(TARGET)

print(train_dataset.describe().transpose()[['mean', 'std']])
#sns.pairplot(train_dataset, diag_kind='kde')

inorm = tf.keras.layers.Normalization(axis=-1, input_shape=[2, ])
inorm.adapt(np.array(train_features))
onorm = tf.keras.layers.Normalization(axis=-1, invert=True)
onorm.adapt(train_labels)

def build_and_compile_model(inorm, onorm):
  model = keras.Sequential([
      inorm,
      layers.Dense(10, activation='relu'),
      layers.Dense(10, activation='relu'),
      layers.Dense(1), 
      onorm,
  ])
  model.compile(loss='mean_squared_error', optimizer='adam')
  return model
model = build_and_compile_model(inorm, onorm)
model.summary()
history = model.fit(
    train_features,
    train_labels,
    validation_split=0.1,
    verbose=0, epochs=200)
print('mse:', model.evaluate(test_features, test_labels, verbose=0))
plot_loss(history)
y = model.predict(test_features, verbose=0)
y = pd.DataFrame(y)[0]

plt.figure(figsize=(5,5))
sns.scatterplot(x=test_labels, y=y.to_numpy(), alpha=0.7)
plt.grid()
plt.show()

model.save(f'model_{TARGET}.h5')
converter = tf.lite.TFLiteConverter.from_keras_model(model)
tflite_model = converter.convert()
with open(f'model_{TARGET}.tflite', "wb") as f:
  f.write(tflite_model)
print('done')
