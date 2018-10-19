import os

def_dir = "./CheckPoint/check.point"

def reader():
	l = []
	for direc in os.listdir(def_dir):
		with open(def_dir + direc, "rb") as f:
			byte = f.read()
			while byte != b"":
				
		os.remove(def_dir + direc)
if __name__ == '__main__':
	reader()
