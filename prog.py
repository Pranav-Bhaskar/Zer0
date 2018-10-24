import os
import numpy
from network.net import Model

def_dir = "./CheckPoint/"
spe = ['.move', 'black', 'white']
peices = {'Z' : 0, 'P' : 1, 'Q' : 2, 'R' : 3, 'B' : 4, 'K' : 5}

def pre_process(k):
	k = k.split(',')
	l = k[-1]
	k = k[:-1]
	for x in l:
		k.append(peices[str(x)])
	k = [int(x) for x in k]
	return numpy.array(k)

def reader():
	val = []
	m = Model()
	m.load()
	l = [f for f in os.listdir(def_dir) if f not in spe]
	for direc in l:
		with open(def_dir + direc, "r") as f:
			for line in f:
				line = line.strip()
				processed = pre_process(line)
				break
		os.remove(def_dir + direc)
		processed = numpy.reshape(processed, (1, 71))
		predicted = m.predict(processed)
		k = [str(processed[0][x]) for x in range(71)]
		k = ','.join(k)
		val.append((predicted, direc, k))
	sorted(val, key=lambda x: x[0][0])
	for x in val[:-1]:
		if x[2][0] is '1':
			f = open(def_dir + "white/.wrong", "a+")
		else:
			f = open(def_dir + "black/.wrong", "a+")
		f.write(str(x[2]))
		f.write('\n')
		f.close()
	
	f = open(def_dir + ".move", "w")
	f.write(str(val[-1][1]))
	f.close()
	
	if val[-1][2][0] is '1':
		f = open(def_dir + "white/.right", "a+")
	else:
		f = open(def_dir + "black/.right", "a+")
	f.write(str(val[-1][2]))
	f.write('\n')
	f.close()

if __name__ == '__main__':
	reader()
