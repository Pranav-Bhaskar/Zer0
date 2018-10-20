from tensorflow import keras
import numpy as np

class Model:
	def __init__(self):
		self.model = keras.Sequential([
			keras.layers.Dense(64, input_shape=(71, ), activation='relu'),
			keras.layers.Dense(64, activation='relu'),
			keras.layers.Dense(8, activation='relu'),
			keras.layers.Dense(1, activation='softmax'),
		])
		self.model.compile(optimizer=keras.optimizers.Adam(0.01),
			loss='mse',
			metrics=['mae',
		])

	def save(self):
		self.model.save('./data/model.h5')

	def load(self):
		self.model = keras.models.load_model('./data/model.h5')

	def fit(self, x, y):
		self.model.fit(x, y, epochs=26, batch_size=100)

	def predict(self, input_data):
		return self.model.predict(input_data)
