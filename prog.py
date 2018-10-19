import os
from random import randint

def_dir = "./CheckPoint/"

def reader():
	l = [f for f in os.listdir(def_dir) if not f.startswith('.')]
	for direc in l:
		with open(def_dir + direc, "r") as f:
			for line in f:
				k = line.split(',')
		os.remove(def_dir + direc)
	f = open(def_dir + ".move", "w")
	f.write(str(l[randint(0, len(l) - 1)]));
	f.close()
if __name__ == '__main__':
	reader()
