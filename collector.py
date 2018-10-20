import argparse
import numpy
from network.net import Model
import os

def_dir = './CheckPoint/'

def fetch_data(folder, files):
	file_path = os.path.join(def_dir, folder, files)
	val_x = numpy.array([]).reshape(0,71)
	if os.path.isfile(file_path):
		with open(file_path, "r") as f:
			for line in f:
				line = line.strip()
				processed = pre_process(line)
				processed = numpy.reshape(processed, (1, 71))
				val_x = numpy.concatenate((val_x, processed))
		os.unlink(file_path)
	else:
		print('ERROR')
	
	x, y = val_x.shape
	if files == '.right':
		val_y = numpy.ones([x, 1])
	else:
		val_y = numpy.zeros([x, 1])
	return (val_x, val_y)

def pre_process(k):
	k = k.split(',')
	k = [int(x) for x in k]
	return numpy.array(k)

def clear_dir(folder):
	for the_file in os.listdir(def_dir + folder):
		file_path = os.path.join(folder, the_file)
		try:
			if os.path.isfile(file_path):
				os.unlink(file_path)
		except:
			print('Error')

def train_dir(folder):
	x, y = fetch_data(folder, '.right')
	l, r = fetch_data(folder, '.wrong')
	val_x = numpy.concatenate((x, l))
	val_y = numpy.concatenate((y, r))
	m = Model()
	m.load()
	m.fit(val_x, val_y)
	m.save()

if __name__ == '__main__':
	parser = argparse.ArgumentParser()
	parser.add_argument('opt', metavar='int', type=int, choices=range(3), help='an integer from [0, 1, 2]')
	args = parser.parse_args()
	if args.opt == 0:	#Tie
		clear_dir('black')
		clear_dir('white')
	elif args.opt == 1:	#White Won
		clear_dir('black')
		train_dir('white')
		clear_dir('white')
	elif args.opt == 2:	#Black Won
		train_dir('black')
		clear_dir('white')
		clear_dir('black')
